#! /bin/bash

ROOT=$PWD

LIBPATH="/usr/lib"
LIBDIR="lib"

URL="https://data.iana.org/time-zones/releases/tzcode2025a.tar.gz"

if [ ! -f "$ROOT/External/tzcode.tar.gz" ]; then
    curl -L -o "$ROOT/External/tzcode.tar.gz" "$URL"
    mkdir $ROOT/External/tzcode
    cd $ROOT/External/tzcode
    tar -xpvf $ROOT/External/tzcode.tar.gz
fi

# this could be a shit solution
if [ -d "/usr/lib64" ]; then
    LIBDIR="lib64"
fi

if [ ! -f "/usr/$LIBDIR/libkqueue.a" ]; then
    cd $ROOT/External/libkqueue
    cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=$LIBDIR . -B build
    cd build
    make
    sudo make install
fi

if [ ! -f "/usr/$LIBDIR/libCoreFoundation.so" ]; then
    echo $LIBDIR
    cd $ROOT/External/OpenCFLite
    ./configure --prefix=/usr --libdir="/usr/$LIBDIR" --with-tz-includes="$ROOT/External/tzcode"
    make
    sudo make install
fi
