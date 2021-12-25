all: lab_03

obj/mergesort.o:
	mkdir -p obj
	gcc -c src/mergesort.c -o obj/mergesort.o -I include
obj/main.o:
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include   
lab_03: obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab_03
clean: 
	rm -r obj 
	rm lab_03
