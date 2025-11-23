# Compiler
CC ?= gcc

# Optimizations
CFLAGS ?= -Wall -Wextra -O3 -march=native -funroll-loops -fomit-frame-pointer
# CFLAGS = -g3 -O0 -fno-omit-frame-pointer

# Project headers
CFLAGS += -Isrc/include

# OpenMP support
CFLAGS += -fopenmp

# External libraries
CFLAGS += -Isrc/external/md5

# Linker
LDFLAGS ?= -s
# LDFLAGS = -g3
LDFLAGS += -fopenmp

# External libraries
LDFLAGS += src/external/md5/libmd5.a
LDFLAGS += -lpcre2-8

# Target
TARGET ?= AoC2015-C
BINDIR ?= $(HOME)/.local/bin
