
#ifndef RETICULATE_LIBPYTHON_H
#define RETICULATE_LIBPYTHON_H

#include <string>
#include <ostream>
#include <stdint.h>

#ifndef LIBPYTHON_CPP
#define LIBPYTHON_EXTERN extern
#else
#define LIBPYTHON_EXTERN
#endif

#define _PYTHON_API_VERSION 1013
#define _PYTHON3_ABI_VERSION 3

LIBPYTHON_EXTERN void **PyArray_API;
//LIBPYTHON_EXTERN unsigned int PyArray_RUNTIME_VERSION;

namespace reticulate {
namespace libpython {





// #if _WIN32 || _WIN64
// #if _WIN64
// typedef __int64 Py_ssize_t;
// #else
// typedef int Py_ssize_t;
// #endif
// #else
// typedef long Py_ssize_t;
// #endif

// #define METH_VARARGS  0x0001
// #define METH_KEYWORDS 0x0002

// #define Py_file_input 257
// #define Py_eval_input 258

// #ifdef RETICULATE_PYTHON_DEBUG

// #define _PyObject_HEAD_EXTRA            \
//     struct _object *_ob_next;           \
//     struct _object *_ob_prev;

// #define _PyObject_EXTRA_INIT 0, 0,

// #else

// #define _PyObject_HEAD_EXTRA
// #define _PyObject_EXTRA_INIT

// #endif /* RETICULATE_PYTHON_DEBUG */

// #define PyObject_HEAD  \
// _PyObject_HEAD_EXTRA   \
//   Py_ssize_t ob_refcnt; \
// struct _typeobject *ob_type;

// #define PyObject_VAR_HEAD               \
// PyObject_HEAD                           \
//   Py_ssize_t ob_size;

// typedef struct _typeobject {
// PyObject_VAR_HEAD
//   const char *tp_name;
//   Py_ssize_t tp_basicsize, tp_itemsize;
// } PyTypeObject;

// typedef struct _object {
// PyObject_HEAD
// } PyObject;

// typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);

// struct PyMethodDef {
//   const char	*ml_name;
//   PyCFunction  ml_meth;
//   int		 ml_flags;
//   const char	*ml_doc;
// };
// typedef struct PyMethodDef PyMethodDef;

// #define PyObject_HEAD3 PyObject ob_base;

// #define PyObject_HEAD_INIT(type) \
// { _PyObject_EXTRA_INIT           \
//   1, type },

// #define PyModuleDef_HEAD_INIT { \
// PyObject_HEAD_INIT(NULL) \
//   NULL, \
//   0, \
//   NULL, \
// }

// typedef int (*inquiry)(PyObject *);
// typedef int (*visitproc)(PyObject *, void *);
// typedef int (*traverseproc)(PyObject *, visitproc, void *);
// typedef void (*freefunc)(void *);
// typedef void (*PyOS_sighandler_t)(int);

// typedef struct PyModuleDef_Base {
//   PyObject_HEAD3
//   PyObject* (*m_init)(void);
//   Py_ssize_t m_index;
//   PyObject* m_copy;
// } PyModuleDef_Base;

// typedef struct PyModuleDef{
//   PyModuleDef_Base m_base;
//   const char* m_name;
//   const char* m_doc;
//   Py_ssize_t m_size;
//   PyMethodDef *m_methods;
//   inquiry m_reload;
//   traverseproc m_traverse;
//   inquiry m_clear;
//   freefunc m_free;
// } PyModuleDef;

// typedef struct PyCompilerFlags{
//   int cf_flags;
//   int cf_feature_version;
// } PyCompilerFlags;

// typedef Py_ssize_t Py_hash_t;

// LIBPYTHON_EXTERN PyTypeObject* PyFunction_Type;
// LIBPYTHON_EXTERN PyTypeObject* PyModule_Type;
// LIBPYTHON_EXTERN PyTypeObject* PyType_Type;
// LIBPYTHON_EXTERN PyTypeObject* PyProperty_Type;
// LIBPYTHON_EXTERN PyTypeObject* PyMethod_Type;

// LIBPYTHON_EXTERN PyObject* Py_None;
// LIBPYTHON_EXTERN PyObject* Py_Unicode;
// LIBPYTHON_EXTERN PyObject* Py_String;
// LIBPYTHON_EXTERN PyObject* Py_Int;
// LIBPYTHON_EXTERN PyObject* Py_Long;
// LIBPYTHON_EXTERN PyObject* Py_Bool;
// LIBPYTHON_EXTERN PyObject* Py_True;
// LIBPYTHON_EXTERN PyObject* Py_False;
// LIBPYTHON_EXTERN PyObject* Py_Dict;
// LIBPYTHON_EXTERN PyObject* Py_DictClass;
// LIBPYTHON_EXTERN PyObject* Py_Float;
// LIBPYTHON_EXTERN PyObject* Py_List;
// LIBPYTHON_EXTERN PyObject* Py_Tuple;
// LIBPYTHON_EXTERN PyObject* Py_Complex;
// LIBPYTHON_EXTERN PyObject* Py_ByteArray;
// LIBPYTHON_EXTERN PyObject* PyExc_KeyboardInterrupt;
// LIBPYTHON_EXTERN PyObject* PyExc_AttributeError;
// LIBPYTHON_EXTERN PyObject* PyExc_RuntimeError;
// LIBPYTHON_EXTERN PyObject* PyExc_ValueError;

// void initialize_type_objects(bool python3);

// #define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)

// #define PyType_HasFeature(type, feature)  ((PyType_GetFlags(type) & (feature)) != 0)
// #define PyType_FastSubclass(type, flag) PyType_HasFeature(type, flag)

// #define Py_TPFLAGS_LONG_SUBCLASS        (1UL << 24)
// #define PyLong_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_LONG_SUBCLASS)
// #define PyLong_CheckExact(o)      (Py_TYPE(o) == Py_TYPE(Py_Long))

// #define Py_TPFLAGS_LIST_SUBCLASS        (1UL << 25)
// #define PyList_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_LIST_SUBCLASS)
// #define PyList_CheckExact(o)      (Py_TYPE(o) == Py_TYPE(Py_List))

// #define Py_TPFLAGS_TUPLE_SUBCLASS       (1UL << 26)
// #define PyTuple_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_TUPLE_SUBCLASS)
// #define PyTuple_CheckExact(o)     (Py_TYPE(o) == Py_TYPE(Py_Tuple))

// #define Py_TPFLAGS_BYTES_SUBCLASS       (1UL << 27)
// #define PyBytes_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_BYTES_SUBCLASS)

// #define Py_TPFLAGS_UNICODE_SUBCLASS     (1UL << 28)
// #define PyUnicode_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_UNICODE_SUBCLASS)
// #define PyUnicode_CheckExact(o)   (Py_TYPE(o) == Py_TYPE(Py_Unicode))

// #define Py_TPFLAGS_DICT_SUBCLASS        (1UL << 29)
// #define PyDict_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_DICT_SUBCLASS)
// #define PyDict_CheckExact(o)      (Py_TYPE(o) == Py_TYPE(Py_Dict))

// #define Py_TPFLAGS_BASE_EXC_SUBCLASS    (1UL << 30)
// #define PyExceptionInstance_Check(x) PyType_FastSubclass(Py_TYPE(x), Py_TPFLAGS_BASE_EXC_SUBCLASS)

// #define Py_TPFLAGS_TYPE_SUBCLASS        (1UL << 31)
// #define PyType_Check(op) PyType_FastSubclass(Py_TYPE(op), Py_TPFLAGS_TYPE_SUBCLASS)
// #define PyType_CheckExact(op) (Py_TYPE(op) == PyType_Type)

// #define PyString_Check(o)    (Py_TYPE(o) == Py_TYPE(Py_String))
// #define PyInt_Check(o)       (Py_TYPE(o) == Py_TYPE(Py_Int))
// #define PyFloat_Check(o)     (Py_TYPE(o) == Py_TYPE(Py_Float))
// #define PyComplex_Check(o)   (Py_TYPE(o) == Py_TYPE(Py_Complex))
// #define PyByteArray_Check(o) (Py_TYPE(o) == Py_TYPE(Py_ByteArray))

// #define PyBool_Check(o)      ((o == Py_False) || (o == Py_True))
// #define PyFunction_Check(op) ((PyTypeObject*)(Py_TYPE(op)) == PyFunction_Type)
// #define PyMethod_Check(op)   ((PyTypeObject *)(Py_TYPE(op)) == PyMethod_Type)
// #define PyExceptionClass_Check(x)                                       \
//     (PyType_Check((x)) &&                                               \
//      PyType_FastSubclass((PyTypeObject*)(x), Py_TPFLAGS_BASE_EXC_SUBCLASS))

// LIBPYTHON_EXTERN void (*Py_InitializeEx)(int);
// LIBPYTHON_EXTERN void (*Py_Finalize)();
// LIBPYTHON_EXTERN int (*Py_IsInitialized)();
// LIBPYTHON_EXTERN const char* (*Py_GetVersion)();
// LIBPYTHON_EXTERN char* (*Py_GetProgramFullPath_v2)();
// LIBPYTHON_EXTERN wchar_t* (*Py_GetProgramFullPath)();


// LIBPYTHON_EXTERN int (*Py_AddPendingCall)(int (*func)(void *), void *arg);
// LIBPYTHON_EXTERN int (*Py_MakePendingCalls)();
// LIBPYTHON_EXTERN void (*PyErr_SetInterrupt)();
// LIBPYTHON_EXTERN void (*PyErr_CheckSignals)();

// LIBPYTHON_EXTERN PyObject* (*Py_InitModule4)(const char *name, PyMethodDef *methods,
//            const char *doc, PyObject *self,
//            int apiver);

// LIBPYTHON_EXTERN PyObject* (*PyImport_ImportModule)(const char *name);
// LIBPYTHON_EXTERN PyObject* (*PyImport_Import)(PyObject * name);
// LIBPYTHON_EXTERN PyObject* (*PyImport_GetModuleDict)();


// LIBPYTHON_EXTERN PyObject* (*PyModule_Create)(PyModuleDef *def, int);
// LIBPYTHON_EXTERN int (*PyImport_AppendInittab)(const char *name, PyObject* (*initfunc)());

// LIBPYTHON_EXTERN PyObject* (*Py_BuildValue)(const char *format, ...);

// LIBPYTHON_EXTERN void (*Py_IncRef)(PyObject *);
// LIBPYTHON_EXTERN void (*Py_DecRef)(PyObject *);

// LIBPYTHON_EXTERN int (*PyObject_Print)(PyObject* o, FILE* fp, int flags);
// LIBPYTHON_EXTERN PyObject* (*PyObject_Str)(PyObject *);
// LIBPYTHON_EXTERN PyObject* (*PyObject_Repr)(PyObject *);

// LIBPYTHON_EXTERN int (*PyObject_IsInstance)(PyObject *object, PyObject *typeorclass);

/* Rich comparison opcodes */
#define Py_LT 0
#define Py_LE 1
#define Py_EQ 2
#define Py_NE 3
#define Py_GT 4
#define Py_GE 5

bool import_numpy_api(bool python3, std::string* pError);
int flush_std_buffers();
//  

} // namespace libpython
} // namespace reticulate

#endif /* RETICULATE_LIBPYTHON_H */
