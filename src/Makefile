CC = g++
CCFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lstdc++ -lgtest -fprofile-arcs -ftest-coverage
PROJECTDIR = ./Calculator
BUILDDIR = ./SmartCalc2
EXECUTABLE = test.out

HEADERS = \
    $(PROJECTDIR)/Model/Arithmetic.h \
    $(PROJECTDIR)/Model/Model.h \
    $(PROJECTDIR)/Model/CreditModel.h \
    $(PROJECTDIR)/Model/DepositModel.h \
    $(PROJECTDIR)/Model/Validator.h

SOURCES = \
    $(PROJECTDIR)/Model/Model.cc \
    $(PROJECTDIR)/Model/CreditModel.cc \
    $(PROJECTDIR)/Model/DepositModel.cc \
    $(PROJECTDIR)/Model/Validator.cc \
    $(PROJECTDIR)/Tests/TestModel.cc \
    $(PROJECTDIR)/Tests/TestValidator.cc \
    $(PROJECTDIR)/Tests/TestCredit.cc \
    $(PROJECTDIR)/Tests/TestDeposit.cc \
    $(PROJECTDIR)/Tests/RunAllTests.cc

OBJECTS = $(SOURCES:.cc=.o)
GCDA = $(SOURCES:.cc=.gcda)
GCNO = $(SOURCES:.cc=.gcno)


all: install

test: $(SOURCES) $(EXECUTABLE)

dvi:

install:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make
	cd $(PROJECTDIR) && $(BUILDDIR)/Calculator.app/Contents/MacOS/Calculator

uninstall:
	cd $(PROJECTDIR) && rm -rf $(BUILDDIR)

check:
	clang-format -n --style="Google" $(SOURCES) $(HEADERS)
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unusedStructMember --suppress=missingInclude --suppress=unmatchedSuppression $(SOURCES) $(HEADERS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(HEADERS) -o $@ $(LDFLAGS)
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $< $(LDFLAGS)

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm *.gcno $(GCDA) $(GCNO) *.info
	rm $(EXECUTABLE)
	rm -rf report
