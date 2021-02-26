demo: demo.o strbuf.o
	gcc -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -o demo demo.o strbuf.o

demo.o: demo.c strbuf.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined demo.c

strbuf.o: strbuf.c strbuf.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined strbuf.c


# separate version of strbuf.o with debugging text enabled
dstrbuf.o: strbuf.c strbuf.h
	gcc -c -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -DDEBUG -o dstrbuf.o strbuf.c

ddemo: demo.o dstrbuf.o
	gcc -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -o demo demo.o dstrbuf.o

clean:
	rm -f *.o demo ddemo
