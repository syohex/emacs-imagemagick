UNAME_S=$(shell uname -s)
EMACS_ROOT ?= ../..

CC      = gcc
CXX     = g++
LD      = gcc
CPPFLAGS = -I$(EMACS_ROOT)/src
CFLAGS = -std=gnu99 -ggdb3 -Wall -fPIC $(CPPFLAGS)
CXXFLAGS = -std=gnu++11 -ggdb3 -Wall -fPIC $(CPPFLAGS) $(shell pkg-config --cflags ImageMagick++)
LDFLAGS = $(shell pkg-config --libs ImageMagick++)

.PHONY : format

all: imagemagick-core.so

imagemagick-core.so: imagemagick_core.o imagemagick_wrapper.o
	$(LD) -shared -o $@ $^ $(LDFLAGS)

imagemagick_core.o: imagemagick_core.c
	$(CC) $(CFLAGS) -c -o $@ $<

imagemagick_wrapper.o: imagemagick_wrapper.cpp imagemagick_wrapper.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	-rm -f imagemagick_core.so imagemagick_core.o imagemagick_wrapper.o

format:
	clang-format -i *.c *.cpp *.h
