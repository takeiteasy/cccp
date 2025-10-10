ifeq ($(OS),Windows_NT)
	LIBEXT=dll
	PROGEXT=.exe
	LINKER:=-lgdi32	include windows.Makefile
else
	UNAME:=$(shell uname -s)
	PROGEXT=
	ifeq ($(UNAME),Darwin)
		LIBEXT=dylib
		LINKER:=-lpthread -framework Cocoa
	else ifeq ($(UNAME),Linux)
		LIBEXT=so
		LINKER:=-lpthread -lX11 -lm
	else
		$(error OS not supported by this Makefile)
	endif
endif

CFLAGS:=-g -Wall -Wno-missing-braces -Ideps -DPAUL_MATH_NO_MATRICES
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

veryclean:
	$(RM) $(OBJS)
	$(RM) -r $(BIN)/**

docs:
	@headerdoc2html src/cccp.h -o docs/; \
	mv docs/cccp_h/*.html docs/; \
	rm -rf docs/cccp_h

FORCE: ;

$(BIN)/%.$(LIBEXT): $(SCENES)/%.c FORCE | $(BIN)
	$(CC) $(LINKER) -Isrc -shared -fpic $(CFLAGS) -o $@ src/cccp.c $<

scenes: $(TARGETS)

all: veryclean $(OUT) scenes clean

.PHONY: clean veryclean all scenes run docs