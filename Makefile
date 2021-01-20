cpp=g++
ydb=$(shell pkg-config --variable=prefix yottadb)
options=-I$(ydb) -L$(ydb) -lyottadb -Wall

all: test1 test2 test3 test4 test5-query \
	cpp-api-wordfreq \
	object-db-blob object-db-globalmapping

test1: test1.cpp ydb-global.o
	$(cpp) test1.cpp ydb-global.o $(options) -o test1

test2: test2.cpp ydb-global.o
	$(cpp) test2.cpp ydb-global.o $(options) -o test2

test3: test3.cpp ydb-global.o
	$(cpp) test3.cpp ydb-global.o $(options) -o test3

test4: test4.cpp ydb-global.o
	$(cpp) test4.cpp ydb-global.o $(options) -o test4

test5-query: test5-query.cpp ydb-global.o
	$(cpp) test5-query.cpp ydb-global.o $(options) -o test5-query

cpp-api-wordfreq: cpp-api-wordfreq.cpp ydb-global.o
	$(cpp) cpp-api-wordfreq.cpp ydb-global.o $(options) -o cpp-api-wordfreq

object-db-blob: object-db-blob.cpp ydb-global.o
	$(cpp) object-db-blob.cpp ydb-global.o $(options) -o object-db-blob

object-db-globalmapping: object-db-globalmapping.cpp ydb-global.o
	$(cpp) object-db-globalmapping.cpp ydb-global.o $(options) -o object-db-globalmapping

ydb-global.o: ydb-global.cpp ydb-global.h
	$(cpp) -c ydb-global.cpp $(options)

clean:
	rm -f *.o
