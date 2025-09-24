CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -std=c99 -pedantic -g
SRC = main.c src/tp1.c src/aux.c src/lista.c src/pila.c src/cola.c
BIN = main

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

run: $(BIN)
	./$(BIN) $(ARGS)

valgrind: $(BIN)
	valgrind --leak-check=full --track-origins=yes ./$(BIN) $(ARGS)

clean:
	rm -f $(BIN)