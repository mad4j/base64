CC = gcc
EXE = base64

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c11


$(EXE): base64.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)