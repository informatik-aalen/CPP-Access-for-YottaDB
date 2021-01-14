ydb=$(shell pkg-config --variable=prefix yottadb)
CXXFLAGS=-I$(ydb) -Wall
LDFLAGS=-L$(ydb) -lyottadb

all: test1 test2 test3

test1: test1.o ydb-global.o
	$(CXX) $^ $(LDFLAGS) -o $@

test2: test2.o ydb-global.o
	$(CXX) $^ $(LDFLAGS) -o $@

test3: test3.o ydb-global.o
	$(CXX) $^ $(LDFLAGS) -o $@

ydb-global.o: ydb-global.cpp ydb-global.h
test1.o: test1.cpp
test2.o: test2.cpp
test3.o: test3.cpp

clean:
	rm -f *.o test1 test2 test3
