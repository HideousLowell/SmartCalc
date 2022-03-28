GCOVFLAGS = -fprofile-arcs -ftest-coverage
FLAGS = -lgtest -lstdc++ -std=c++20
WCHECK = -Werror -Wall -Wextra
TEST_FILES = test.cpp model/calculation.cpp model/polish_notation.cpp model/credit_model.cpp
S = --suppress=
all: build calc

calc:
	cd view/SmartCalc.app/Contents/MacOS && ./SmartCalc

tests:
	g++ $(FLAGS) $(TEST_FILES) -o test
	./test

leaks:
	leaks --atExit -- ./test

gcov_report: 
	@g++ -lgtest --coverage $(TEST_FILES) $(FLAGS) -o test
	@./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

clean: myclean
	cd view && make clean

myclean:
	rm -rf *.gc* *.o *.a *.out *.info s21_calc test
	rm -rf report/ archive/

open:
	open report/index.html

build:
	cd view && qmake && make

rebuild: 
	clean all

install: build
	cd view && make clean

uninstall:
	rm -rf view/Makefile view/.qmake.stash view/SmartCalc.app/

cpplint: 
	python3 ../materials/linters/cpplint.py --extensions=cpp model/* controller/* \
	view/calcplot.cpp view/calcplot.h view/*c.cpp view/*c.h view/*w.cpp view/*w.h \
	view/*g.cpp view/*g.h view/*n.cpp test.cpp

cppcheck: 
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem --suppress=unusedFunction model/*.cpp model/*.h

dist:
	mkdir archive
	tar --totals --create --verbose --file archive.tar controller model view
	mv archive.tar archive/

dvi:	
	open info.html
	