CC = g++
EXE = base64

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c++17

all: $(EXE)

$(EXE): base64.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)


define test
	@echo -n "Test $(1)... "
	@$(EXE) $(2) < tests/$(3).txt | cmp -s tests/$(4).txt -
	@if [ $$? -eq 0 ] ; then echo "PASSED." ; else echo "FAILED." ; fi
endef

tests: $(EXE)
	@echo "Performing encoding tests..."
	$(call test,01,,test5e,test5d)
	$(call test,02,,test6e,test6d)
	$(call test,03,,test7e,test7d)
	$(call test,04,-d,test5d,test5e)
	$(call test,05,-d,test6d,test6e)
	$(call test,06,-d,test7d,test7e)
	@echo "...DONE"