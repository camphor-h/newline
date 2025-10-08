newline: newline.c newline.h
	cc -Wall -o newline newline.c
clean:
	rm -f newline
