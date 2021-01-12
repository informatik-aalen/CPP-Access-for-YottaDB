// Version 20210112
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

extern "C" {
#include <libyottadb.h>
}

/*
 Winfried Bantel, Aalen University
 */
#define YDB_CPPSTR_TO_BUFFER(str, buf) buf.buf_addr = (char *) str.c_str(), buf.len_used = buf.len_alloc = str.length()
#define MAX_INDEX 32

class c_ydb_global {
public:
	c_ydb_global(string, int = 0);
	friend ostream & operator << (ostream & o, c_ydb_global & c);
	c_ydb_global & operator [] (string);
	c_ydb_global & operator [] (int);
	string operator = (const string & );
	int operator = (const int & );
	int operator += (int);
	int operator -= (int);
	int operator ++ (); // prefix
	int operator ++ (int); // postfix
	int operator -- (); // prefix
	int operator -- (int); // postfix
	operator string();
	string next();
	string previous();
	void kill(int = 1);
	unsigned int  data();
	int rc();
	c_ydb_global operator = (c_ydb_global &);
protected:
	string name;
	ydb_buffer_t b_name;
	int error;
	ydb_buffer_t b_index[MAX_INDEX];
	string s_index[MAX_INDEX];
	unsigned int height;
	unsigned int make_index_array();
	int use_throw;
};
