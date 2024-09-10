CC=					gcc -g
CTFLAGS=				-std=c11
CFLAGS=				-Wall -Wextra -Werror -std=c11 -pedantic
GCOVFLAGS=			-fprofile-arcs -ftest-coverage -lgcov --coverage
SOURCES=			parser.c transformations.c
OBJECT=		$(patsubst %*.c, %*.o, $(SOURCES))
SOURCES_TEST=		test.c 
OS=					$(shell uname -s)

ifeq ($(OS), Linux)
  CFLAGS+=			-D OS_LINUX
  CHECKFLAGS=			-lpthread -lcheck -pthread -lrt -lsubunit -lm
endif
ifeq ($(OS), Darwin)
  CFLAGS+=			-D OS_MAC
  CHECKFLAGS=		-lcheck
endif

all: clean install

install: clean 
	mkdir 3DViewer1
	cd 3DViewer1 && qmake ../ && make

uninstall: clean
	rm -rf 3DViewer1

test: clean $(SOURCES_TEST)
	$(CC) $(CFLAGS) $(CTFLAGS) parser.c transformations.c $(SOURCES_TEST) $(CHECKFLAGS) -o test
	./test
	
gcov_report: clean
	@gcc $(GCOVFLAGS) $(SOURCES_TEST) $(SOURCES) $(CHECKFLAGS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
# @lcov -e GcovReport.info '*.c' -o GcovReport.info
	@genhtml -o report GcovReport.info
	@open ./report/index.html
	@rm -rf ./*.gcno ./*gcda ./GcovReport.*

dvi:
	open ../README.md

dist:
	rm -rf ../3DViewer/
	mkdir ../3DViewer/
	cp pars* ../3DViewer/
	cp trans* ../3DViewer/
	cp Open* ../3DViewer/
	cp main* ../3DViewer/
	# cp dvi.html ../3DViewer/
	tar -C ../ -czvf 3DViewer.tgz 3DViewer/
	rm -rf ../3DViewer/

clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h *.cpp
	@rm .clang-format

leaks: test
	leaks -atExit -- ./test

clean:
	@rm -rf ./a.out ./*.o ./*.a ./test ./GcovReport ./report ./*.info ./*.gcno ./*gcda ./*gch