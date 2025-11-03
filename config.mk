# Compiler
CC ?= gcc

CFLAGS ?= -Wall -Wextra -O3 -march=native
CFLAGS += -Isrc/include

# Linker
LDFLAGS ?= -s

# Target
TARGET ?= AoC2015-C
BINDIR ?= $(HOME)/.local/bin