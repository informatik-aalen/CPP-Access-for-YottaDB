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
// REVIEW: This looks wrong; it should use `YDB_MAX_SUBS` instead. YDB_MAX_SUBS is not guarenteed to be 32 (it just happens to be in practice).
#define MAX_INDEX 32

// REVIEW: what does the `c_` mean?
class c_ydb_global {
// REVIEW: It would be nice to add documentation inline to all these files. This is documented in the readme, but not inline.
/* REVIEW: The following functions are missing:
	- ydb_delete_excl
	- ydb_lock
	- ydb_lock_decr
	- ydb_lock_incr
	- ydb_node_next
	- ydb_node_previous
	- ydb_tp
	- ydb_str2zwr
	- ydb_zwr2str
 * I know you are working on ydb_tp. str2zwr and zwr2str probably don't make sense to add since they
 * don't require a key, although it may be nice to add a wrapper function that takes and returns
 * `string` instead. I think it makes sense to add the others.
 */
/* 
 * REVIEW: There is no way to change a variable (`name`), nor to retrieve the subscripts of an
 * existing global. That means that each time you want to change only the variable, or only one
 * subscript, you have to make a new ydb_global. It would be nice to add a way to change these so
 * the interface can be more efficient.
 */
public:
	// REVIEW: I would take a boolean instead of an int here to make it clear there are only two possible error handling mechanisms.
	c_ydb_global(string, int = 0);
	// REVIEW: what does `friend` do here?
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
	// REVIEW: this should be documented. 1 means YDB_DEL_TREE, 0 means YDB_DEL_NODE. I would even go so far as making it an `enum`.
	void kill(int = 1);
	// REVIEW: the `int` here is confusing, but is consistent wtih `ydb_data`. Consider using an enum instead, but keeping as an int seems fine if you think consistency is better.
	unsigned int  data();
	int rc();
	c_ydb_global operator = (c_ydb_global &);
// REVIEW: why use `protected` instead of `private`? Why add this to the public header instead of the .cpp file?
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
