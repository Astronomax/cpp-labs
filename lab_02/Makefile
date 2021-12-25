all: lab_02

obj/str.o:
	mkdir -p obj
	gcc -c src/str.c -o obj/str.o -I include
obj/test.o:
	mkdir -p obj
	gcc -c src/test.c -o obj/test.o -I include
obj/test_str.o:
	mkdir -p obj
	gcc -c src/test_str.c -o obj/test_str.o -I include   
lab_02: obj/str.o obj/test.o obj/test_str.o
	gcc obj/str.o obj/test.o obj/test_str.o -o lab_02
clean: 
	rm -r obj 
	rm lab_02
