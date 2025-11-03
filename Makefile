-include config.mk

# Resources
ROUT = $(wildcard src/resources/*.out)
RINS = $(wildcard src/resources/*.in)
RSRC = src/resources.c

# Sources and objects
SRCS = $(RSRC) $(filter-out $(RSRC), $(wildcard src/*.c))
OBJS = $(SRCS:src/%.c=bin/%.o)

# Build rules
all: $(RSRC) $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) $^ $(LDFLAGS) -o bin/$@

# Resources embedding
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
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp bin/$< $(BINDIR)/

clean:
	rm -rf bin
	rm $(RSRC)
