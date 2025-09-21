#include <Python.h>

// Definition for the staticmod.say_hello function
static PyObject* staticmod_say_hello(PyObject* self, PyObject* args) {
    printf("Hello from staticmod!\n");
    Py_RETURN_NONE;
}

// Method definition object for the staticmod module
static PyMethodDef Staticmod_methods[] = {
    {"say_hello", staticmod_say_hello, METH_NOARGS, "Says hello from staticmod."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

static PyModuleDef_Slot Staticmod_slots[] = {
    {Py_mod_gil, Py_MOD_GIL_NOT_USED},
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
    {0, NULL}
};

// Module definition object for the staticmod module
static struct PyModuleDef staticmodmodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "staticmod",
    .m_doc = NULL,
    .m_size = 0,
    .m_methods = Staticmod_methods,
    .m_slots = Staticmod_slots,
};

// Function to initialize the staticmod module
PyMODINIT_FUNC PyInit_staticmod(void) {
    return PyModuleDef_Init(&staticmodmodule);
}
