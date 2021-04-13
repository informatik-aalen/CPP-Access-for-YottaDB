/*
 Version 20210413
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

class c_ydb_entry { // proxy class for []-operator
public:
	friend ostream & operator << (ostream &, c_ydb_entry);
	friend int ydb_lock(vector<c_ydb_entry> &, unsigned long long);
	friend class c_ydb_global;
	
	c_ydb_entry (c_ydb_global *, string);
	c_ydb_entry (c_ydb_global *);
	c_ydb_entry & operator[](const char *);
	c_ydb_entry & operator[](string);
	c_ydb_entry & operator[](c_ydb_entry);
	c_ydb_entry & operator [] (int);
	c_ydb_entry & operator [] (double);
	operator string();
	operator indexList () const;
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
	double operator=(double);

	void kill(bool = true);
	int lock_inc(unsigned long long = 0);
	int lock_dec();
	indexList query();
	string nextSibling();
	string previousSibling();
	bool isSet();
	bool hasChilds();
	string getName() const ;

protected:
	c_ydb_global * glo;
	ydb_buffer_t b_index[MAX_INDEX];
	string s_index[MAX_INDEX];
	unsigned int height;
	void make_index_array();
	unsigned int data();
};

class c_ydb_global {
public:
	c_ydb_global(const string & s);
	c_ydb_global(const c_ydb_global &);
	friend ostream & operator << (ostream & o, c_ydb_global & c);
	friend int ydb_lock(vector<c_ydb_entry> &, unsigned long long);
	c_ydb_entry operator [] (string);
	c_ydb_entry operator [] (const char *);
	c_ydb_entry operator [] (int);
	c_ydb_entry operator [] (double);
	c_ydb_entry operator [] (c_ydb_entry);
	c_ydb_entry operator () (indexList &);
	operator string ();
//	operator double ();
	operator c_ydb_entry();
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
	double operator=(double);
	void kill(bool = true);
	int  lock_inc(unsigned long long = 0);
	int lock_dec();
	bool isSet();
	bool hasChilds();
	string getName() const;
	void setName(const string & s);
protected:
	string name;
	ydb_buffer_t b_name;
	int error;
	string double_to_string(double);
};

int ydb_lock(vector<c_ydb_entry> & , unsigned long long = 0);
/*  1 */ int ydb_lock(const c_ydb_entry &, unsigned long long = 0);
/*  2 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  3 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  4 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  5 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  6 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  7 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  8 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/*  9 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);
/* 10 */ int ydb_lock(const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, const c_ydb_entry &, unsigned long long = 0);



/*
 
 JSON
 
 */
#if WITH_JSON > 0
#include <jsoncpp/json/json.h>
#include "ydb-global.h"
// void jsoncpp_2_ydb(const c_ydb_entry & glo, const Json::Value & val);
// Json::Value ydb_2_jsoncpp(const c_ydb_entry & glo);
// int isNumeric(string str);
void operator << (const c_ydb_entry & glo, const Json::Value & val);
void operator << (Json::Value & val,const c_ydb_entry & glo);
void operator >> (Json::Value & val, const c_ydb_entry & glo);
//void operator >> (const c_ydb_entry & glo, Json::Value & val);
#endif
