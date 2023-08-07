OS := $(shell uname -s)

CC = g++
CPPFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
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

exampleModel.o:
	$(CC) $(CPPFLAGS) -c exampleModel.cpp -o exampleModel.o $(LIBS)

consoleView.o:
	$(CC) $(CPPFLAGS) -c consoleView.cpp -o consoleView.o $(LIBS)

test: consoleView.o exampleModel.o exampleController.o
	$(CC) $(CPPFLAGS) exampleController.o exampleModel.o consoleView.o main.cpp -o test.out $(LIBS)
	./test.out
