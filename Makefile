CXX=g++
CPPFLAGS=-std=c++11 -Wall
HEADERS=-Isrc -Iexternals/libserial/src
LDFLAGS=-Lsrc -Lexternals/libserial/src/.libs
LDLIBS=-lserial

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))

.PHONY: all rpi debug debug-rpi cross-compile help clean distclean

all: CPPFLAGS+= -O2
all: bin/synthberry
	strip bin/synthberry

debug: CPPFLAGS+= -D DEBUG -g
debug: bin/synthberry

rpi: CPPFLAGS+= -O2
rpi: cross-compile bin/synthberry
	$(CROSS_COMPILE)-strip bin/synthberry

debug-rpi: CPPFLAGS+= -D DEBUG -g
debug-rpi: cross-compile bin/synthberry

cross-compile:
	$(eval PATH:=$(shell pwd)/externals/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$(PATH))
	$(eval CC=arm-linux-gnueabihf-gcc)
	$(eval CXX=arm-linux-gnueabihf-g++)
	$(eval CROSS_COMPILE=arm-linux-gnueabihf)
	$(eval ARCH=arm)

bin/synthberry: libserial $(OBJS)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/*.o

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

libserial:
	cd externals/libserial; ./configure --host=$(CROSS_COMPILE)
	make -C externals/libserial
	touch $@

help:
	@echo "Possible targets:"
	@echo "	all 			Build synthberry natively"
	@echo "	debug 			Build synthberry natively with debugging options"
	@echo "	rpi 			Cross-compile synthberry for the Raspberry Pi"
	@echo "	debug-rpi 		Cross-compile synthberry for the Raspberry Pi with debugging options"

clean:
	rm -rf bin obj

distclean: clean
	make -C externals/libserial distclean
	rm -f libserial
