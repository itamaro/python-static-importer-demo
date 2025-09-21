#include <string>
#include <unordered_map>
#include "Python.h"

extern "C" {
    PyMODINIT_FUNC PyInit_staticmod(void);
}

typedef PyObject* (*pyinitfunc)();

std::unordered_map<std::string_view, pyinitfunc> _static_extension_info = {
    {"staticmod", PyInit_staticmod},
};

PyDoc_STRVAR(
    create_module_doc,
    "Create a module from the embedded static extension init function\n"
);

static PyObject* create_module(PyObject* self, PyObject* spec) {
    PyObject* name = PyObject_GetAttrString(spec, "name");
    if (name == nullptr) {
        return nullptr;
    }

    const std::string namestr = PyUnicode_AsUTF8(name);
    if (namestr.empty()) {
        Py_DECREF(name);
        return nullptr;
    }

    pyinitfunc initfunc = nullptr;
    if (auto result = _static_extension_info.find(namestr);
        result != _static_extension_info.end()) {
        initfunc = result->second;
    }

    if (initfunc == nullptr) {
        PyErr_SetString(
            PyExc_ImportError, "Module unknown to static extension finder");
        return nullptr;
    }

    return PyImport_CreateModuleFromInitfunc(spec, initfunc);
}

PyDoc_STRVAR(
    check_module_doc,
    "Check if a module is contained in the embedded static extensions map\n"
);

static PyObject* check_module(PyObject* self, PyObject* fullname) {
    if (!PyUnicode_Check(fullname)) {
        PyErr_SetString(PyExc_TypeError, "Expected a unicode object");
        return nullptr;
    }
    const std::string modname = PyUnicode_AsUTF8(fullname);
    if (_static_extension_info.find(modname) != _static_extension_info.end()) {
        Py_INCREF(Py_True);
        return Py_True;
    }
    Py_INCREF(Py_False);
    return Py_False;
}

static PyModuleDef_Slot static_utils_slots[] = {
#ifdef Py_GIL_DISABLED
    {Py_mod_gil, Py_MOD_GIL_NOT_USED},
#endif
    {}
};

static PyMethodDef static_utils_methods[] = {
    {"check_module", check_module, METH_O, check_module_doc},
    {"create_module", create_module, METH_O, create_module_doc},
    {}
};

PyDoc_STRVAR(
    module_doc,
    "Utils for importing modules statically linked into the python binary \n"
);

static struct PyModuleDef static_utils_def {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "static_utils",
    .m_doc = module_doc,
    .m_size = 0,
    .m_methods = static_utils_methods,
    .m_slots = static_utils_slots,
    .m_traverse = nullptr,
    .m_clear = nullptr,
    .m_free = nullptr
};

PyMODINIT_FUNC PyInit_static_utils(void) {
    return PyModuleDef_Init(&static_utils_def);
}
