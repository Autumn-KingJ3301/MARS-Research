CC ?= cc
CPPFLAGS += -Iinclude
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS += -lm
SOURCES := $(wildcard src/*.c)
HEADERS := $(wildcard include/*.h)

.PHONY: all demo test clean
all: build/basic build/continuity
build:
	mkdir -p build
build/basic: examples/basic.c $(SOURCES) $(HEADERS) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(SOURCES) $(LDLIBS) -o $@
build/continuity: examples/continuity.c $(SOURCES) $(HEADERS) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(SOURCES) $(LDLIBS) -o $@
build/test_primitives: tests/test_primitives.c $(SOURCES) $(HEADERS) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(SOURCES) $(LDLIBS) -o $@
demo: all
	./build/basic
	./build/continuity
test: build/test_primitives
	./build/test_primitives
clean:
	rm -rf build
