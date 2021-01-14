// Version 20210112
/*
 Winfried Bantel, Aalen University
ToDo:
 make_index_array: MAX_INDEX abfangen
 Operator [] for double

*/
#include <iostream>
#include <string>
#include <string.h>
#include "ydb-global.h"
using namespace std;

static ydb_buffer_t global_val = {YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]};

// Konstruktor
c_ydb_global::c_ydb_global(string s, int t) {
	name = s;
	YDB_CPPSTR_TO_BUFFER(name, b_name);
	height = 0;
	use_throw = t;
}

// error-getter
int c_ydb_global::rc() {
	/* REVIEW: if no call to YDB has happened, this will return uninitialized memory.
	 * This should initialize `error = YDB_OK` in the `c_ydb_global` constructor.
	 */
	return error;
}

// Ausgabeoperator <<
ostream & operator << (ostream & o,  c_ydb_global & c) {
	o << (string) c;
	return o;
}

// Zuweisung aus String
// REVIEW: I think this will make a copy of `s` unconditionally. Consider returning `string&` instead.
string c_ydb_global::operator = ( const string & s) {
	ydb_buffer_t value;
	YDB_CPPSTR_TO_BUFFER(s, value);

	error = ydb_set_s(&b_name, make_index_array(), b_index, &value);
	if (use_throw && error)
		throw error;
	return s;
}

// Zuweisung aus int
int c_ydb_global::operator = ( const int & i) {
	*this = to_string(i);
	return i;
}

// Zuweisung aus c_ydb_global
// REVIEW: This will make a copy of `this` unconditionally. Consider returning `c_ydb_global&` instead.
c_ydb_global c_ydb_global::operator = (c_ydb_global & re) {
	*this = (string) re;
	return *this;
}

// string-typecast
c_ydb_global::operator string() {
	error = ydb_get_s(&b_name, make_index_array(), b_index, &global_val);
	if (use_throw && error)
		throw error;
	// REVIEW: This looks incorrect. If an error occurs, buf_addr may not be set to a valid address.
	// I think to fix this you would need to use exceptions unconditionally, because there's no
	// way to return an error from `operator string()`.
	return string(global_val.buf_addr, global_val.len_used);
}

// []-Operator mit string
c_ydb_global & c_ydb_global::operator [] (string s) {
	s_index[height++] = s;
	return *this;
}

// []-Operator mit int
c_ydb_global & c_ydb_global::operator [] (int i) {
	s_index[height++] = to_string(i);
	return *this;
}

// Methode order / next
string c_ydb_global::next() {
	string result;
	if ((error = ydb_subscript_next_s(&b_name, make_index_array(), b_index, &global_val)) == YDB_OK)
		result = string(global_val.buf_addr, global_val.len_used);
	if (use_throw && error)
		throw error;
	return result;
}

// Methode order(..., -1) / previous
string c_ydb_global::previous() {
	string result;
	if ((error = ydb_subscript_previous_s(&b_name, make_index_array(), b_index, &global_val)) == YDB_OK)
		result = string(global_val.buf_addr, global_val.len_used);
	if (use_throw && error)
		throw error;
	return result;
}

// Kill
void c_ydb_global::kill(int p) {
	error = ydb_delete_s(&b_name, make_index_array(), b_index, p ? YDB_DEL_TREE : YDB_DEL_NODE);
	if (error && use_throw)
		throw error;
	height = 0;
}

// $data
unsigned int  c_ydb_global::data() {
	unsigned int rc;
	error = ydb_data_s(&b_name, make_index_array(), b_index, & rc);
	if (error && use_throw)
		throw error;
	return rc;
}

int  c_ydb_global::operator+=(int by) {
	string dummy = to_string(by);
	ydb_buffer_t value;
	
	YDB_CPPSTR_TO_BUFFER(dummy, value);
	error = ydb_incr_s(&b_name, make_index_array(), b_index, & value, & global_val);
	if (error && use_throw)
		throw error;
	return stoi( string(global_val.buf_addr, global_val.len_used));
}

int  c_ydb_global::operator -= (int by) {
	return *this += -by;
}

int  c_ydb_global::operator ++ () { // prefix
	return *this += 1;
}

int  c_ydb_global::operator ++ (int dummy) { // postfix
	return (*this += 1) - 1;
}

int  c_ydb_global::operator -- () { // prefix
	return *this += -1;
}

int  c_ydb_global::operator --(int dummy) { // postfix
	return (*this += -1) + 1;
}

/*
Now protected methods
*/

// index-buffer aufbauen
unsigned int c_ydb_global::make_index_array() {
	unsigned int h2 = height;
	for (unsigned int i = 0; i < height; i++)
	YDB_CPPSTR_TO_BUFFER(s_index[i], b_index[i]);
	height = 0;
	return h2;
}
