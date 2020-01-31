DEBUG=yes
ifeq ($(DEBUG), yes)
	FLAGS=-Wall -g
else
	FLAGS=-Wall
endif

main: sudoku.o main.o 
	gcc $(FLAGS) doto/sudoku.o doto/main.o -o bin/main
	
sudoku.o: sudoku.c sudoku.h
	gcc $(FLAGS) -c sudoku.c -o doto/sudoku.o

main.o: main.c sudoku.h
	gcc $(FLAGS) -c main.c -o doto/main.o

cac40: main clean

clean:
	rm -rf doto/*.o