# Compiler
CC ?= gcc

# Optimizations
CFLAGS ?= -Wall -Wextra -O3 -march=native -funroll-loops -fomit-frame-pointer

# Project headers
CFLAGS += -Isrc/include

# OpenMP support
CFLAGS += -fopenmp

# External libraries
CFLAGS += -Isrc/external/md5

# Linker
LDFLAGS ?= -s
LDFLAGS += -fopenmp

# External libraries
LDFLAGS += -lcrypto

# Target
TARGET ?= AoC2015-C
BINDIR ?= $(HOME)/.local/bin