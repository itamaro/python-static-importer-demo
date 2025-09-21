EXT_SUFFIX = .so

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
