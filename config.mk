CC ?= gcc
CFLAGS ?= -Wall -Wextra -O3 -march=native
LDFLAGS ?= -s

TARGET ?= AoC2015-C
PREFIX ?= $(HOME)/.local
BINDIR ?= $(PREFIX)/bin