/*
 Version 20210120
 Winfried Bantel, Aalen University
 ToDo:
 make_index_array: YDB_MAX_SUBS abfangen dt. in []
 Operator [] for double
*/

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "ydb-global.h"
using namespace std;

int ydb_global_throw_error = 0;

static ydb_buffer_t global_ret[YDB_MAX_SUBS] ={ // Must be YDB_MAX_SUBS entries!
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]},
	{YDB_MAX_STR, YDB_MAX_STR, new char[YDB_MAX_STR]}
};

// Konstruktor
c_ydb_global::c_ydb_global(string s) {
	name = s;
	YDB_CPPSTR_TO_BUFFER(name, b_name);
	error = 0;
}

// error-getter
int c_ydb_global::last_error() {
	return error;
}

// Ausgabeoperator <<
ostream & operator << (ostream & o,  c_ydb_global & c) {
	o << (string) c_ydb_entry(&c);
	return o;
}

ostream & operator << (ostream & o,  c_ydb_entry e) {
	o << (string) e;
	return o;
}

// Zuweisung aus String
/*c_ydb_global & c_ydb_global::operator = (const string & s) {
	ydb_buffer_t value;
	YDB_CPPSTR_TO_BUFFER(s, value);

	error = ydb_set_s(&b_name, make_index_array(), b_index, &value);
	return *this;
}

// Zuweisung aus int
c_ydb_global & c_ydb_global::operator = ( const int & i) {
	string dummy = to_string(i);
	*this = dummy;
	return *this;
}

// Zuweisung aus c_ydb_global
c_ydb_global & c_ydb_global::operator = (c_ydb_global & re) {
	string dummy = re;
	*this = dummy;
	return *this;
}

// string-typecast
c_ydb_global::operator string() {
	error = ydb_get_s(&b_name, make_index_array(), b_index, global_ret);
	if (error && ydb_global_thow_error)
		throw error;
	return error ? "" : string(global_ret[0].buf_addr, global_ret[0].len_used);
}

// []-Operator mit string
c_ydb_entry c_ydb_global::operator [] (string s) {
	return c_ydb_entry(this, s);
}

c_ydb_entry c_ydb_global::operator [] (int _i) {
	return c_ydb_entry(this, to_string(_i));
}

c_ydb_global::operator string () {
	return string(c_ydb_entry(this));
}




// []-Operator mit int
c_ydb_global & c_ydb_global::operator [] (int i) {
	s_index[height++] = to_string(i);
	return *this;
}

// []-Operator mit indexListe
c_ydb_global & c_ydb_global::operator [] (indexList & l) {
	for (unsigned int i = 0; i< l.size(); i++)
		s_index[height++] = l[i];
	return *this;
}


// $data
unsigned int  c_ydb_global::data() {
	unsigned int rc;
	error = ydb_data_s(&b_name, make_index_array(), b_index, & rc);
	return rc;
}
*/
int  c_ydb_entry::operator+=(int by) {
	string dummy = to_string(by);
	int rc = 0;
	ydb_buffer_t value;
	YDB_CPPSTR_TO_BUFFER(dummy, value);
	make_index_array();
	glo->error = ydb_incr_s(&(glo->b_name), height, b_index, & value, global_ret);
	if (!glo->error)
		rc = stoi(string(global_ret[0].buf_addr, global_ret[0].len_used));
	else if (ydb_global_throw_error)
		throw glo->error;
	return rc;
}

int  c_ydb_entry::operator -= (int by) {
	return *this += -by;
}

int  c_ydb_entry::operator ++ () { // prefix
	return *this += 1;
}

int  c_ydb_entry::operator ++ (int dummy) { // postfix
	return (*this += 1) - 1;
}

int  c_ydb_entry::operator -- () { // prefix
	return *this += -1;
}

int  c_ydb_entry::operator --(int dummy) { // postfix
	return (*this += -1) + 1;
}

int  c_ydb_global::operator+=(int by) {
	return c_ydb_entry(this) += by;
}

int  c_ydb_global::operator--() {
	return c_ydb_entry(this) += -1;
}

int  c_ydb_global::operator++() {
	int rc = c_ydb_entry(this) += 1;
	return rc;
}

int  c_ydb_global::operator--(int dummy) {
	return (c_ydb_entry(this) += -1) +1;
}

string  c_ydb_global::operator =(string s) {
	c_ydb_entry(this) = s;
	return s;
}

int  c_ydb_global::operator =(int i) {
	c_ydb_entry(this) = to_string(i);
	return i;
}

//Now protected methods


// index-buffer aufbauen
void c_ydb_entry::make_index_array() {
	for (unsigned int i = 0; i < height; i++)
		YDB_CPPSTR_TO_BUFFER(s_index[i], b_index[i]);
}

// Proxy c_ydb_entry

c_ydb_entry::c_ydb_entry(c_ydb_global * _g, string _s) {
	glo = _g, s_index[0] = _s, height = 1;
}

c_ydb_entry::c_ydb_entry(c_ydb_global * _g) {
	glo = _g, height = 0;
}

c_ydb_entry & c_ydb_entry::operator [](const char * t) {
	s_index[height++] = string(t);
	return *this;
}

c_ydb_entry & c_ydb_entry::operator [](string _s) {
	s_index[height++] = _s;
	return *this;
}

c_ydb_entry & c_ydb_entry::operator [](c_ydb_entry e) {
	s_index[height++] = (string) e;
	return *this;
}

c_ydb_entry & c_ydb_entry::operator [](int _i) {
	s_index[height++] = to_string(_i);
	return *this;
}

c_ydb_entry::operator string (){
	make_index_array();
	glo->error = ydb_get_s(&(glo->b_name), height, b_index, global_ret);
	if (glo->error && ydb_global_throw_error)
		throw glo->error;
//	cout << "== " << string(global_ret[0].buf_addr, global_ret[0].len_used);
	return string(glo->error ? "" : string(global_ret[0].buf_addr, global_ret[0].len_used));
}
/*
c_ydb_entry::operator int (){
	int a = stoi(string(*this));
	return a;
}*/

double c_ydb_entry::operator + (){
	return 	stod(string(*this));
}

int c_ydb_entry::operator = (int i){
	*this = to_string(i);
	return i;
}


string c_ydb_entry::operator = (string s){
	ydb_buffer_t value;
	YDB_CPPSTR_TO_BUFFER(s, value);
	make_index_array();
	glo->error = ydb_set_s(&(glo->b_name), height, b_index, &value);
	if (glo->error && ydb_global_throw_error)
		throw glo->error;
	return s;
}

void c_ydb_entry::kill(bool p) {
	make_index_array();
	glo->error = ydb_delete_s(&(glo->b_name), height, b_index, p ? YDB_DEL_TREE : YDB_DEL_NODE);
	if (glo->error && ydb_global_throw_error)
		throw glo->error;
}

// Methode order / next
string c_ydb_entry::nextSibling() {
	string result;
	make_index_array();
	if ((glo->error = ydb_subscript_next_s(&(glo->b_name), height, b_index, global_ret)) == YDB_OK)
		result = string(global_ret[0].buf_addr, global_ret[0].len_used);
	else if (ydb_global_throw_error)
		throw glo->error;
	return result;
}

string c_ydb_entry::previousSibling() {
	string result;
	make_index_array();
	if ((glo->error = ydb_subscript_previous_s(&(glo->b_name), height, b_index, global_ret)) == YDB_OK)
		result = string(global_ret[0].buf_addr, global_ret[0].len_used);
	else if (ydb_global_throw_error)
		throw glo->error;
	return result;
}

c_ydb_entry  c_ydb_global::operator [] (string s) {
	return c_ydb_entry(this, s);
}

c_ydb_entry  c_ydb_global::operator [] (c_ydb_entry e) {
	return c_ydb_entry(this, (string) e);
}

c_ydb_entry  c_ydb_global::operator [] (const char * txt) {
	return c_ydb_entry(this, string(txt));
}

c_ydb_entry  c_ydb_global::operator [] (int i) {
	return c_ydb_entry(this, to_string(i));
}

void c_ydb_global::kill(bool p) {
	c_ydb_entry(this).kill();
}

c_ydb_global::operator string() {
	return (string) c_ydb_entry(this);
}
/*
c_ydb_global::operator int () {
	return stoi(string(c_ydb_entry(this)));
}*/
double c_ydb_global::operator + () {
	return stod(string(c_ydb_entry(this)));
}
c_ydb_entry c_ydb_global::operator () (indexList & l) {
	c_ydb_entry e = c_ydb_entry(this);
	for (unsigned int i = 0; i< l.size(); i++)
		e.s_index[e.height++] = l[i];
	return e;
}

indexList c_ydb_entry::query() {
	indexList rc;
	int n = YDB_MAX_SUBS;
	make_index_array();
	glo->error = ydb_node_next_s(&(glo->b_name), height, b_index, &n, global_ret);
	if (glo->error == YDB_OK)
		for (int i = 0; i < n; i++)
			rc.push_back(string(global_ret[i].buf_addr, global_ret[i].len_used));
	else if (ydb_global_throw_error)
		throw glo->error;
	return rc;
}
