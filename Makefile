#Sample Makefile for Malloc
CC=gcc
CFLAGS=-g -O0 -fPIC -Werror -Wall -std=gnu99

TESTS=t-test1 test1
HEADERS=utils.h malloc.h

all:	${TESTS} libmalloc.so

clean:
	rm -rf *.o *.so ${TESTS}

libmalloc.so: utils.o malloc.o realloc.o calloc.o memalign.o free.o
	$(CC) $(CFLAGS) -shared -Wl,--unresolved-symbols=ignore-all $^ -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@ -lpthread

# For every XYZ.c file, generate XYZ.o.
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) $< -c -o $@

check1:	libmalloc.so test1 t-test1
	LD_PRELOAD=`pwd`/libmalloc.so ./t-test1

check:	libmalloc.so ${TESTS}
	LD_PRELOAD=`pwd`/libmalloc.so ./t-test1

dist: clean
	dir=`basename $$PWD`; cd ..; tar cvf $$dir.tar ./$$dir; gzip $$dir.tar

