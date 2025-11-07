#!/bin/bash

set -e

EXTERNAL_LIBS="src/external/"

echo "Checking external libraries..."

echo ""

echo "Building md5 library..."
gcc -Wall -Wextra -O3 -march=native -funroll-loops -fomit-frame-pointer -c $EXTERNAL_LIBS/md5/md5.c -o $EXTERNAL_LIBS/md5/md5.o
ar rcs $EXTERNAL_LIBS/md5/libmd5.a $EXTERNAL_LIBS/md5/md5.o
echo "md5 library built successfully."

echo ""

echo "Checking for pcre2 library..."
if ldconfig -p | grep -q libpcre2-8; then
  echo "pcre2 library found."
else
  echo "pcre2 library not found. Please install it using your package manager."
  exit 1
fi

echo ""