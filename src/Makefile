CC = g++
CCFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lstdc++ -lgtest --coverage
PROJECTDIR = ./Calculator
EXECUTABLE = test.out

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
	$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm *.gcno
	rm $(EXECUTABLE)
