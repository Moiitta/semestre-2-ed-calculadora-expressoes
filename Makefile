CC = clang
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c pilha.c fila.c
OUT = programa

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

run: all
	./$(OUT)
