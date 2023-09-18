CC = g++
CCFLAGS = -g -std=c++17 -pedantic -Wall -Werror -Wextra
LDFLAGS = -lstdc++ -lgtest -fprofile-arcs -ftest-coverage
PROJECTDIR = ./Calculator
BUILDDIR = ./SmartCalc2
EXECUTABLE = test.out
STATICLIB = SmartCalc2.a
DISTDIR = ./DISTRIBUTIVE

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
	open ./dvi.md

build:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make

install:
	cd $(PROJECTDIR) && ls -la && mkdir $(BUILDDIR) && cd $(BUILDDIR) && cmake .. && make
	cd $(PROJECTDIR) && $(BUILDDIR)/Calculator.app/Contents/MacOS/Calculator

uninstall:
	cd $(PROJECTDIR) && rm -rf $(BUILDDIR)

dist:
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
	mkdir $(DISTDIR)/src
	cp -r $(PROJECTDIR) dvi.md Makefile $(DISTDIR)/src/
	tar cvzf $(DISTDIR).tgz $(DISTDIR)
	rm -rf $(DISTDIR)

check:
	clang-format -n --style="Google" $(SOURCES) $(HEADERS)
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=unusedStructMember --suppress=missingInclude --suppress=unmatchedSuppression $(SOURCES) $(HEADERS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(HEADERS) -o $@ $(LDFLAGS)
	./$(EXECUTABLE) 

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $< $(LDFLAGS)

$(STATICLIB): $(OBJECTS)
	ar rcs $(STATICLIB) $^

gcov_report: $(EXECUTABLE)
	./$(EXECUTABLE)
	lcov -t "./test.out" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

.PHONY: clean
clean:
	@rm -rf $(OBJECTS)
	@rm -rf $(EXECUTABLE)
	@rm -rf $(STATICLIB)
	@rm -rf *.gcno $(GCDA) $(GCNO) *.info
	@rm -rf report
