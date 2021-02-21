demo: demo.o arraylist.o
	gcc -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -o demo demo.o arraylist.o

demo.o: demo.c arraylist.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined demo.c

arraylist.o: arraylist.c arraylist.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined arraylist.c


# separate version of arraylist.o with debugging text enabled
darraylist.o: arraylist.c arraylist.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -DDEBUG -o darraylist.o arraylist.c

ddemo: demo.o darraylist.o
	gcc -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -o demo demo.o darraylist.o

clean:
	rm -f *.o demo ddemo
