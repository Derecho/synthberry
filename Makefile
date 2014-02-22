CXX=g++
CPPFLAGS=-Iexternals/libserial/src
LDFLAGS=-Lexternals/libserial/src/.libs
LDLIBS=-lserial

all: test

test: libserial
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/test src/test.cpp

libserial:
	cd externals/libserial; ./configure
	make -C externals/libserial
	touch $@

clean:
	rm -rf bin obj

distclean: clean
	make -C externals/libserial distclean
	rm libserial
