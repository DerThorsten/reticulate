// in the emscripten-build of reticulate we link against a static python 
// library, hence we cannot use the "libpython.cpp/h" part since this 
// assumes a dynamic library. Instead we include the "libpython_extra.cpp/h" part which
// contains the same code from libpython **which is not part of python itself**
#define LIBPYTHON_CPP
#include "libpython_extra.h"

#include <Python.h>

#include <R.h>
#include <Rinternals.h>
#include <numpy/arrayobject.h>


#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace reticulate {
namespace libpython {

// returns 'true' if the buffer was flushed, or if the stdout / stderr
// objects within 'sys' did not contain 'flush' methods
bool flush_std_buffer(const char* name) {

  // returns borrowed reference
  PyObject* buffer(PySys_GetObject(name));
  if (buffer == NULL || buffer == Py_None)
    return true;

  // try to invoke flush method
  PyObject* result = PyObject_CallMethod(buffer, "flush", NULL);
  if (result != NULL) {
    Py_DecRef(result);
    return true;
  }

  // if we got here, an error must have occurred; print it
  PyObject *ptype, *pvalue, *ptraceback;
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
  if (pvalue) {
    PyObject* pvalue_str = PyObject_Str(pvalue);
    if (pvalue_str) {
      REprintf("Error flushing Python %s: %s\n", name, PyUnicode_AsUTF8(pvalue_str));
      Py_DecRef(pvalue_str);
    }
  }

  // clean up
  if (ptype)      Py_DecRef(ptype);
  if (pvalue)     Py_DecRef(pvalue);
  if (ptraceback) Py_DecRef(ptraceback);

  return false;

}

  
int flush_std_buffers() {

  PyObject *error_type, *error_value, *error_traceback;
  PyErr_Fetch(&error_type, &error_value, &error_traceback);
  bool stdout_ok = flush_std_buffer("stdout");
  bool stderr_ok = flush_std_buffer("stderr");
  bool ok = stdout_ok && stderr_ok;
  PyErr_Restore(error_type, error_value, error_traceback);

  return ok ? 0 : -1;

}



} // namespace libpython
} // namespace reticulate
