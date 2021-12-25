all: lab_04

obj/clist.o:
	mkdir -p obj
	gcc -c src/clist.c -o obj/clist.o -I include
obj/main.o:
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o -I include   
lab_04: obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab_04
clean: 
	rm -r obj 
	rm lab_04
