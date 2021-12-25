all: hw_01

obj/bmp.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/bmp.c -o obj/bmp.o -I include
obj/stego.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/stego.c -o obj/stego.o -I include
obj/main.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/main.c -o obj/main.o -I include   
hw_01: obj/bmp.o obj/stego.o obj/main.o
	gcc obj/bmp.o obj/stego.o obj/main.o -o hw_01
clean: 
	rm -r obj 
	rm hw_01
