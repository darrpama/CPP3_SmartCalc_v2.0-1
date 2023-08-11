OS := $(shell uname -s)

CC = g++
# CPPFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
CPPFLAGS = -g -std=c++17 -Wall -Werror -Wextra -lstdc++
LIBS = -lgtest --coverage

all: test

clean:
	rm -rf s21_calculator.a
	rm -rf *.o
	rm -rf *.out
	rm -rf build
	rm -rf report
	rm *.gcda *.gcno
	rm test.info
	rm unit_tests

exampleController.o:
	$(CC) $(CPPFLAGS) -c exampleController.cpp -o exampleController.o $(LIBS)

Model.o:
	$(CC) $(CPPFLAGS) -c Model.cpp -o Model.o $(LIBS)

consoleView.o:
	$(CC) $(CPPFLAGS) -c consoleView.cpp -o consoleView.o $(LIBS)

test: Model.o
	$(CC) $(CPPFLAGS) Model.o main.cpp -o test.out $(LIBS)
	./test.out
