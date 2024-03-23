#!/bin/bash

cd $PWD/libplist
./autogen.sh
make
make DESTDIR=$PWD/DESTDIR install
cp DESTDIR/usr/local/lib/*.dylib ./
