// in the emscripten-build of reticulate we link against a static python 
// library, hence we cannot use the "libpython.cpp/h" part since this 
// assumes a dynamic library. Instead we include the "libpython_extra.cpp/h" part which
// contains the same code from libpython **which is not part of python itself**
#define LIBPYTHON_CPP
#include "libpython_extra.h"

#include <Python.h>

#include <R.h>
#include <Rinternals.h>


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

bool import_numpy_api(bool python3, std::string* pError) {

  PyObject* numpy = PyImport_ImportModule("numpy.core.multiarray");
  if (numpy == NULL) {
    *pError = "numpy.core.multiarray failed to import";
    PyErr_Clear();
    return false;
  }


  PyObject* c_api = PyObject_GetAttrString(numpy, "_ARRAY_API");
  Py_DecRef(numpy);
  if (c_api == NULL) {
    *pError = "numpy.core.multiarray _ARRAY_API not found";
    return false;
  }

  // get api pointer
  // if (python3)
    PyArray_API = (void **)PyCapsule_GetPointer(c_api, NULL);
  // else
  //   PyArray_API = (void **)PyCObject_AsVoidPtr(c_api);

  Py_DecRef(c_api);
  if (PyArray_API == NULL) {
    *pError = "_ARRAY_API is NULL pointer";
    return false;
  }

  // check C API version
  // we aim to compile a single binary compatible with both numpy 2.x and 1.x
 // PyArray_RUNTIME_VERSION = PyArray_GetNDArrayCVersion();
  // if (NPY_VERSION_2 != PyArray_RUNTIME_VERSION &&
  //     NPY_VERSION_1 != PyArray_RUNTIME_VERSION) {
  //   std::ostringstream ostr;
  //   ostr << "incompatible NumPy binary version " << (int) PyArray_GetNDArrayCVersion() << " "
  //   "(expecting version " << (int) NPY_VERSION_2 << " or " << (int) NPY_VERSION_1 << ")";
  //   *pError = ostr.str();
  //   return false;
  // }

  // // check feature version
  // if (NPY_1_6_API_VERSION > PyArray_GetNDArrayCFeatureVersion()) {
  //   std::ostringstream ostr;
  //   ostr << "incompatible NumPy feature version " << (int) PyArray_GetNDArrayCFeatureVersion() << " "
  //   "(expecting version " << (int) NPY_1_6_API_VERSION << " or greater)";
  //   *pError = ostr.str();
  //   return false;
  // }

  return true;
}



} // namespace libpython
} // namespace reticulate
