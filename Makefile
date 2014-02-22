CXX=g++
CPPFLAGS=-std=c++11 -Wall
HEADERS=-Isrc -Iexternals/libserial/src
LDFLAGS=-Lsrc -Lexternals/libserial/src/.libs
LDLIBS=-lserial

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))

all: CPPFLAGS+= -O2
all: libserial $(OBJS)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/*.o
	strip bin/synthberry

debug: CPPFLAGS+= -D DEBUG -g
debug: all

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

libserial:
	cd externals/libserial; ./configure
	make -C externals/libserial
	touch $@

clean:
	rm -rf bin obj

distclean: clean
	make -C externals/libserial distclean
	rm libserial
