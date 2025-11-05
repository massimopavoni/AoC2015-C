#!/bin/bash

set -e

EXTERNAL_LIBS="src/external/"

echo "Fetching external libraries..."

echo "Building md5 library..."
gcc -Wall -Wextra -O3 -march=native -funroll-loops -fomit-frame-pointer -c $EXTERNAL_LIBS/md5/md5.c -o $EXTERNAL_LIBS/md5/md5.o
ar rcs $EXTERNAL_LIBS/md5/libmd5.a $EXTERNAL_LIBS/md5/md5.o
echo "md5 library built successfully."