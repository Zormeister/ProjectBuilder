#!/bin/bash

cd $PWD/external/libplist
./autogen.sh
make
make DESTDIR=$PWD/DESTDIR install
cp DESTDIR/usr/local/lib/*.dylib $PWD/../
