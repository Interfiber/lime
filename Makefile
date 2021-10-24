SRC_FILE = src/manifest.m
COMPILE_ARGS = -std=c99 -Wall -framework Carbon -framework Cocoa

build:
	gcc $(COMPILE_ARGS) $(SRC_FILE) -o bin/lime

