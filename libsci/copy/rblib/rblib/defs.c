#define PY_SSIZE_T_CLEAN
#ifndef CYTHON_USE_PYLONG_INTERNALS
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 0
#else
#include "pyconfig.h"
#ifdef PYLONG_BITS_IN_DIGIT
#define CYTHON_USE_PYLONG_INTERNALS 1
#else
#define CYTHON_USE_PYLONG_INTERNALS 0
#endif
#endif
#endif
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03020000)
    #error Cython requires Python 2.6+ or Python 3.2+.
#else
#define CYTHON_ABI "0_22_1"
#include <stddef.h>
#ifndef offsetof
#define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
#define CYTHON_COMPILING_IN_PYPY 1
#define CYTHON_COMPILING_IN_CPYTHON 0
#else
#define CYTHON_COMPILING_IN_PYPY 0
#define CYTHON_COMPILING_IN_CPYTHON 1
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
#define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos) \
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ? \
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
#else
  #define CYTHON_PEP393_ENABLED 0
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
  #define __Pyx_PyFrozenSet_Size(s)         PyObject_Size(s)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ? \
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
  #define __Pyx_PyFrozenSet_Size(s)         PySet_Size(s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#ifndef CYTHON_INLINE
  #if defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  /* Initialize NaN. The sign is irrelevant, an exponent with all bits 1 and
   a nonzero mantissa means NaN. If the first bit in the mantissa is 1, it is
   a quiet NaN. */
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#define __Pyx_void_to_None(void_result) (void_result, Py_INCREF(Py_None), Py_None)
#ifdef __cplusplus
template<typename T>
void __Pyx_call_destructor(T* x) {
    x->~T();
}
template<typename T>
class __Pyx_FakeReference {
  public:
    __Pyx_FakeReference() : ptr(NULL) { }
    __Pyx_FakeReference(T& ref) : ptr(&ref) { }
    T *operator->() { return ptr; }
    operator T&() { return *ptr; }
  private:
    T *ptr;
};
#endif


#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#define __PYX_HAVE__rblib__defs
#define __PYX_HAVE_API__rblib__defs
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
typedef struct {PyObject **p; char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (    \
    (sizeof(type) < sizeof(Py_ssize_t))  ||             \
    (sizeof(type) > sizeof(Py_ssize_t) &&               \
          likely(v < (type)PY_SSIZE_T_MAX ||            \
                 v == (type)PY_SSIZE_T_MAX)  &&         \
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||       \
                                v == (type)PY_SSIZE_T_MIN)))  ||  \
    (sizeof(type) == sizeof(Py_ssize_t) &&              \
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||        \
                               v == (type)PY_SSIZE_T_MAX)))  )
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_Owned_Py_None(b) (Py_INCREF(Py_None), Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? (Py_INCREF(Py_True), Py_True) : (Py_INCREF(Py_False), Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_COMPILING_IN_CPYTHON
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "rblib/defs.pyx",
};

/*--- Type declarations ---*/

/* --- Runtime support code (head) --- */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          if (acquire_gil) { \
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure(); \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
              PyGILState_Release(__pyx_gilstate_save); \
          } else { \
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__); \
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil) \
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext() \
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {                            \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_XDECREF(tmp);                              \
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {                             \
        PyObject *tmp = (PyObject *) r;                         \
        r = v; __Pyx_DECREF(tmp);                               \
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

static PyObject *__Pyx_GetBuiltinName(PyObject *name);

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

typedef struct {
    int code_line;
    PyCodeObject* code_object;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

static int __Pyx_check_binary_version(void);

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'rblib.defs' */
#define __Pyx_MODULE_NAME "rblib.defs"
int __pyx_module_is_main_rblib__defs = 0;

/* Implementation of 'rblib.defs' */
static char __pyx_k_1[] = "1";
static char __pyx_k_2[] = "2";
static char __pyx_k_3[] = "3";
static char __pyx_k_4[] = "4";
static char __pyx_k_5[] = "5";
static char __pyx_k_6[] = "6";
static char __pyx_k_7[] = "7";
static char __pyx_k_8[] = "8";
static char __pyx_k_9[] = "9";
static char __pyx_k_A[] = "A";
static char __pyx_k_B[] = "B";
static char __pyx_k_C[] = "C";
static char __pyx_k_D[] = "D";
static char __pyx_k_G[] = "G";
static char __pyx_k_H[] = "H";
static char __pyx_k_I[] = "I";
static char __pyx_k_K[] = "K";
static char __pyx_k_M[] = "M";
static char __pyx_k_N[] = "N";
static char __pyx_k_R[] = "R";
static char __pyx_k_S[] = "S";
static char __pyx_k_T[] = "T";
static char __pyx_k_U[] = "U";
static char __pyx_k_V[] = "V";
static char __pyx_k_W[] = "W";
static char __pyx_k_X[] = "X";
static char __pyx_k_Y[] = "Y";
static char __pyx_k_a[] = "a";
static char __pyx_k_c[] = "c";
static char __pyx_k_g[] = "g";
static char __pyx_k_n[] = "n";
static char __pyx_k_t[] = "t";
static char __pyx_k_u[] = "u";
static char __pyx_k_10[] = "10";
static char __pyx_k_11[] = "11";
static char __pyx_k_12[] = "12";
static char __pyx_k_13[] = "13";
static char __pyx_k_14[] = "14";
static char __pyx_k_15[] = "15";
static char __pyx_k_16[] = "16";
static char __pyx_k_17[] = "17";
static char __pyx_k_18[] = "18";
static char __pyx_k_19[] = "19";
static char __pyx_k_20[] = "20";
static char __pyx_k_21[] = "21";
static char __pyx_k_22[] = "22";
static char __pyx_k_AC[] = "AC";
static char __pyx_k_AG[] = "AG";
static char __pyx_k_AT[] = "AT";
static char __pyx_k_AU[] = "AU";
static char __pyx_k_CA[] = "CA";
static char __pyx_k_CG[] = "CG";
static char __pyx_k_CT[] = "CT";
static char __pyx_k_CU[] = "CU";
static char __pyx_k_Cg[] = "Cg";
static char __pyx_k_GA[] = "GA";
static char __pyx_k_GC[] = "GC";
static char __pyx_k_GT[] = "GT";
static char __pyx_k_GU[] = "GU";
static char __pyx_k_MT[] = "MT";
static char __pyx_k_TA[] = "TA";
static char __pyx_k_TC[] = "TC";
static char __pyx_k_TG[] = "TG";
static char __pyx_k__2[] = "-";
static char __pyx_k_cG[] = "cG";
static char __pyx_k_cg[] = "cg";
static char __pyx_k_re[] = "re";
static char __pyx_k_ACG[] = "ACG";
static char __pyx_k_ACT[] = "ACT";
static char __pyx_k_ACU[] = "ACU";
static char __pyx_k_AGT[] = "AGT";
static char __pyx_k_AGU[] = "AGU";
static char __pyx_k_A_A[] = "A/A";
static char __pyx_k_A_C[] = "A/C";
static char __pyx_k_A_G[] = "A/G";
static char __pyx_k_A_T[] = "A/T";
static char __pyx_k_CGT[] = "CGT";
static char __pyx_k_CGU[] = "CGU";
static char __pyx_k_C_C[] = "C/C";
static char __pyx_k_C_T[] = "C/T";
static char __pyx_k_G_C[] = "G/C";
static char __pyx_k_G_G[] = "G/G";
static char __pyx_k_G_T[] = "G/T";
static char __pyx_k_TEC[] = "TEC";
static char __pyx_k_T_T[] = "T/T";
static char __pyx_k_cpg[] = "cpg";
static char __pyx_k_hdg[] = "hdg";
static char __pyx_k_hrc[] = "hrc";
static char __pyx_k_imm[] = "imm";
static char __pyx_k_lnc[] = "lnc";
static char __pyx_k_ACGT[] = "ACGT";
static char __pyx_k_ACGU[] = "ACGU";
static char __pyx_k_Gene[] = "Gene";
static char __pyx_k_chr1[] = "chr1";
static char __pyx_k_chr2[] = "chr2";
static char __pyx_k_chr3[] = "chr3";
static char __pyx_k_chr4[] = "chr4";
static char __pyx_k_chr5[] = "chr5";
static char __pyx_k_chr6[] = "chr6";
static char __pyx_k_chr7[] = "chr7";
static char __pyx_k_chr8[] = "chr8";
static char __pyx_k_chr9[] = "chr9";
static char __pyx_k_chrM[] = "chrM";
static char __pyx_k_chrX[] = "chrX";
static char __pyx_k_chrY[] = "chrY";
static char __pyx_k_hchr[] = "hchr";
static char __pyx_k_main[] = "__main__";
static char __pyx_k_rRNA[] = "rRNA";
static char __pyx_k_sRNA[] = "sRNA";
static char __pyx_k_srna[] = "srna";
static char __pyx_k_tRNA[] = "tRNA";
static char __pyx_k_test[] = "__test__";
static char __pyx_k_A_T_C[] = "A/T/C";
static char __pyx_k_G_A_C[] = "G/A/C";
static char __pyx_k_G_A_T[] = "G/A/T";
static char __pyx_k_G_C_2[] = "G|C";
static char __pyx_k_G_T_C[] = "G/T/C";
static char __pyx_k_chr10[] = "chr10";
static char __pyx_k_chr11[] = "chr11";
static char __pyx_k_chr12[] = "chr12";
static char __pyx_k_chr13[] = "chr13";
static char __pyx_k_chr14[] = "chr14";
static char __pyx_k_chr15[] = "chr15";
static char __pyx_k_chr16[] = "chr16";
static char __pyx_k_chr17[] = "chr17";
static char __pyx_k_chr18[] = "chr18";
static char __pyx_k_chr19[] = "chr19";
static char __pyx_k_chr20[] = "chr20";
static char __pyx_k_chr21[] = "chr21";
static char __pyx_k_chr22[] = "chr22";
static char __pyx_k_chrMT[] = "chrMT";
static char __pyx_k_hrfam[] = "hrfam";
static char __pyx_k_miRNA[] = "miRNA";
static char __pyx_k_ncRNA[] = "ncRNA";
static char __pyx_k_reppt[] = "reppt";
static char __pyx_k_snRNA[] = "snRNA";
static char __pyx_k_ACGTNU[] = "[^ACGTNU]";
static char __pyx_k_CRISPR[] = "CRISPR";
static char __pyx_k_Intron[] = "Intron";
static char __pyx_k_coding[] = "coding";
static char __pyx_k_hiupac[] = "hiupac";
static char __pyx_k_import[] = "__import__";
static char __pyx_k_lncRNA[] = "lncRNA";
static char __pyx_k_nuclpt[] = "nuclpt";
static char __pyx_k_pseudo[] = "pseudo";
static char __pyx_k_scaRNA[] = "scaRNA";
static char __pyx_k_snoRNA[] = "snoRNA";
static char __pyx_k_A_T_C_G[] = "A/T/C/G";
static char __pyx_k_Cis_reg[] = "Cis-reg";
static char __pyx_k_Mt_rRNA[] = "Mt_rRNA";
static char __pyx_k_Mt_tRNA[] = "Mt_tRNA";
static char __pyx_k_compile[] = "compile";
static char __pyx_k_gcconpt[] = "gcconpt";
static char __pyx_k_hmutidx[] = "hmutidx";
static char __pyx_k_lincRNA[] = "lincRNA";
static char __pyx_k_unknown[] = "unknown";
static char __pyx_k_hnuclidx[] = "hnuclidx";
static char __pyx_k_misc_RNA[] = "misc_RNA";
static char __pyx_k_ribozyme[] = "ribozyme";
static char __pyx_k_vaultRNA[] = "vaultRNA";
static char __pyx_k_Gene_rRNA[] = "Gene_rRNA";
static char __pyx_k_Gene_sRNA[] = "Gene_sRNA";
static char __pyx_k_Gene_tRNA[] = "Gene_tRNA";
static char __pyx_k_IG_C_gene[] = "IG_C_gene";
static char __pyx_k_IG_D_gene[] = "IG_D_gene";
static char __pyx_k_IG_J_gene[] = "IG_J_gene";
static char __pyx_k_IG_V_gene[] = "IG_V_gene";
static char __pyx_k_TR_C_gene[] = "TR_C_gene";
static char __pyx_k_TR_D_gene[] = "TR_D_gene";
static char __pyx_k_TR_J_gene[] = "TR_J_gene";
static char __pyx_k_TR_V_gene[] = "TR_V_gene";
static char __pyx_k_antisense[] = "antisense";
static char __pyx_k_antitoxin[] = "antitoxin";
static char __pyx_k_Gene_miRNA[] = "Gene_miRNA";
static char __pyx_k_Gene_snRNA[] = "Gene_snRNA";
static char __pyx_k_hgeneclass[] = "hgeneclass";
static char __pyx_k_non_coding[] = "non_coding";
static char __pyx_k_pseudogene[] = "pseudogene";
static char __pyx_k_Gene_CRISPR[] = "Gene_CRISPR";
static char __pyx_k_Gene_lncRNA[] = "Gene_lncRNA";
static char __pyx_k_N_n_a_c_g_t[] = "N|n|a|c|g|t";
static char __pyx_k_known_ncrna[] = "known_ncrna";
static char __pyx_k_Cis_reg_IRES[] = "Cis-reg_IRES";
static char __pyx_k_macro_lncRNA[] = "macro_lncRNA";
static char __pyx_k_transposable[] = "transposable";
static char __pyx_k_Gene_ribozyme[] = "Gene_ribozyme";
static char __pyx_k_Cis_reg_leader[] = "Cis-reg_leader";
static char __pyx_k_Gene_antisense[] = "Gene_antisense";
static char __pyx_k_Gene_antitoxin[] = "Gene_antitoxin";
static char __pyx_k_protein_coding[] = "protein_coding";
static char __pyx_k_sense_intronic[] = "sense_intronic";
static char __pyx_k_IG_C_pseudogene[] = "IG_C_pseudogene";
static char __pyx_k_IG_J_pseudogene[] = "IG_J_pseudogene";
static char __pyx_k_IG_V_pseudogene[] = "IG_V_pseudogene";
static char __pyx_k_TR_J_pseudogene[] = "TR_J_pseudogene";
static char __pyx_k_TR_V_pseudogene[] = "TR_V_pseudogene";
static char __pyx_k_sense_overlapping[] = "sense_overlapping";
static char __pyx_k_Cis_reg_riboswitch[] = "Cis-reg_riboswitch";
static char __pyx_k_unitary_pseudogene[] = "unitary_pseudogene";
static char __pyx_k_Gene_snRNA_splicing[] = "Gene_snRNA_splicing";
static char __pyx_k_processed_pseudogene[] = "processed_pseudogene";
static char __pyx_k_processed_transcript[] = "processed_transcript";
static char __pyx_k_transposable_element[] = "transposable_element";
static char __pyx_k_polymorphic_pseudogene[] = "polymorphic_pseudogene";
static char __pyx_k_unprocessed_pseudogene[] = "unprocessed_pseudogene";
static char __pyx_k_Cis_reg_thermoregulator[] = "Cis-reg_thermoregulator";
static char __pyx_k_3prime_overlapping_ncrna[] = "3prime_overlapping_ncrna";
static char __pyx_k_Gene_snRNA_snoRNA_CD_box[] = "Gene_snRNA_snoRNA_CD-box";
static char __pyx_k_Gene_snRNA_snoRNA_scaRNA[] = "Gene_snRNA_snoRNA_scaRNA";
static char __pyx_k_Cis_reg_frameshift_element[] = "Cis-reg_frameshift_element";
static char __pyx_k_Gene_snRNA_snoRNA_HACA_box[] = "Gene_snRNA_snoRNA_HACA-box";
static char __pyx_k_bidirectional_promoter_lncrna[] = "bidirectional_promoter_lncrna";
static char __pyx_k_transcribed_unitary_pseudogene[] = "transcribed_unitary_pseudogene";
static char __pyx_k_translated_processed_pseudogene[] = "translated_processed_pseudogene";
static char __pyx_k_transcribed_processed_pseudogene[] = "transcribed_processed_pseudogene";
static char __pyx_k_transcribed_unprocessed_pseudoge[] = "transcribed_unprocessed_pseudogene";
static char __pyx_k_translated_unprocessed_pseudogen[] = "translated_unprocessed_pseudogene";
static PyObject *__pyx_kp_s_1;
static PyObject *__pyx_kp_s_10;
static PyObject *__pyx_kp_s_11;
static PyObject *__pyx_kp_s_12;
static PyObject *__pyx_kp_s_13;
static PyObject *__pyx_kp_s_14;
static PyObject *__pyx_kp_s_15;
static PyObject *__pyx_kp_s_16;
static PyObject *__pyx_kp_s_17;
static PyObject *__pyx_kp_s_18;
static PyObject *__pyx_kp_s_19;
static PyObject *__pyx_kp_s_2;
static PyObject *__pyx_kp_s_20;
static PyObject *__pyx_kp_s_21;
static PyObject *__pyx_kp_s_22;
static PyObject *__pyx_kp_s_3;
static PyObject *__pyx_kp_s_3prime_overlapping_ncrna;
static PyObject *__pyx_kp_s_4;
static PyObject *__pyx_kp_s_5;
static PyObject *__pyx_kp_s_6;
static PyObject *__pyx_kp_s_7;
static PyObject *__pyx_kp_s_8;
static PyObject *__pyx_kp_s_9;
static PyObject *__pyx_n_s_A;
static PyObject *__pyx_n_s_AC;
static PyObject *__pyx_n_s_ACG;
static PyObject *__pyx_n_s_ACGT;
static PyObject *__pyx_kp_s_ACGTNU;
static PyObject *__pyx_n_s_ACGU;
static PyObject *__pyx_n_s_ACT;
static PyObject *__pyx_n_s_ACU;
static PyObject *__pyx_n_s_AG;
static PyObject *__pyx_n_s_AGT;
static PyObject *__pyx_n_s_AGU;
static PyObject *__pyx_n_s_AT;
static PyObject *__pyx_n_s_AU;
static PyObject *__pyx_kp_s_A_A;
static PyObject *__pyx_kp_s_A_C;
static PyObject *__pyx_kp_s_A_G;
static PyObject *__pyx_kp_s_A_T;
static PyObject *__pyx_kp_s_A_T_C;
static PyObject *__pyx_kp_s_A_T_C_G;
static PyObject *__pyx_n_s_B;
static PyObject *__pyx_n_s_C;
static PyObject *__pyx_n_s_CA;
static PyObject *__pyx_n_s_CG;
static PyObject *__pyx_n_s_CGT;
static PyObject *__pyx_n_s_CGU;
static PyObject *__pyx_n_s_CRISPR;
static PyObject *__pyx_n_s_CT;
static PyObject *__pyx_n_s_CU;
static PyObject *__pyx_kp_s_C_C;
static PyObject *__pyx_kp_s_C_T;
static PyObject *__pyx_n_s_Cg;
static PyObject *__pyx_kp_s_Cis_reg;
static PyObject *__pyx_kp_s_Cis_reg_IRES;
static PyObject *__pyx_kp_s_Cis_reg_frameshift_element;
static PyObject *__pyx_kp_s_Cis_reg_leader;
static PyObject *__pyx_kp_s_Cis_reg_riboswitch;
static PyObject *__pyx_kp_s_Cis_reg_thermoregulator;
static PyObject *__pyx_n_s_D;
static PyObject *__pyx_n_s_G;
static PyObject *__pyx_n_s_GA;
static PyObject *__pyx_n_s_GC;
static PyObject *__pyx_n_s_GT;
static PyObject *__pyx_n_s_GU;
static PyObject *__pyx_kp_s_G_A_C;
static PyObject *__pyx_kp_s_G_A_T;
static PyObject *__pyx_kp_s_G_C;
static PyObject *__pyx_kp_s_G_C_2;
static PyObject *__pyx_kp_s_G_G;
static PyObject *__pyx_kp_s_G_T;
static PyObject *__pyx_kp_s_G_T_C;
static PyObject *__pyx_n_s_Gene;
static PyObject *__pyx_n_s_Gene_CRISPR;
static PyObject *__pyx_n_s_Gene_antisense;
static PyObject *__pyx_n_s_Gene_antitoxin;
static PyObject *__pyx_n_s_Gene_lncRNA;
static PyObject *__pyx_n_s_Gene_miRNA;
static PyObject *__pyx_n_s_Gene_rRNA;
static PyObject *__pyx_n_s_Gene_ribozyme;
static PyObject *__pyx_n_s_Gene_sRNA;
static PyObject *__pyx_n_s_Gene_snRNA;
static PyObject *__pyx_kp_s_Gene_snRNA_snoRNA_CD_box;
static PyObject *__pyx_kp_s_Gene_snRNA_snoRNA_HACA_box;
static PyObject *__pyx_n_s_Gene_snRNA_snoRNA_scaRNA;
static PyObject *__pyx_n_s_Gene_snRNA_splicing;
static PyObject *__pyx_n_s_Gene_tRNA;
static PyObject *__pyx_n_s_H;
static PyObject *__pyx_n_s_I;
static PyObject *__pyx_n_s_IG_C_gene;
static PyObject *__pyx_n_s_IG_C_pseudogene;
static PyObject *__pyx_n_s_IG_D_gene;
static PyObject *__pyx_n_s_IG_J_gene;
static PyObject *__pyx_n_s_IG_J_pseudogene;
static PyObject *__pyx_n_s_IG_V_gene;
static PyObject *__pyx_n_s_IG_V_pseudogene;
static PyObject *__pyx_n_s_Intron;
static PyObject *__pyx_n_s_K;
static PyObject *__pyx_n_s_M;
static PyObject *__pyx_n_s_MT;
static PyObject *__pyx_n_s_Mt_rRNA;
static PyObject *__pyx_n_s_Mt_tRNA;
static PyObject *__pyx_n_s_N;
static PyObject *__pyx_kp_s_N_n_a_c_g_t;
static PyObject *__pyx_n_s_R;
static PyObject *__pyx_n_s_S;
static PyObject *__pyx_n_s_T;
static PyObject *__pyx_n_s_TA;
static PyObject *__pyx_n_s_TC;
static PyObject *__pyx_n_s_TEC;
static PyObject *__pyx_n_s_TG;
static PyObject *__pyx_n_s_TR_C_gene;
static PyObject *__pyx_n_s_TR_D_gene;
static PyObject *__pyx_n_s_TR_J_gene;
static PyObject *__pyx_n_s_TR_J_pseudogene;
static PyObject *__pyx_n_s_TR_V_gene;
static PyObject *__pyx_n_s_TR_V_pseudogene;
static PyObject *__pyx_kp_s_T_T;
static PyObject *__pyx_n_s_U;
static PyObject *__pyx_n_s_V;
static PyObject *__pyx_n_s_W;
static PyObject *__pyx_n_s_X;
static PyObject *__pyx_n_s_Y;
static PyObject *__pyx_kp_s__2;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_antisense;
static PyObject *__pyx_n_s_antitoxin;
static PyObject *__pyx_n_s_bidirectional_promoter_lncrna;
static PyObject *__pyx_n_s_c;
static PyObject *__pyx_n_s_cG;
static PyObject *__pyx_n_s_cg;
static PyObject *__pyx_n_s_chr1;
static PyObject *__pyx_n_s_chr10;
static PyObject *__pyx_n_s_chr11;
static PyObject *__pyx_n_s_chr12;
static PyObject *__pyx_n_s_chr13;
static PyObject *__pyx_n_s_chr14;
static PyObject *__pyx_n_s_chr15;
static PyObject *__pyx_n_s_chr16;
static PyObject *__pyx_n_s_chr17;
static PyObject *__pyx_n_s_chr18;
static PyObject *__pyx_n_s_chr19;
static PyObject *__pyx_n_s_chr2;
static PyObject *__pyx_n_s_chr20;
static PyObject *__pyx_n_s_chr21;
static PyObject *__pyx_n_s_chr22;
static PyObject *__pyx_n_s_chr3;
static PyObject *__pyx_n_s_chr4;
static PyObject *__pyx_n_s_chr5;
static PyObject *__pyx_n_s_chr6;
static PyObject *__pyx_n_s_chr7;
static PyObject *__pyx_n_s_chr8;
static PyObject *__pyx_n_s_chr9;
static PyObject *__pyx_n_s_chrM;
static PyObject *__pyx_n_s_chrMT;
static PyObject *__pyx_n_s_chrX;
static PyObject *__pyx_n_s_chrY;
static PyObject *__pyx_n_s_coding;
static PyObject *__pyx_n_s_compile;
static PyObject *__pyx_n_s_cpg;
static PyObject *__pyx_n_s_g;
static PyObject *__pyx_n_s_gcconpt;
static PyObject *__pyx_n_s_hchr;
static PyObject *__pyx_n_s_hdg;
static PyObject *__pyx_n_s_hgeneclass;
static PyObject *__pyx_n_s_hiupac;
static PyObject *__pyx_n_s_hmutidx;
static PyObject *__pyx_n_s_hnuclidx;
static PyObject *__pyx_n_s_hrc;
static PyObject *__pyx_n_s_hrfam;
static PyObject *__pyx_n_s_imm;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_n_s_known_ncrna;
static PyObject *__pyx_n_s_lincRNA;
static PyObject *__pyx_n_s_lnc;
static PyObject *__pyx_n_s_lncRNA;
static PyObject *__pyx_n_s_macro_lncRNA;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_miRNA;
static PyObject *__pyx_n_s_misc_RNA;
static PyObject *__pyx_n_s_n;
static PyObject *__pyx_n_s_ncRNA;
static PyObject *__pyx_n_s_non_coding;
static PyObject *__pyx_n_s_nuclpt;
static PyObject *__pyx_n_s_polymorphic_pseudogene;
static PyObject *__pyx_n_s_processed_pseudogene;
static PyObject *__pyx_n_s_processed_transcript;
static PyObject *__pyx_n_s_protein_coding;
static PyObject *__pyx_n_s_pseudo;
static PyObject *__pyx_n_s_pseudogene;
static PyObject *__pyx_n_s_rRNA;
static PyObject *__pyx_n_s_re;
static PyObject *__pyx_n_s_reppt;
static PyObject *__pyx_n_s_ribozyme;
static PyObject *__pyx_n_s_sRNA;
static PyObject *__pyx_n_s_scaRNA;
static PyObject *__pyx_n_s_sense_intronic;
static PyObject *__pyx_n_s_sense_overlapping;
static PyObject *__pyx_n_s_snRNA;
static PyObject *__pyx_n_s_snoRNA;
static PyObject *__pyx_n_s_srna;
static PyObject *__pyx_n_s_t;
static PyObject *__pyx_n_s_tRNA;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_transcribed_processed_pseudogene;
static PyObject *__pyx_n_s_transcribed_unitary_pseudogene;
static PyObject *__pyx_n_s_transcribed_unprocessed_pseudoge;
static PyObject *__pyx_n_s_translated_processed_pseudogene;
static PyObject *__pyx_n_s_translated_unprocessed_pseudogen;
static PyObject *__pyx_n_s_transposable;
static PyObject *__pyx_n_s_transposable_element;
static PyObject *__pyx_n_s_u;
static PyObject *__pyx_n_s_unitary_pseudogene;
static PyObject *__pyx_n_s_unknown;
static PyObject *__pyx_n_s_unprocessed_pseudogene;
static PyObject *__pyx_n_s_vaultRNA;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_3;
static PyObject *__pyx_int_4;
static PyObject *__pyx_int_5;
static PyObject *__pyx_tuple_;

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    "defs",
    0, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_kp_s_1, __pyx_k_1, sizeof(__pyx_k_1), 0, 0, 1, 0},
  {&__pyx_kp_s_10, __pyx_k_10, sizeof(__pyx_k_10), 0, 0, 1, 0},
  {&__pyx_kp_s_11, __pyx_k_11, sizeof(__pyx_k_11), 0, 0, 1, 0},
  {&__pyx_kp_s_12, __pyx_k_12, sizeof(__pyx_k_12), 0, 0, 1, 0},
  {&__pyx_kp_s_13, __pyx_k_13, sizeof(__pyx_k_13), 0, 0, 1, 0},
  {&__pyx_kp_s_14, __pyx_k_14, sizeof(__pyx_k_14), 0, 0, 1, 0},
  {&__pyx_kp_s_15, __pyx_k_15, sizeof(__pyx_k_15), 0, 0, 1, 0},
  {&__pyx_kp_s_16, __pyx_k_16, sizeof(__pyx_k_16), 0, 0, 1, 0},
  {&__pyx_kp_s_17, __pyx_k_17, sizeof(__pyx_k_17), 0, 0, 1, 0},
  {&__pyx_kp_s_18, __pyx_k_18, sizeof(__pyx_k_18), 0, 0, 1, 0},
  {&__pyx_kp_s_19, __pyx_k_19, sizeof(__pyx_k_19), 0, 0, 1, 0},
  {&__pyx_kp_s_2, __pyx_k_2, sizeof(__pyx_k_2), 0, 0, 1, 0},
  {&__pyx_kp_s_20, __pyx_k_20, sizeof(__pyx_k_20), 0, 0, 1, 0},
  {&__pyx_kp_s_21, __pyx_k_21, sizeof(__pyx_k_21), 0, 0, 1, 0},
  {&__pyx_kp_s_22, __pyx_k_22, sizeof(__pyx_k_22), 0, 0, 1, 0},
  {&__pyx_kp_s_3, __pyx_k_3, sizeof(__pyx_k_3), 0, 0, 1, 0},
  {&__pyx_kp_s_3prime_overlapping_ncrna, __pyx_k_3prime_overlapping_ncrna, sizeof(__pyx_k_3prime_overlapping_ncrna), 0, 0, 1, 0},
  {&__pyx_kp_s_4, __pyx_k_4, sizeof(__pyx_k_4), 0, 0, 1, 0},
  {&__pyx_kp_s_5, __pyx_k_5, sizeof(__pyx_k_5), 0, 0, 1, 0},
  {&__pyx_kp_s_6, __pyx_k_6, sizeof(__pyx_k_6), 0, 0, 1, 0},
  {&__pyx_kp_s_7, __pyx_k_7, sizeof(__pyx_k_7), 0, 0, 1, 0},
  {&__pyx_kp_s_8, __pyx_k_8, sizeof(__pyx_k_8), 0, 0, 1, 0},
  {&__pyx_kp_s_9, __pyx_k_9, sizeof(__pyx_k_9), 0, 0, 1, 0},
  {&__pyx_n_s_A, __pyx_k_A, sizeof(__pyx_k_A), 0, 0, 1, 1},
  {&__pyx_n_s_AC, __pyx_k_AC, sizeof(__pyx_k_AC), 0, 0, 1, 1},
  {&__pyx_n_s_ACG, __pyx_k_ACG, sizeof(__pyx_k_ACG), 0, 0, 1, 1},
  {&__pyx_n_s_ACGT, __pyx_k_ACGT, sizeof(__pyx_k_ACGT), 0, 0, 1, 1},
  {&__pyx_kp_s_ACGTNU, __pyx_k_ACGTNU, sizeof(__pyx_k_ACGTNU), 0, 0, 1, 0},
  {&__pyx_n_s_ACGU, __pyx_k_ACGU, sizeof(__pyx_k_ACGU), 0, 0, 1, 1},
  {&__pyx_n_s_ACT, __pyx_k_ACT, sizeof(__pyx_k_ACT), 0, 0, 1, 1},
  {&__pyx_n_s_ACU, __pyx_k_ACU, sizeof(__pyx_k_ACU), 0, 0, 1, 1},
  {&__pyx_n_s_AG, __pyx_k_AG, sizeof(__pyx_k_AG), 0, 0, 1, 1},
  {&__pyx_n_s_AGT, __pyx_k_AGT, sizeof(__pyx_k_AGT), 0, 0, 1, 1},
  {&__pyx_n_s_AGU, __pyx_k_AGU, sizeof(__pyx_k_AGU), 0, 0, 1, 1},
  {&__pyx_n_s_AT, __pyx_k_AT, sizeof(__pyx_k_AT), 0, 0, 1, 1},
  {&__pyx_n_s_AU, __pyx_k_AU, sizeof(__pyx_k_AU), 0, 0, 1, 1},
  {&__pyx_kp_s_A_A, __pyx_k_A_A, sizeof(__pyx_k_A_A), 0, 0, 1, 0},
  {&__pyx_kp_s_A_C, __pyx_k_A_C, sizeof(__pyx_k_A_C), 0, 0, 1, 0},
  {&__pyx_kp_s_A_G, __pyx_k_A_G, sizeof(__pyx_k_A_G), 0, 0, 1, 0},
  {&__pyx_kp_s_A_T, __pyx_k_A_T, sizeof(__pyx_k_A_T), 0, 0, 1, 0},
  {&__pyx_kp_s_A_T_C, __pyx_k_A_T_C, sizeof(__pyx_k_A_T_C), 0, 0, 1, 0},
  {&__pyx_kp_s_A_T_C_G, __pyx_k_A_T_C_G, sizeof(__pyx_k_A_T_C_G), 0, 0, 1, 0},
  {&__pyx_n_s_B, __pyx_k_B, sizeof(__pyx_k_B), 0, 0, 1, 1},
  {&__pyx_n_s_C, __pyx_k_C, sizeof(__pyx_k_C), 0, 0, 1, 1},
  {&__pyx_n_s_CA, __pyx_k_CA, sizeof(__pyx_k_CA), 0, 0, 1, 1},
  {&__pyx_n_s_CG, __pyx_k_CG, sizeof(__pyx_k_CG), 0, 0, 1, 1},
  {&__pyx_n_s_CGT, __pyx_k_CGT, sizeof(__pyx_k_CGT), 0, 0, 1, 1},
  {&__pyx_n_s_CGU, __pyx_k_CGU, sizeof(__pyx_k_CGU), 0, 0, 1, 1},
  {&__pyx_n_s_CRISPR, __pyx_k_CRISPR, sizeof(__pyx_k_CRISPR), 0, 0, 1, 1},
  {&__pyx_n_s_CT, __pyx_k_CT, sizeof(__pyx_k_CT), 0, 0, 1, 1},
  {&__pyx_n_s_CU, __pyx_k_CU, sizeof(__pyx_k_CU), 0, 0, 1, 1},
  {&__pyx_kp_s_C_C, __pyx_k_C_C, sizeof(__pyx_k_C_C), 0, 0, 1, 0},
  {&__pyx_kp_s_C_T, __pyx_k_C_T, sizeof(__pyx_k_C_T), 0, 0, 1, 0},
  {&__pyx_n_s_Cg, __pyx_k_Cg, sizeof(__pyx_k_Cg), 0, 0, 1, 1},
  {&__pyx_kp_s_Cis_reg, __pyx_k_Cis_reg, sizeof(__pyx_k_Cis_reg), 0, 0, 1, 0},
  {&__pyx_kp_s_Cis_reg_IRES, __pyx_k_Cis_reg_IRES, sizeof(__pyx_k_Cis_reg_IRES), 0, 0, 1, 0},
  {&__pyx_kp_s_Cis_reg_frameshift_element, __pyx_k_Cis_reg_frameshift_element, sizeof(__pyx_k_Cis_reg_frameshift_element), 0, 0, 1, 0},
  {&__pyx_kp_s_Cis_reg_leader, __pyx_k_Cis_reg_leader, sizeof(__pyx_k_Cis_reg_leader), 0, 0, 1, 0},
  {&__pyx_kp_s_Cis_reg_riboswitch, __pyx_k_Cis_reg_riboswitch, sizeof(__pyx_k_Cis_reg_riboswitch), 0, 0, 1, 0},
  {&__pyx_kp_s_Cis_reg_thermoregulator, __pyx_k_Cis_reg_thermoregulator, sizeof(__pyx_k_Cis_reg_thermoregulator), 0, 0, 1, 0},
  {&__pyx_n_s_D, __pyx_k_D, sizeof(__pyx_k_D), 0, 0, 1, 1},
  {&__pyx_n_s_G, __pyx_k_G, sizeof(__pyx_k_G), 0, 0, 1, 1},
  {&__pyx_n_s_GA, __pyx_k_GA, sizeof(__pyx_k_GA), 0, 0, 1, 1},
  {&__pyx_n_s_GC, __pyx_k_GC, sizeof(__pyx_k_GC), 0, 0, 1, 1},
  {&__pyx_n_s_GT, __pyx_k_GT, sizeof(__pyx_k_GT), 0, 0, 1, 1},
  {&__pyx_n_s_GU, __pyx_k_GU, sizeof(__pyx_k_GU), 0, 0, 1, 1},
  {&__pyx_kp_s_G_A_C, __pyx_k_G_A_C, sizeof(__pyx_k_G_A_C), 0, 0, 1, 0},
  {&__pyx_kp_s_G_A_T, __pyx_k_G_A_T, sizeof(__pyx_k_G_A_T), 0, 0, 1, 0},
  {&__pyx_kp_s_G_C, __pyx_k_G_C, sizeof(__pyx_k_G_C), 0, 0, 1, 0},
  {&__pyx_kp_s_G_C_2, __pyx_k_G_C_2, sizeof(__pyx_k_G_C_2), 0, 0, 1, 0},
  {&__pyx_kp_s_G_G, __pyx_k_G_G, sizeof(__pyx_k_G_G), 0, 0, 1, 0},
  {&__pyx_kp_s_G_T, __pyx_k_G_T, sizeof(__pyx_k_G_T), 0, 0, 1, 0},
  {&__pyx_kp_s_G_T_C, __pyx_k_G_T_C, sizeof(__pyx_k_G_T_C), 0, 0, 1, 0},
  {&__pyx_n_s_Gene, __pyx_k_Gene, sizeof(__pyx_k_Gene), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_CRISPR, __pyx_k_Gene_CRISPR, sizeof(__pyx_k_Gene_CRISPR), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_antisense, __pyx_k_Gene_antisense, sizeof(__pyx_k_Gene_antisense), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_antitoxin, __pyx_k_Gene_antitoxin, sizeof(__pyx_k_Gene_antitoxin), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_lncRNA, __pyx_k_Gene_lncRNA, sizeof(__pyx_k_Gene_lncRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_miRNA, __pyx_k_Gene_miRNA, sizeof(__pyx_k_Gene_miRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_rRNA, __pyx_k_Gene_rRNA, sizeof(__pyx_k_Gene_rRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_ribozyme, __pyx_k_Gene_ribozyme, sizeof(__pyx_k_Gene_ribozyme), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_sRNA, __pyx_k_Gene_sRNA, sizeof(__pyx_k_Gene_sRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_snRNA, __pyx_k_Gene_snRNA, sizeof(__pyx_k_Gene_snRNA), 0, 0, 1, 1},
  {&__pyx_kp_s_Gene_snRNA_snoRNA_CD_box, __pyx_k_Gene_snRNA_snoRNA_CD_box, sizeof(__pyx_k_Gene_snRNA_snoRNA_CD_box), 0, 0, 1, 0},
  {&__pyx_kp_s_Gene_snRNA_snoRNA_HACA_box, __pyx_k_Gene_snRNA_snoRNA_HACA_box, sizeof(__pyx_k_Gene_snRNA_snoRNA_HACA_box), 0, 0, 1, 0},
  {&__pyx_n_s_Gene_snRNA_snoRNA_scaRNA, __pyx_k_Gene_snRNA_snoRNA_scaRNA, sizeof(__pyx_k_Gene_snRNA_snoRNA_scaRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_snRNA_splicing, __pyx_k_Gene_snRNA_splicing, sizeof(__pyx_k_Gene_snRNA_splicing), 0, 0, 1, 1},
  {&__pyx_n_s_Gene_tRNA, __pyx_k_Gene_tRNA, sizeof(__pyx_k_Gene_tRNA), 0, 0, 1, 1},
  {&__pyx_n_s_H, __pyx_k_H, sizeof(__pyx_k_H), 0, 0, 1, 1},
  {&__pyx_n_s_I, __pyx_k_I, sizeof(__pyx_k_I), 0, 0, 1, 1},
  {&__pyx_n_s_IG_C_gene, __pyx_k_IG_C_gene, sizeof(__pyx_k_IG_C_gene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_C_pseudogene, __pyx_k_IG_C_pseudogene, sizeof(__pyx_k_IG_C_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_D_gene, __pyx_k_IG_D_gene, sizeof(__pyx_k_IG_D_gene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_J_gene, __pyx_k_IG_J_gene, sizeof(__pyx_k_IG_J_gene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_J_pseudogene, __pyx_k_IG_J_pseudogene, sizeof(__pyx_k_IG_J_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_V_gene, __pyx_k_IG_V_gene, sizeof(__pyx_k_IG_V_gene), 0, 0, 1, 1},
  {&__pyx_n_s_IG_V_pseudogene, __pyx_k_IG_V_pseudogene, sizeof(__pyx_k_IG_V_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_Intron, __pyx_k_Intron, sizeof(__pyx_k_Intron), 0, 0, 1, 1},
  {&__pyx_n_s_K, __pyx_k_K, sizeof(__pyx_k_K), 0, 0, 1, 1},
  {&__pyx_n_s_M, __pyx_k_M, sizeof(__pyx_k_M), 0, 0, 1, 1},
  {&__pyx_n_s_MT, __pyx_k_MT, sizeof(__pyx_k_MT), 0, 0, 1, 1},
  {&__pyx_n_s_Mt_rRNA, __pyx_k_Mt_rRNA, sizeof(__pyx_k_Mt_rRNA), 0, 0, 1, 1},
  {&__pyx_n_s_Mt_tRNA, __pyx_k_Mt_tRNA, sizeof(__pyx_k_Mt_tRNA), 0, 0, 1, 1},
  {&__pyx_n_s_N, __pyx_k_N, sizeof(__pyx_k_N), 0, 0, 1, 1},
  {&__pyx_kp_s_N_n_a_c_g_t, __pyx_k_N_n_a_c_g_t, sizeof(__pyx_k_N_n_a_c_g_t), 0, 0, 1, 0},
  {&__pyx_n_s_R, __pyx_k_R, sizeof(__pyx_k_R), 0, 0, 1, 1},
  {&__pyx_n_s_S, __pyx_k_S, sizeof(__pyx_k_S), 0, 0, 1, 1},
  {&__pyx_n_s_T, __pyx_k_T, sizeof(__pyx_k_T), 0, 0, 1, 1},
  {&__pyx_n_s_TA, __pyx_k_TA, sizeof(__pyx_k_TA), 0, 0, 1, 1},
  {&__pyx_n_s_TC, __pyx_k_TC, sizeof(__pyx_k_TC), 0, 0, 1, 1},
  {&__pyx_n_s_TEC, __pyx_k_TEC, sizeof(__pyx_k_TEC), 0, 0, 1, 1},
  {&__pyx_n_s_TG, __pyx_k_TG, sizeof(__pyx_k_TG), 0, 0, 1, 1},
  {&__pyx_n_s_TR_C_gene, __pyx_k_TR_C_gene, sizeof(__pyx_k_TR_C_gene), 0, 0, 1, 1},
  {&__pyx_n_s_TR_D_gene, __pyx_k_TR_D_gene, sizeof(__pyx_k_TR_D_gene), 0, 0, 1, 1},
  {&__pyx_n_s_TR_J_gene, __pyx_k_TR_J_gene, sizeof(__pyx_k_TR_J_gene), 0, 0, 1, 1},
  {&__pyx_n_s_TR_J_pseudogene, __pyx_k_TR_J_pseudogene, sizeof(__pyx_k_TR_J_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_TR_V_gene, __pyx_k_TR_V_gene, sizeof(__pyx_k_TR_V_gene), 0, 0, 1, 1},
  {&__pyx_n_s_TR_V_pseudogene, __pyx_k_TR_V_pseudogene, sizeof(__pyx_k_TR_V_pseudogene), 0, 0, 1, 1},
  {&__pyx_kp_s_T_T, __pyx_k_T_T, sizeof(__pyx_k_T_T), 0, 0, 1, 0},
  {&__pyx_n_s_U, __pyx_k_U, sizeof(__pyx_k_U), 0, 0, 1, 1},
  {&__pyx_n_s_V, __pyx_k_V, sizeof(__pyx_k_V), 0, 0, 1, 1},
  {&__pyx_n_s_W, __pyx_k_W, sizeof(__pyx_k_W), 0, 0, 1, 1},
  {&__pyx_n_s_X, __pyx_k_X, sizeof(__pyx_k_X), 0, 0, 1, 1},
  {&__pyx_n_s_Y, __pyx_k_Y, sizeof(__pyx_k_Y), 0, 0, 1, 1},
  {&__pyx_kp_s__2, __pyx_k__2, sizeof(__pyx_k__2), 0, 0, 1, 0},
  {&__pyx_n_s_a, __pyx_k_a, sizeof(__pyx_k_a), 0, 0, 1, 1},
  {&__pyx_n_s_antisense, __pyx_k_antisense, sizeof(__pyx_k_antisense), 0, 0, 1, 1},
  {&__pyx_n_s_antitoxin, __pyx_k_antitoxin, sizeof(__pyx_k_antitoxin), 0, 0, 1, 1},
  {&__pyx_n_s_bidirectional_promoter_lncrna, __pyx_k_bidirectional_promoter_lncrna, sizeof(__pyx_k_bidirectional_promoter_lncrna), 0, 0, 1, 1},
  {&__pyx_n_s_c, __pyx_k_c, sizeof(__pyx_k_c), 0, 0, 1, 1},
  {&__pyx_n_s_cG, __pyx_k_cG, sizeof(__pyx_k_cG), 0, 0, 1, 1},
  {&__pyx_n_s_cg, __pyx_k_cg, sizeof(__pyx_k_cg), 0, 0, 1, 1},
  {&__pyx_n_s_chr1, __pyx_k_chr1, sizeof(__pyx_k_chr1), 0, 0, 1, 1},
  {&__pyx_n_s_chr10, __pyx_k_chr10, sizeof(__pyx_k_chr10), 0, 0, 1, 1},
  {&__pyx_n_s_chr11, __pyx_k_chr11, sizeof(__pyx_k_chr11), 0, 0, 1, 1},
  {&__pyx_n_s_chr12, __pyx_k_chr12, sizeof(__pyx_k_chr12), 0, 0, 1, 1},
  {&__pyx_n_s_chr13, __pyx_k_chr13, sizeof(__pyx_k_chr13), 0, 0, 1, 1},
  {&__pyx_n_s_chr14, __pyx_k_chr14, sizeof(__pyx_k_chr14), 0, 0, 1, 1},
  {&__pyx_n_s_chr15, __pyx_k_chr15, sizeof(__pyx_k_chr15), 0, 0, 1, 1},
  {&__pyx_n_s_chr16, __pyx_k_chr16, sizeof(__pyx_k_chr16), 0, 0, 1, 1},
  {&__pyx_n_s_chr17, __pyx_k_chr17, sizeof(__pyx_k_chr17), 0, 0, 1, 1},
  {&__pyx_n_s_chr18, __pyx_k_chr18, sizeof(__pyx_k_chr18), 0, 0, 1, 1},
  {&__pyx_n_s_chr19, __pyx_k_chr19, sizeof(__pyx_k_chr19), 0, 0, 1, 1},
  {&__pyx_n_s_chr2, __pyx_k_chr2, sizeof(__pyx_k_chr2), 0, 0, 1, 1},
  {&__pyx_n_s_chr20, __pyx_k_chr20, sizeof(__pyx_k_chr20), 0, 0, 1, 1},
  {&__pyx_n_s_chr21, __pyx_k_chr21, sizeof(__pyx_k_chr21), 0, 0, 1, 1},
  {&__pyx_n_s_chr22, __pyx_k_chr22, sizeof(__pyx_k_chr22), 0, 0, 1, 1},
  {&__pyx_n_s_chr3, __pyx_k_chr3, sizeof(__pyx_k_chr3), 0, 0, 1, 1},
  {&__pyx_n_s_chr4, __pyx_k_chr4, sizeof(__pyx_k_chr4), 0, 0, 1, 1},
  {&__pyx_n_s_chr5, __pyx_k_chr5, sizeof(__pyx_k_chr5), 0, 0, 1, 1},
  {&__pyx_n_s_chr6, __pyx_k_chr6, sizeof(__pyx_k_chr6), 0, 0, 1, 1},
  {&__pyx_n_s_chr7, __pyx_k_chr7, sizeof(__pyx_k_chr7), 0, 0, 1, 1},
  {&__pyx_n_s_chr8, __pyx_k_chr8, sizeof(__pyx_k_chr8), 0, 0, 1, 1},
  {&__pyx_n_s_chr9, __pyx_k_chr9, sizeof(__pyx_k_chr9), 0, 0, 1, 1},
  {&__pyx_n_s_chrM, __pyx_k_chrM, sizeof(__pyx_k_chrM), 0, 0, 1, 1},
  {&__pyx_n_s_chrMT, __pyx_k_chrMT, sizeof(__pyx_k_chrMT), 0, 0, 1, 1},
  {&__pyx_n_s_chrX, __pyx_k_chrX, sizeof(__pyx_k_chrX), 0, 0, 1, 1},
  {&__pyx_n_s_chrY, __pyx_k_chrY, sizeof(__pyx_k_chrY), 0, 0, 1, 1},
  {&__pyx_n_s_coding, __pyx_k_coding, sizeof(__pyx_k_coding), 0, 0, 1, 1},
  {&__pyx_n_s_compile, __pyx_k_compile, sizeof(__pyx_k_compile), 0, 0, 1, 1},
  {&__pyx_n_s_cpg, __pyx_k_cpg, sizeof(__pyx_k_cpg), 0, 0, 1, 1},
  {&__pyx_n_s_g, __pyx_k_g, sizeof(__pyx_k_g), 0, 0, 1, 1},
  {&__pyx_n_s_gcconpt, __pyx_k_gcconpt, sizeof(__pyx_k_gcconpt), 0, 0, 1, 1},
  {&__pyx_n_s_hchr, __pyx_k_hchr, sizeof(__pyx_k_hchr), 0, 0, 1, 1},
  {&__pyx_n_s_hdg, __pyx_k_hdg, sizeof(__pyx_k_hdg), 0, 0, 1, 1},
  {&__pyx_n_s_hgeneclass, __pyx_k_hgeneclass, sizeof(__pyx_k_hgeneclass), 0, 0, 1, 1},
  {&__pyx_n_s_hiupac, __pyx_k_hiupac, sizeof(__pyx_k_hiupac), 0, 0, 1, 1},
  {&__pyx_n_s_hmutidx, __pyx_k_hmutidx, sizeof(__pyx_k_hmutidx), 0, 0, 1, 1},
  {&__pyx_n_s_hnuclidx, __pyx_k_hnuclidx, sizeof(__pyx_k_hnuclidx), 0, 0, 1, 1},
  {&__pyx_n_s_hrc, __pyx_k_hrc, sizeof(__pyx_k_hrc), 0, 0, 1, 1},
  {&__pyx_n_s_hrfam, __pyx_k_hrfam, sizeof(__pyx_k_hrfam), 0, 0, 1, 1},
  {&__pyx_n_s_imm, __pyx_k_imm, sizeof(__pyx_k_imm), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_n_s_known_ncrna, __pyx_k_known_ncrna, sizeof(__pyx_k_known_ncrna), 0, 0, 1, 1},
  {&__pyx_n_s_lincRNA, __pyx_k_lincRNA, sizeof(__pyx_k_lincRNA), 0, 0, 1, 1},
  {&__pyx_n_s_lnc, __pyx_k_lnc, sizeof(__pyx_k_lnc), 0, 0, 1, 1},
  {&__pyx_n_s_lncRNA, __pyx_k_lncRNA, sizeof(__pyx_k_lncRNA), 0, 0, 1, 1},
  {&__pyx_n_s_macro_lncRNA, __pyx_k_macro_lncRNA, sizeof(__pyx_k_macro_lncRNA), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_miRNA, __pyx_k_miRNA, sizeof(__pyx_k_miRNA), 0, 0, 1, 1},
  {&__pyx_n_s_misc_RNA, __pyx_k_misc_RNA, sizeof(__pyx_k_misc_RNA), 0, 0, 1, 1},
  {&__pyx_n_s_n, __pyx_k_n, sizeof(__pyx_k_n), 0, 0, 1, 1},
  {&__pyx_n_s_ncRNA, __pyx_k_ncRNA, sizeof(__pyx_k_ncRNA), 0, 0, 1, 1},
  {&__pyx_n_s_non_coding, __pyx_k_non_coding, sizeof(__pyx_k_non_coding), 0, 0, 1, 1},
  {&__pyx_n_s_nuclpt, __pyx_k_nuclpt, sizeof(__pyx_k_nuclpt), 0, 0, 1, 1},
  {&__pyx_n_s_polymorphic_pseudogene, __pyx_k_polymorphic_pseudogene, sizeof(__pyx_k_polymorphic_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_processed_pseudogene, __pyx_k_processed_pseudogene, sizeof(__pyx_k_processed_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_processed_transcript, __pyx_k_processed_transcript, sizeof(__pyx_k_processed_transcript), 0, 0, 1, 1},
  {&__pyx_n_s_protein_coding, __pyx_k_protein_coding, sizeof(__pyx_k_protein_coding), 0, 0, 1, 1},
  {&__pyx_n_s_pseudo, __pyx_k_pseudo, sizeof(__pyx_k_pseudo), 0, 0, 1, 1},
  {&__pyx_n_s_pseudogene, __pyx_k_pseudogene, sizeof(__pyx_k_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_rRNA, __pyx_k_rRNA, sizeof(__pyx_k_rRNA), 0, 0, 1, 1},
  {&__pyx_n_s_re, __pyx_k_re, sizeof(__pyx_k_re), 0, 0, 1, 1},
  {&__pyx_n_s_reppt, __pyx_k_reppt, sizeof(__pyx_k_reppt), 0, 0, 1, 1},
  {&__pyx_n_s_ribozyme, __pyx_k_ribozyme, sizeof(__pyx_k_ribozyme), 0, 0, 1, 1},
  {&__pyx_n_s_sRNA, __pyx_k_sRNA, sizeof(__pyx_k_sRNA), 0, 0, 1, 1},
  {&__pyx_n_s_scaRNA, __pyx_k_scaRNA, sizeof(__pyx_k_scaRNA), 0, 0, 1, 1},
  {&__pyx_n_s_sense_intronic, __pyx_k_sense_intronic, sizeof(__pyx_k_sense_intronic), 0, 0, 1, 1},
  {&__pyx_n_s_sense_overlapping, __pyx_k_sense_overlapping, sizeof(__pyx_k_sense_overlapping), 0, 0, 1, 1},
  {&__pyx_n_s_snRNA, __pyx_k_snRNA, sizeof(__pyx_k_snRNA), 0, 0, 1, 1},
  {&__pyx_n_s_snoRNA, __pyx_k_snoRNA, sizeof(__pyx_k_snoRNA), 0, 0, 1, 1},
  {&__pyx_n_s_srna, __pyx_k_srna, sizeof(__pyx_k_srna), 0, 0, 1, 1},
  {&__pyx_n_s_t, __pyx_k_t, sizeof(__pyx_k_t), 0, 0, 1, 1},
  {&__pyx_n_s_tRNA, __pyx_k_tRNA, sizeof(__pyx_k_tRNA), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_transcribed_processed_pseudogene, __pyx_k_transcribed_processed_pseudogene, sizeof(__pyx_k_transcribed_processed_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_transcribed_unitary_pseudogene, __pyx_k_transcribed_unitary_pseudogene, sizeof(__pyx_k_transcribed_unitary_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_transcribed_unprocessed_pseudoge, __pyx_k_transcribed_unprocessed_pseudoge, sizeof(__pyx_k_transcribed_unprocessed_pseudoge), 0, 0, 1, 1},
  {&__pyx_n_s_translated_processed_pseudogene, __pyx_k_translated_processed_pseudogene, sizeof(__pyx_k_translated_processed_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_translated_unprocessed_pseudogen, __pyx_k_translated_unprocessed_pseudogen, sizeof(__pyx_k_translated_unprocessed_pseudogen), 0, 0, 1, 1},
  {&__pyx_n_s_transposable, __pyx_k_transposable, sizeof(__pyx_k_transposable), 0, 0, 1, 1},
  {&__pyx_n_s_transposable_element, __pyx_k_transposable_element, sizeof(__pyx_k_transposable_element), 0, 0, 1, 1},
  {&__pyx_n_s_u, __pyx_k_u, sizeof(__pyx_k_u), 0, 0, 1, 1},
  {&__pyx_n_s_unitary_pseudogene, __pyx_k_unitary_pseudogene, sizeof(__pyx_k_unitary_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_unknown, __pyx_k_unknown, sizeof(__pyx_k_unknown), 0, 0, 1, 1},
  {&__pyx_n_s_unprocessed_pseudogene, __pyx_k_unprocessed_pseudogene, sizeof(__pyx_k_unprocessed_pseudogene), 0, 0, 1, 1},
  {&__pyx_n_s_vaultRNA, __pyx_k_vaultRNA, sizeof(__pyx_k_vaultRNA), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  return 0;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "rblib/defs.pyx":48
 * import re
 * nuclpt  = re.compile("[^ACGTNU]",re.I)
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]             # <<<<<<<<<<<<<<
 * gcconpt = re.compile("G|C",re.I)
 * cpg     = re.compile("CG",re.I)
 */
  __pyx_tuple_ = PyTuple_Pack(1, __pyx_kp_s_N_n_a_c_g_t); if (unlikely(!__pyx_tuple_)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_tuple_);
  __Pyx_GIVEREF(__pyx_tuple_);
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_3 = PyInt_FromLong(3); if (unlikely(!__pyx_int_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_4 = PyInt_FromLong(4); if (unlikely(!__pyx_int_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_int_5 = PyInt_FromLong(5); if (unlikely(!__pyx_int_5)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initdefs(void); /*proto*/
PyMODINIT_FUNC initdefs(void)
#else
PyMODINIT_FUNC PyInit_defs(void); /*proto*/
PyMODINIT_FUNC PyInit_defs(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  PyObject *__pyx_t_4 = NULL;
  Py_ssize_t __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  int __pyx_lineno = 0;
  const char *__pyx_filename = NULL;
  int __pyx_clineno = 0;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_defs(void)", 0);
  if ( __Pyx_check_binary_version() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #ifdef __Pyx_CyFunction_USED
  if (__Pyx_CyFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("defs", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  /*--- Initialize various global constants etc. ---*/
  if (unlikely(__Pyx_InitGlobals() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  #endif
  if (__pyx_module_is_main_rblib__defs) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;};
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    if (!PyDict_GetItemString(modules, "rblib.defs")) {
      if (unlikely(PyDict_SetItemString(modules, "rblib.defs", __pyx_m) < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (unlikely(__Pyx_InitCachedBuiltins() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Constants init code ---*/
  if (unlikely(__Pyx_InitCachedConstants() < 0)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  /*--- Type import code ---*/
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/

  /* "rblib/defs.pyx":3
 * # -*- coding: UTF-8 -*-
 * # Degenerate base
 * hchr= {"chr1":"1",             # <<<<<<<<<<<<<<
 * 		"chr2":"2",
 * 		"chr3":"3",
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr1, __pyx_kp_s_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr2, __pyx_kp_s_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr3, __pyx_kp_s_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr4, __pyx_kp_s_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr5, __pyx_kp_s_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr6, __pyx_kp_s_6) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr7, __pyx_kp_s_7) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr8, __pyx_kp_s_8) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr9, __pyx_kp_s_9) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr10, __pyx_kp_s_10) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr11, __pyx_kp_s_11) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr12, __pyx_kp_s_12) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr13, __pyx_kp_s_13) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr14, __pyx_kp_s_14) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr15, __pyx_kp_s_15) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr16, __pyx_kp_s_16) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr17, __pyx_kp_s_17) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr18, __pyx_kp_s_18) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr19, __pyx_kp_s_19) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr20, __pyx_kp_s_20) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr21, __pyx_kp_s_21) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chr22, __pyx_kp_s_22) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chrX, __pyx_n_s_X) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chrY, __pyx_n_s_Y) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chrM, __pyx_n_s_MT) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_chrMT, __pyx_n_s_MT) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hchr, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 3; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":30
 * 		"chrMT":"MT",
 * 		}
 * hdg = {"A":"A/A",             # <<<<<<<<<<<<<<
 * 		"C":"C/C",
 * 		"G":"G/G",
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_A, __pyx_kp_s_A_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_C, __pyx_kp_s_C_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_G, __pyx_kp_s_G_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_T, __pyx_kp_s_T_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_R, __pyx_kp_s_A_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Y, __pyx_kp_s_C_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_M, __pyx_kp_s_A_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_K, __pyx_kp_s_G_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_S, __pyx_kp_s_G_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_W, __pyx_kp_s_A_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_H, __pyx_kp_s_A_T_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_B, __pyx_kp_s_G_T_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_V, __pyx_kp_s_G_A_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_D, __pyx_kp_s_G_A_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_N, __pyx_kp_s_A_T_C_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hdg, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 30; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":46
 * 		"N":"A/T/C/G",
 * 		}
 * import re             # <<<<<<<<<<<<<<
 * nuclpt  = re.compile("[^ACGTNU]",re.I)
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_re, 0, -1); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 46; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_re, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 46; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":47
 * 		}
 * import re
 * nuclpt  = re.compile("[^ACGTNU]",re.I)             # <<<<<<<<<<<<<<
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]
 * gcconpt = re.compile("G|C",re.I)
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_compile); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_I); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  __pyx_t_5 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
      __pyx_t_5 = 1;
    }
  }
  __pyx_t_6 = PyTuple_New(2+__pyx_t_5); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  if (__pyx_t_2) {
    __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2); __pyx_t_2 = NULL;
  }
  __Pyx_INCREF(__pyx_kp_s_ACGTNU);
  __Pyx_GIVEREF(__pyx_kp_s_ACGTNU);
  PyTuple_SET_ITEM(__pyx_t_6, 0+__pyx_t_5, __pyx_kp_s_ACGTNU);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_6, 1+__pyx_t_5, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_6, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_nuclpt, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 47; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":48
 * import re
 * nuclpt  = re.compile("[^ACGTNU]",re.I)
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]             # <<<<<<<<<<<<<<
 * gcconpt = re.compile("G|C",re.I)
 * cpg     = re.compile("CG",re.I)
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_compile); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple_, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_reppt, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":49
 * nuclpt  = re.compile("[^ACGTNU]",re.I)
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]
 * gcconpt = re.compile("G|C",re.I)             # <<<<<<<<<<<<<<
 * cpg     = re.compile("CG",re.I)
 * 
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_compile); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_I); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = NULL;
  __pyx_t_5 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_6))) {
    __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_6);
    if (likely(__pyx_t_3)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
      __Pyx_INCREF(__pyx_t_3);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_6, function);
      __pyx_t_5 = 1;
    }
  }
  __pyx_t_2 = PyTuple_New(2+__pyx_t_5); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  if (__pyx_t_3) {
    __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3); __pyx_t_3 = NULL;
  }
  __Pyx_INCREF(__pyx_kp_s_G_C_2);
  __Pyx_GIVEREF(__pyx_kp_s_G_C_2);
  PyTuple_SET_ITEM(__pyx_t_2, 0+__pyx_t_5, __pyx_kp_s_G_C_2);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_2, 1+__pyx_t_5, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_2, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_gcconpt, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 49; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":50
 * reppt   = re.compile("N|n|a|c|g|t") # or [Nnacgt]
 * gcconpt = re.compile("G|C",re.I)
 * cpg     = re.compile("CG",re.I)             # <<<<<<<<<<<<<<
 * 
 * hmutidx = {"AG":0,
 */
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_compile); if (unlikely(!__pyx_t_2)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_re); if (unlikely(!__pyx_t_6)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_4 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_I); if (unlikely(!__pyx_t_4)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_4);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = NULL;
  __pyx_t_5 = 0;
  if (CYTHON_COMPILING_IN_CPYTHON && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_6)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_6);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
      __pyx_t_5 = 1;
    }
  }
  __pyx_t_3 = PyTuple_New(2+__pyx_t_5); if (unlikely(!__pyx_t_3)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_3);
  if (__pyx_t_6) {
    __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_6); __pyx_t_6 = NULL;
  }
  __Pyx_INCREF(__pyx_n_s_CG);
  __Pyx_GIVEREF(__pyx_n_s_CG);
  PyTuple_SET_ITEM(__pyx_t_3, 0+__pyx_t_5, __pyx_n_s_CG);
  __Pyx_GIVEREF(__pyx_t_4);
  PyTuple_SET_ITEM(__pyx_t_3, 1+__pyx_t_5, __pyx_t_4);
  __pyx_t_4 = 0;
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_cpg, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 50; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":52
 * cpg     = re.compile("CG",re.I)
 * 
 * hmutidx = {"AG":0,             # <<<<<<<<<<<<<<
 * 		"TC":0, # AT_Transitions
 * 		"AC":1, # AT_Transversions
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AG, __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TC, __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AC, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AT, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TA, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TG, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CT, __pyx_int_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_GA, __pyx_int_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CA, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CG, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_GC, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_GT, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hmutidx, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":68
 * 
 * # 1.
 * hrc = {'A':'T',             # <<<<<<<<<<<<<<
 * 		'a':'T',
 * 		'T':'A',
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_A, __pyx_n_s_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_a, __pyx_n_s_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_T, __pyx_n_s_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_t, __pyx_n_s_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_U, __pyx_n_s_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_u, __pyx_n_s_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_C, __pyx_n_s_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_c, __pyx_n_s_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_G, __pyx_n_s_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_g, __pyx_n_s_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_N, __pyx_n_s_N) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_n, __pyx_n_s_N) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hrc, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 68; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":81
 * 		'n':'N',
 * 		}
 * hnuclidx = {'A':0,             # <<<<<<<<<<<<<<
 * 		'a':0,
 * 		'C':1,
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_A, __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_a, __pyx_int_0) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_C, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_c, __pyx_int_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_G, __pyx_int_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_g, __pyx_int_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_T, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_t, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_U, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_u, __pyx_int_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_N, __pyx_int_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_n, __pyx_int_4) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CG, __pyx_int_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_cG, __pyx_int_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_cg, __pyx_int_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Cg, __pyx_int_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hnuclidx, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 81; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":98
 * 		'Cg':5,
 * 		}
 * hrfam = {             # <<<<<<<<<<<<<<
 * 		"Cis-reg_leader":"Cis-reg",
 * 		"Intron":"Intron",
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg_leader, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Intron, __pyx_n_s_Intron) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_antitoxin, __pyx_n_s_antitoxin) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_tRNA, __pyx_n_s_tRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_snRNA_splicing, __pyx_n_s_snRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_miRNA, __pyx_n_s_miRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_sRNA, __pyx_n_s_sRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_lncRNA, __pyx_n_s_lncRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg_thermoregulator, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Gene_snRNA_snoRNA_HACA_box, __pyx_n_s_snoRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg_frameshift_element, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_snRNA_snoRNA_scaRNA, __pyx_n_s_snoRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_CRISPR, __pyx_n_s_CRISPR) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg_IRES, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_antisense, __pyx_n_s_antisense) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_ribozyme, __pyx_n_s_ribozyme) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Cis_reg_riboswitch, __pyx_kp_s_Cis_reg) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_Gene_snRNA_snoRNA_CD_box, __pyx_n_s_snoRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene, __pyx_n_s_Gene) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_rRNA, __pyx_n_s_rRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Gene_snRNA, __pyx_n_s_snRNA) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hrfam, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 98; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":127
 * """
 * 
 * hgeneclass = {             # <<<<<<<<<<<<<<
 *         "3prime_overlapping_ncrna":"lnc",            # Long non-coding RNA genes
 *         "antisense":"lnc",                           # Long non-coding RNA genes
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s_3prime_overlapping_ncrna, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_antisense, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_C_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_C_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_D_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_J_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_J_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_V_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_V_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_known_ncrna, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_lincRNA, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_miRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_misc_RNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Mt_rRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Mt_tRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_non_coding, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_polymorphic_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_processed_transcript, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_protein_coding, __pyx_n_s_coding) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_rRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_sense_intronic, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_sense_overlapping, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_snoRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_snRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TEC, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_unitary_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_unprocessed_pseudoge, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_translated_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_translated_unprocessed_pseudogen, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_C_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_J_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_V_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_IG_V_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_known_ncrna, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_lincRNA, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_miRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_misc_RNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Mt_rRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_Mt_tRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_non_coding, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_polymorphic_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_processed_transcript, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_protein_coding, __pyx_n_s_coding) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_rRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_sense_intronic, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_sense_overlapping, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_snoRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_snRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TEC, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_unitary_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transcribed_unprocessed_pseudoge, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_translated_processed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_translated_unprocessed_pseudogen, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_C_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_D_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_J_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_J_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_V_gene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_TR_V_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_unitary_pseudogene, __pyx_n_s_imm) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_unprocessed_pseudogene, __pyx_n_s_pseudo) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_scaRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_sRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ribozyme, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_macro_lncRNA, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_vaultRNA, __pyx_n_s_srna) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_bidirectional_promoter_lncrna, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s__2, __pyx_n_s_unknown) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ncRNA, __pyx_n_s_lnc) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_transposable_element, __pyx_n_s_transposable) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hgeneclass, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 127; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":208
 * 
 * ##=== IUPAC
 * hiupac= {             # <<<<<<<<<<<<<<
 * 		'A'    :'A',
 * 		'C'    :'C',
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_A, __pyx_n_s_A) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_C, __pyx_n_s_C) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_G, __pyx_n_s_G) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_T, __pyx_n_s_T) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_U, __pyx_n_s_U) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AG, __pyx_n_s_R) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CT, __pyx_n_s_Y) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CU, __pyx_n_s_Y) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_GT, __pyx_n_s_K) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_GU, __pyx_n_s_K) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AC, __pyx_n_s_M) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CG, __pyx_n_s_S) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AT, __pyx_n_s_W) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AU, __pyx_n_s_W) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CGT, __pyx_n_s_B) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_CGU, __pyx_n_s_B) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AGT, __pyx_n_s_D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_AGU, __pyx_n_s_D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ACT, __pyx_n_s_H) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ACU, __pyx_n_s_H) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ACG, __pyx_n_s_V) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ACGU, __pyx_n_s_N) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_n_s_ACGT, __pyx_n_s_N) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_t_1, __pyx_kp_s__2, __pyx_kp_s__2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_hiupac, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 208; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "rblib/defs.pyx":1
 * # -*- coding: UTF-8 -*-             # <<<<<<<<<<<<<<
 * # Degenerate base
 * hchr= {"chr1":"1",
 */
  __pyx_t_1 = PyDict_New(); if (unlikely(!__pyx_t_1)) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 1; __pyx_clineno = __LINE__; goto __pyx_L1_error;}
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_4);
  __Pyx_XDECREF(__pyx_t_6);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init rblib.defs", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init rblib.defs");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* --- Runtime support code --- */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if CYTHON_COMPILING_IN_CPYTHON
    result = PyDict_GetItem(__pyx_d, name);
    if (likely(result)) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = (start + end) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        __pyx_d,      /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = py_line;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

#define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)       \
    {                                                                     \
        func_type value = func_value;                                     \
        if (sizeof(target_type) < sizeof(func_type)) {                    \
            if (unlikely(value != (func_type) (target_type) value)) {     \
                func_type zero = 0;                                       \
                if (is_unsigned && unlikely(value < zero))                \
                    goto raise_neg_overflow;                              \
                else                                                      \
                    goto raise_overflow;                                  \
            }                                                             \
        }                                                                 \
        return (target_type) value;                                       \
    }

#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
 #endif
#endif

static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +(((PyLongObject*)x)->ob_digit[0]));
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, -(sdigit) ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(long, long, PyLong_AsLong(x))
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT(long, PY_LONG_LONG, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned long, PyLong_AsUnsignedLong(x))
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
            }
        } else {
#if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
 #if CYTHON_USE_PYLONG_INTERNALS
            switch (Py_SIZE(x)) {
                case  0: return 0;
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +(((PyLongObject*)x)->ob_digit[0]));
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, -(sdigit) ((PyLongObject*)x)->ob_digit[0]);
            }
 #endif
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT(int, long, PyLong_AsLong(x))
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT(int, PY_LONG_LONG, PyLong_AsLongLong(x))
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_Int(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_Int(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else
        if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else
        return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
    } else
#endif
#if !CYTHON_COMPILING_IN_PYPY
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_Int(PyObject* x) {
  PyNumberMethods *m;
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return Py_INCREF(x), x;
  m = Py_TYPE(x)->tp_as_number;
#if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
#else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b)))
      return PyInt_AS_LONG(b);
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_COMPILING_IN_CPYTHON && PY_MAJOR_VERSION >= 3
     #if CYTHON_USE_PYLONG_INTERNALS
       switch (Py_SIZE(b)) {
       case -1: return -(sdigit)((PyLongObject*)b)->ob_digit[0];
       case  0: return 0;
       case  1: return ((PyLongObject*)b)->ob_digit[0];
       }
     #endif
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
