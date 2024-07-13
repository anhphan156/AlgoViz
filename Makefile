CC := gcc
CFLAGS := -g
LDFLAGS := -lm -lxkbcommon -lraylib

SRCDIR := src
BUILDDIR := build
INCDIR := include

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

EXECUTABLE := out

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $^ -o $@

run:
	./out

leak:
	valgrind --leak-check=full ./out

clean:
	rm -rf $(BUILDDIR)/%.o $(EXECUTABLE)
