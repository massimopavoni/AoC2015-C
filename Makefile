-include config.mk

ROUT = $(wildcard src/resources/*.out)
RINS = $(wildcard src/resources/*.in)
RSRC = src/resources.c

SRCS = $(RSRC) $(filter-out $(RSRC), $(wildcard src/*.c))
OBJS = $(SRCS:src/%.c=bin/%.o)

all: $(RSRC) $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) $^ $(LDFLAGS) -o bin/$@

$(RSRC): $(ROUT) $(RINS)
	@{ \
		echo '#include "resources.h"'; \
		echo ''; \
		echo 'const char* RESOURCES[] = {'; \
		for res in $^; do \
			echo "  \"$$(awk '{ gsub(/\\/,"\\\\"); gsub(/"/,"\\\""); printf "%s\\n", $$0 }' "$$res" | tr -d '\n')\","; \
		done; \
		echo '};'; \
	} > $@

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp bin/$< $(BINDIR)/

clean:
	rm -rf bin
	rm $(RSRC)
