CC = g++
EXE = base64

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c++11

all: $(EXE)

$(EXE): base64.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm -f $(EXE)


define test
	@echo -n "Test $(1)... "
	@$(EXE) $(2) < tests/$(3).txt | xargs echo -n | cmp -s tests/$(4).txt -
	@if [ $$? -eq 0 ] ; then echo "PASSED." ; else echo "FAILED." ; fi
endef

tests: $(EXE)
	@echo "Performing tests..."
	$(call test,01,,test3e,test3d)
	$(call test,02,,test4e,test4d)
	$(call test,03,,test5e,test5d)
	$(call test,04,,test6e,test6d)
	$(call test,05,-d,test3d,test3e)
	$(call test,06,-d,test4d,test4e)
	$(call test,07,-d,test5d,test5e)
	$(call test,08,-d,test6d,test6e)
	@echo "...DONE"
