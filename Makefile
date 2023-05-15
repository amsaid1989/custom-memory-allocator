CC=clang
CFLAGS=-g -Wall -Werror -pedantic
SRC=*.c
OUT=main

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
