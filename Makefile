CFLAGS = -W -Wall -g

finddiv: finddiv.o
	gcc -o $@ $^

finddiv.o: finddiv.c

clean:
	rm -f finddiv finddiv.o
