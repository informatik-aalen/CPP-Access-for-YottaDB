# 20210413

cpp=g++
ydb=$(shell pkg-config --variable=prefix yottadb)
coptions=-I$(ydb) -I../src/ -Wall -DWITH_JSON=1 
loptions=-L$(ydb) -lyottadb -ljsoncpp
baseexecutables=json_import json_export json-import-string

executables=$(patsubst %,bin/%,$(baseexecutables))

all:	$(executables)

ydb-global.o: ../src/ydb-global.cpp ../src/ydb-global.h
	$(cpp) -c ../src/ydb-global.cpp $(coptions)

bin/%: %.cpp ydb-global.o
	$(cpp) $< ydb-global.o $(coptions) $(loptions) -o $@
clean:
	rm -f *.o

clean-all: clean
	rm -f $(executables)
