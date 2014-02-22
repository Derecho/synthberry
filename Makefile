CXX=g++
CPPFLAGS=-std=c++11
HEADERS=-Isrc -Iexternals/libserial/src
LDFLAGS=-Lsrc -Lexternals/libserial/src/.libs
LDLIBS=-lserial

SRCS=$(wildcard src/*.cpp)
OBJS=$(subst src,obj,$(subst .cpp,.o,$(SRCS)))

all: libserial $(OBJS)
	mkdir -p bin
	#$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/*.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o bin/synthberry obj/main.o obj/note.o obj/notes.o obj/serialmidi.o

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
