/*
 Version 20210120
 Winfried Bantel, Aalen University
 */
#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

extern "C" {
#include <libyottadb.h>
}

#define YDB_CPPSTR_TO_BUFFER(str, buf) buf.buf_addr = (char *) str.c_str(), buf.len_used = buf.len_alloc = str.length()
#define MAX_INDEX 32
typedef vector<string> indexList;

class c_ydb_global;
class c_ydb_entry;

class c_special_string {
	unsigend int l;
	
}
class c_ydb_entry { // proxy class for []-operator
public:
	friend ostream & operator << (ostream &, c_ydb_entry);

	c_ydb_entry (c_ydb_global *, string);
	c_ydb_entry (c_ydb_global *);
	c_ydb_entry & operator[](const char *);
	c_ydb_entry & operator[](string);
	c_ydb_entry & operator[](c_ydb_entry);
	c_ydb_entry & operator [] (int);
	operator string();
	//operator int ();
	string operator=(string);
	double operator + ();
	int operator=(int);
	int operator+=(int);
	int operator-=(int);
	int operator++(int);
	int operator++();
	int operator--(int);
	int operator--();

	void kill(bool = true);
	indexList query();
	string nextSibling();
	string previousSibling();
// private:
	c_ydb_global * glo;
	ydb_buffer_t b_index[MAX_INDEX];
	string s_index[MAX_INDEX];
	unsigned int height;
	void make_index_array();
};

class c_ydb_global {
public:
	c_ydb_global(string);
	friend ostream & operator << (ostream & o, c_ydb_global & c);
	c_ydb_entry operator [] (string);
	c_ydb_entry operator [] (const char *);
	c_ydb_entry operator [] (int);
	c_ydb_entry operator [] (c_ydb_entry);
	c_ydb_entry operator () (indexList &);
	operator string ();
//	operator double ();
	friend class c_ydb_entry;
	int last_error();
	double operator + ();
	string operator=(string);
	int operator=(int);
	int operator+=(int);
	int operator-=(int);
	int operator++(int);
	int operator++();
	int operator--(int);
	int operator--();
	void kill(bool = true);
protected:
	string name;
	ydb_buffer_t b_name;
	int error;
};
