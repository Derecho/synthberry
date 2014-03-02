CC=gcc
CXX=g++
CPPFLAGS=-std=c++11 -Wall
HEADERS=-Isrc -Iexternals/libserial/src -Iexternals/alsa-lib/include
LDFLAGS=-Lsrc -Lexternals/libserial/src/.libs -Lexternals/alsa-lib/src/.libs
LDLIBS=-lserial -lasound

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))

.PHONY: all rpi debug debug-rpi cross-compile help clean distclean

all: CPPFLAGS+= -O2
all: bin/synthberry
	strip bin/synthberry

debug: CPPFLAGS+= -D DEBUG -g3 -ggdb
debug: bin/synthberry

rpi: CPPFLAGS+= -O2
rpi: cross-compile bin/synthberry
	$(CROSS_COMPILE)-strip bin/synthberry

debug-rpi: CPPFLAGS+= -D DEBUG -g3 -ggdb
debug-rpi: cross-compile bin/synthberry

# Temporary
alsapoc: CPPFLAGS+= -D DEBUG -g3 -ggdb
alsapoc: bin/alsapoc

# Temporary
alsapoc-rpi: CPPFLAGS+= -D DEBUG -g3 -ggdb
alsapoc-rpi: cross-compile bin/alsapoc

cross-compile:
	$(eval PATH:=$(shell pwd)/externals/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$(PATH))
	$(eval CROSS_COMPILE=arm-linux-gnueabihf)
	$(eval CC=$(CROSS_COMPILE)-gcc)
	$(eval CXX=$(CROSS_COMPILE)-g++)
	$(eval ARCH=arm)

bin/synthberry: libserial libasound $(OBJS)
	mkdir -p bin
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $(OBJS)

# Temporary
bin/alsapoc: libserial libasound
	mkdir -p bin obj
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(HEADERS) -o obj/alsapoc.o -c poc/alsapoc.cpp
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ obj/alsapoc.o

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(HEADERS) -o $@ -c $<

libserial:
	cd externals/libserial; ./configure --host=$(CROSS_COMPILE)
	make -C externals/libserial
	touch $@

libasound:
	cd externals/alsa-lib; libtoolize --force --copy --automake
	cd externals/alsa-lib; aclocal
	cd externals/alsa-lib; autoheader
	cd externals/alsa-lib; automake --foreign --copy --add-missing
	cd externals/alsa-lib; autoconf
	cd externals/alsa-lib; ./configure --host=$(CROSS_COMPILE) --disable-python
	make -C externals/alsa-lib
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
	-make -C externals/libserial distclean
	-make -C externals/alsa-lib distclean
	rm -f libserial libasound
