#!/bin/sh

all: format

format: format.c
	clang -g -Wall -pedantic -std=c99 -o format format.c

clean:
	rm -f format *~