#!/bin/bash

cd $PWD/external/libplist
./autogen.sh
make
make DESTDIR=$PWD/DESTDIR install
cp DESTDIR/usr/local/lib/*.dylib $PWD/../
ln -sf $PWD/../libplist++-2.0.dylib  $PWD/../libplist++.dylib
ln -sf $PWD/../libplist-2.0.dylib  $PWD/../libplist.dylib
