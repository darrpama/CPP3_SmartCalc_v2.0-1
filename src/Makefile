CC = g++
CCFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lstdc++ -lgtest --coverage
PROJECTDIR = ./Calculator
EXECUTABLE = test

HEADERS = \
    $(PROJECTDIR)/Model/Arithmetic.h \
    $(PROJECTDIR)/Model/Model.h \
    $(PROJECTDIR)/Model/Validator.h

SOURCES = \
    $(PROJECTDIR)/Model/Model.cc \
    $(PROJECTDIR)/Model/Validator.cc \
    $(PROJECTDIR)/Tests/testModel.cc

OBJECTS = $(SOURCES:.cc=.o)


all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(HEADERS) -o $@ $(LDFLAGS) 

%.o: %.cc
	$(CC) $(CPPFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -rf s21_calculator.a
	rm -rf *.o
	rm -rf *.out
	rm -rf build
	rm -rf report
	rm -rf *.dSYM
	rm *.gcda *.gcno
