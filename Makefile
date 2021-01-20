# 20210120
cpp=g++
ydb=$(shell pkg-config --variable=prefix yottadb)
options=-I$(ydb) -L$(ydb) -lyottadb -Wall
baseexecutables=test1 test2 test3 test4 test5-query \
        cpp-api-wordfreq \
        object-db-blob object-db-globalmapping
executables=$(patsubst %,bin/%,$(baseexecutables))

all:	$(executables)

ydb-global.o: ydb-global.cpp ydb-global.h
	$(cpp) -c ydb-global.cpp $(options)

bin/%: %.cpp ydb-global.o
	$(cpp) $< ydb-global.o $(options) -o $@
clean:
	rm -f *.o

clean-all: clean
	rm -f $(executables)
