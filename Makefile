CXX=g++
LDLIBS=-lserial

all: test

test:
	mkdir -p bin
	$(CXX) $(LDLIBS) -o bin/test src/test.cpp

clean:
	rm -rf bin obj

distclean: clean
