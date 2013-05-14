OBJ = sudoku.o
CFLAGS = -Wall -Wextra -std=c99

all: bin

bin: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o bin

clean:
	rm bin $(OBJ)