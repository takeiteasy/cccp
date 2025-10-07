ifeq ($(OS),Windows_NT)
	LIBEXT=dll
	PROGEXT=.exe
	CFLAGS:=-g -Wall -Wno-missing-braces -fenable-matrix -Ideps
	LINKER:=-lgdi32	include windows.Makefile
else
	UNAME:=$(shell uname -s)
	PROGEXT=
	ifeq ($(UNAME),Darwin)
		LIBEXT=dylib
		CFLAGS:=-g -Wall -Wno-missing-braces -fenable-matrix -Ideps
		LINKER:=-lpthread -framework Cocoa

	else ifeq ($(UNAME),Linux)
		LIBEXT=so
		CFLAGS:=-g -Wall -Wno-missing-braces -fenable-matrix -Ideps
		LINKER:=-lpthread -lX11 -lm
	else
		$(error OS not supported by this Makefile)
	endif
endif

BIN := build
SRCS:=$(filter-out src/cccp.c, $(wildcard src/*.c))
OBJS:=$(SRCS:.c=.o)
OUT:=$(BIN)/cccp$(PROGEXT)

SCENES:=examples
TARGETS:=$(foreach file,$(foreach src,$(wildcard $(SCENES)/*.c),$(notdir $(src))),$(patsubst %.c,$(BIN)/%.$(LIBEXT),$(file)))

default: $(OUT) clean

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(LINKER) -o $@ $^

run:
	./cccp$(PROGEXT)

clean:
	$(RM) $(OBJS)

veryclean: clean
	$(RM) -r $(BIN)/**

FORCE: ;

$(BIN)/%.$(LIBEXT): $(SCENES)/%.c FORCE | $(BIN)
	$(CC) $(LINKER) -Isrc -shared -fpic $(CFLAGS) -o $@ src/cccp.c $<

scenes: $(TARGETS)

all: $(OUT) scenes

.PHONY: clean veryclean all scenes run