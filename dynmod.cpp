#include <Python.h>

// Our C++ function that will be called from Python
static PyObject* dynmod_add(PyObject* self, PyObject* args)
{
    long a, b;
    if (!PyArg_ParseTuple(args, "ll", &a, &b)) {
        return NULL;
    }
    return PyLong_FromLong(a + b);
}

// Module method table
static PyMethodDef DynmodMethods[] = {
    {"add", dynmod_add, METH_VARARGS, "Add two numbers."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Module definition structure
static struct PyModuleDef dynmod_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "dynmod",
    .m_doc = "A simple example module.",
    .m_size = 0,
    .m_methods = DynmodMethods,
};

// Module initialization function
PyMODINIT_FUNC PyInit_dynmod(void)
{
    return PyModuleDef_Init(&dynmod_module);
}
