all: lab_05

obj/point_list.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/point_list.c -o obj/point_list.o -I include
obj/clist.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/clist.c -o obj/clist.o -I include
obj/main.o:
	mkdir -p obj
	gcc -c -Wall -Wextra -pedantic -Werror src/main.c -o obj/main.o -I include   
lab_05: obj/point_list.o obj/clist.o obj/main.o
	gcc obj/point_list.o obj/clist.o obj/main.o -o lab_05
clean: 
	rm -r obj 
	rm lab_05
