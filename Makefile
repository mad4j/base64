CC = g++
EXE = base64

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c++17

all: $(EXE)

$(EXE): base64.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)

tests: $(EXE)
	@echo "Performing encoding tests..."
	@$(EXE) < tests/test5e.txt | cmp -s tests/test5d.txt -
	@echo $$?
	@$(EXE) < tests/test6e.txt | cmp -s tests/test6d.txt -
	@echo $$?
	@$(EXE) < tests/test7e.txt | cmp -s tests/test7d.txt -
	@echo $$?
	@echo "Performing decoding tests..."
	@$(EXE) -d < tests/test5d.txt | cmp -s tests/test5e.txt -
	@echo $$?
	@$(EXE) -d < tests/test6d.txt | cmp -s tests/test6e.txt -
	@echo $$?
	@$(EXE) -d < tests/test7d.txt | cmp -s tests/test7e.txt -
	@echo $$?
	@echo "..DONE"