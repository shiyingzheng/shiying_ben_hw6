#!/bin/sh

all: format

format: format.c
	clang -o format format.c

clean:
	rm -f format *~