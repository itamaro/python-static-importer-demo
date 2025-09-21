#include <Python.h>
#include <cstdio>
#include <iostream>

extern "C"
{
  PyMODINIT_FUNC PyInit_static_utils(void);
}

int main(int argc, char *argv[])
{
  PyStatus status;
  PyConfig config;
  PyConfig_InitPythonConfig(&config);

  /* optional but recommended */
  status = PyConfig_SetBytesString(&config, &config.program_name, argv[0]);
  if (PyStatus_Exception(status))
  {
    return 1;
  }
  status = PyConfig_SetBytesArgv(&config, argc, argv);
  if (PyStatus_Exception(status))
  {
    return 1;
  }
  status = PyConfig_Read(&config);
  if (PyStatus_Exception(status))
  {
    return 1;
  }

  PyImport_AppendInittab("static_utils", PyInit_static_utils);

  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status))
  {
    return 1;
  }
  PyConfig_Clear(&config);

  // Add current directory to Python path to find our module
  PyRun_SimpleString("import sys\nsys.path.append('.')");

  // Import static_extension_importer and get StaticExtensionImporter class
  PyObject *pModule = PyImport_ImportModule("static_extension_importer");
  if (pModule == NULL)
  {
    PyErr_Print();
    fprintf(stderr, "Error: Could not import static_extension_importer\n");
    return 1;
  }
  PyObject *pClass = PyObject_GetAttrString(pModule, "StaticExtensionImporter");
  if (pClass == NULL)
  {
    PyErr_Print();
    fprintf(stderr, "Error: Could not get StaticExtensionImporter class\n");
    Py_DECREF(pModule);
    return 1;
  }

  // Get sys.meta_path and append StaticExtensionImporter
  PyObject *sys_module = PyImport_ImportModule("sys");
  if (sys_module == NULL)
  {
    PyErr_Print();
    fprintf(stderr, "Error: Could not import sys module\n");
    Py_DECREF(pModule);
    Py_DECREF(pClass);
    return 1;
  }
  PyObject *meta_path = PyObject_GetAttrString(sys_module, "meta_path");
  if (meta_path == NULL)
  {
    PyErr_Print();
    fprintf(stderr, "Error: Could not get sys.meta_path\n");
    Py_DECREF(sys_module);
    Py_DECREF(pModule);
    Py_DECREF(pClass);
    return 1;
  }

  if (PyList_Append(meta_path, pClass) == -1)
  {
    PyErr_Print();
    fprintf(stderr, "Error: Could not append StaticExtensionImporter to sys.meta_path\n");
    Py_DECREF(meta_path);
    Py_DECREF(sys_module);
    Py_DECREF(pModule);
    Py_DECREF(pClass);
    return 1;
  }

  Py_DECREF(meta_path);
  Py_DECREF(sys_module);
  Py_DECREF(pModule);
  Py_DECREF(pClass);

  return Py_RunMain();
}
