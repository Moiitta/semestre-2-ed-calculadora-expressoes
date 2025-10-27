CC = clang
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c calculadora.c pilha.c fila.c
OUT = ./output/programa

TEST_SRC = tests.c calculadora.c pilha.c fila.c unity/unity.c
TEST_OUT = ./output/testes

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

run: all
	./$(OUT)

# Testes
test:
	$(CC) $(TEST_SRC) -Iunity -o $(TEST_OUT) $(CFLAGS)
	./$(TEST_OUT)

clean:
	rm -f $(OUT) $(TEST_OUT)
