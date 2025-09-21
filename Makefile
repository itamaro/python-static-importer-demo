CXX = clang++ -mmacosx-version-min=14.6 -std=c++20
EXT_SUFFIX = .so
ifeq ($(PYTHON_HOME),)
CXXFLAGS = $(shell pkg-config --cflags python3)
LDFLAGS = $(shell pkg-config --libs python3)
else
CXXFLAGS = -I$(PYTHON_HOME)/include/python3.15
LDFLAGS = -L$(PYTHON_HOME)/lib -lpython3.15
endif

all: demo dynmod$(EXT_SUFFIX)

demo: main.o static_utils.o staticmod.o
	$(CXX) main.o static_utils.o staticmod.o $(LDFLAGS) -o demo

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dynmod$(EXT_SUFFIX): dynmod.o
	$(CXX) dynmod.o -shared -undefined dynamic_lookup -o dynmod$(EXT_SUFFIX)

clean:
	rm -f *.o *.so *.dylib *.pyc demo
	rm -rf __pycache__
