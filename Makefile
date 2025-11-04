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
			echo "  \"$$(perl -0777 -pe 's/\\/\\\\/g; s/"/\\"/g; chomp; s/\n/\\n/g' "$$res")\","; \
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
