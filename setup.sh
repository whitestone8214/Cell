#!/bin/bash


if (test "$1" = "build"); then
	gcc -I. cell.c -shared -o libcell.so
elif (test "$1" = "install"); then
	cp -f cell.h /usr/include/ || exit 1
	cp -f libcell.so /lib/ || exit 1
	cp -f cell.pc /lib/pkgconfig/ || exit 1
fi