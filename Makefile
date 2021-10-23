SRC_FILE = src/manifest.m
COMPILE_ARGS = -std=c99 -Wall -framework Carbon
CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

build:
	gcc $(COMPILE_ARGS) $(SRC_FILE) -o bin/lime
