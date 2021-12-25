all: link
bin/algorithm.o:
	gcc -c src/algorithm.c -o bin/algorithm.o
bin/io.o:
	gcc -c src/io.c -o bin/io.o
bin/main.o:
	gcc -c src/main.c -o bin/main.o
bin/util.o:
	gcc -c src/util.c -o bin/util.o
link: bin/algorithm.o bin/io.o bin/main.o bin/util.o 
	gcc bin/algorithm.o bin/io.o bin/main.o bin/util.o -o lab1/main
clean: 
	rm bin/*.o lab1/main
