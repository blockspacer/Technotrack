CC         = g++
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: stack

stack: main.cpp stack.hpp vector.hpp tools.hpp
	$(CC)  -Wall main.cpp -o stack 

gcov_stack: main.cpp stack.hpp vector.hpp tools.hpp
	$(CC) $(GCOV_FLAGS) main.cpp -o stack 

clean:
	rm stack

gcov_clean:
	rm *.gcda *.gcno *.gcov stack
