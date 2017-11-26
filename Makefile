CC = g++
EXE = base64

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c++17


$(EXE): base64.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)