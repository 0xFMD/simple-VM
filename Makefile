CC = gcc
CFLAGS = -Wall
PREFIX = zvm
SRC = src/$(PREFIX).c src/$(PREFIX)_instruction.c src/$(PREFIX)_exception.c src/$(PREFIX)_io.c
OUT = $(PREFIX)

all: $(OUT)

$(OUT):
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean
