# Python Static Extension Importer Demo

## Build

To use a custom Python build (e.g., if you built Python from source), run `make` with the appropriate `CXX`, `CXXFLAGS`, and `LDFLAGS` environment variables.

For example:

```bash
export PYTHON_HOME=/path/to/your/custom/python/installation
CXX="clang++ -mmacosx-version-min=14.6 -std=c++20" CXXFLAGS="-I${PYTHON_HOME}/include/python3.15d" LDFLAGS="-L${PYTHON_HOME}/lib -lpython3.15d" make
```

The demo currently requires a custom-built CPython 3.15 from https://github.com/itamaro/cpython/tree/gh-116146-create-builtin-initfunc

## Run

After building, you can run the executable from the project root:

```bash
./demo script.py
```
