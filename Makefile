CXX=g++
CPPFLAGS=-std=c++11 -Wall
HEADERS=-Isrc -Iexternals/libserial/src
LDFLAGS=-Lsrc -Lexternals/libserial/src/.libs
LDLIBS=-lserial

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))

.PHONY: all debug rpi clean distclean

all: CPPFLAGS+= -O2
all: libserial $(OBJS)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/*.o
	strip bin/synthberry

debug: CPPFLAGS+= -D DEBUG -g
debug: all

rpi: export PATH:=$(shell pwd)/externals/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$(PATH)
rpi: CC=arm-linux-gnueabihf-gcc
rpi: CXX=arm-linux-gnueabihf-g++
rpi: CROSS_COMPILE=arm-linux-gnueabihf
rpi: CPPFLAGS+= -O2
rpi: export ARCH=arm
rpi: libserial-rpi $(OBJS)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/*.o
	arm-linux-gnueabihf-strip bin/synthberry

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

libserial:
	cd externals/libserial; ./configure
	make -C externals/libserial
	touch $@

libserial-rpi:
	cd externals/libserial; ./configure --host=$(CROSS_COMPILE)
	make -C externals/libserial
	touch $@

clean:
	rm -rf bin obj

distclean: clean
	make -C externals/libserial distclean
	rm -f libserial libserial-rpi
