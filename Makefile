ifeq ($(OS),Windows_NT)
	include windows.Makefile
else
	UNAME:=$(shell uname -s)
	ifeq ($(UNAME),Darwin)
		include macos.Makefile
	else ifeq ($(UNAME),Linux)
		include linux.Makefile
	else
		$(error OS not supported by this Makefile)
	endif
endif

build:
	$(CC) -g -o cccp$(PROGEXT) src/*.c -Ideps -fenable-matrix -lpthread -framework Cocoa

run:
	./cccp$(PROGEXT)