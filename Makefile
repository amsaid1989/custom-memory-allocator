CC=clang
CFLAGS=-g -Wall -Wextra -Werror -pedantic
SRC=*.c
OUT=main

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
