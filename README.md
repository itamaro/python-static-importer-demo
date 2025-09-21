# Python Static Extension Importer Demo

## Build

To use a custom Python build (e.g., if you built Python from source), set the `PYTHON_HOME` environment variable to the installation prefix of your custom Python build before running `make`.

For example:

```bash
export PYTHON_HOME=/path/to/your/custom/python/installation
make
```

If `PYTHON_HOME` is not set, the Makefile will attempt to use `pkg-config` to find Python headers and libraries.

The demo currently requires a custom-built CPython 3.15 from https://github.com/itamaro/cpython/tree/gh-116146-create-builtin-initfunc

## Run

After building, you can run the executable from the project root:

```bash
./demo script.py
```
