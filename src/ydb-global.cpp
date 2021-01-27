/*
 Version 20210127
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


// $data protected!!!!
unsigned int  c_ydb_entry::data() {
	unsigned int rc;
	make_index_array();
	glo->error = ydb_data_s(&(glo->b_name), height, b_index, & rc);
	if (glo->error && ydb_global_throw_error)
		throw glo->error;
	return rc;
}

bool c_ydb_global::isSet() {
	return c_ydb_entry(this).data() % 2;
}

bool c_ydb_global::hasChilds() {
	return c_ydb_entry(this).data() >= 10;
}

bool c_ydb_entry::isSet() {
	return data() % 2;
}

bool c_ydb_entry::hasChilds() {
	return data() >= 10;
}

int  c_ydb_entry::operator += (int by) {
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

int  c_ydb_global::operator -- () {
	return c_ydb_entry(this) += -1;
}

int  c_ydb_global::operator ++ () {
	int rc = c_ydb_entry(this) += 1;
	return rc;
}

int  c_ydb_global::operator -- (int dummy) {
	return (c_ydb_entry(this) += -1) +1;
}

string  c_ydb_global::operator = (string s) {
	c_ydb_entry(this) = s;
	return s;
}

int  c_ydb_global::operator = (int i) {
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
	return string(glo->error ? "" : string(global_ret[0].buf_addr, global_ret[0].len_used));
}

/* // Not bossible because std::string-constructors are then ambigous!!! Unary + instead!
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


c_ydb_global::operator c_ydb_entry() {
	return c_ydb_entry(this);
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

int c_ydb_entry::lock_inc(unsigned long long t) {
	make_index_array();
	glo->error = ydb_lock_incr_s(t, &(glo->b_name), height, b_index);
	if (glo->error && glo->error != YDB_LOCK_TIMEOUT && ydb_global_throw_error)
		throw glo->error; // YDB_LOCK_TIMEOUT always via rc !!!!
	return glo->error;
}

int c_ydb_entry::lock_dec() {
	make_index_array();
	glo->error = ydb_lock_decr_s(&(glo->b_name), height, b_index);
	if (glo->error && ydb_global_throw_error)
		throw glo->error;
	return glo->error;
}

int c_ydb_global::lock_inc(unsigned long long t) {
	return c_ydb_entry(this).lock_inc(t);
}

int c_ydb_global::lock_dec() {
	return c_ydb_entry(this).lock_dec();
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

//

int ydb_lock(vector<c_ydb_entry> & v, unsigned long long t) {
//	cout << v.size() << " " << v[0].height << endl;
	for (unsigned int i = 0; i < v.size(); i++) {
		v[i].make_index_array();
/*		cout << v[i].glo->name << ": " << v[i].height << endl;
		for (unsigned int j = 0; j < v[i].height; j++)
			cout << j << " ==> " <<v[i].s_index[j] << " " << (unsigned long int) v[i].s_index[j].c_str() << " " << (unsigned long int) v[i].b_index[j].buf_addr << endl;*/
	}
	switch (v.size()) {
		case 1: return ydb_lock_s(t, 1,  &(v[0].glo->b_name), v[0].height, v[0].b_index);
		case 2: return ydb_lock_s(t, 2, &(v[0].glo->b_name), v[0].height, v[0].b_index,
										&(v[1].glo->b_name), v[1].height, v[1].b_index);
		case 3: return ydb_lock_s(t, 3, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index);
		case 4: return ydb_lock_s(t, 4, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index);
		case 5: return ydb_lock_s(t, 5, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index);
		case 6: return ydb_lock_s(t, 6, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index,
								  &(v[5].glo->b_name), v[5].height, v[5].b_index);
		case 7: return ydb_lock_s(t, 7, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index,
								  &(v[5].glo->b_name), v[5].height, v[5].b_index,
								  &(v[6].glo->b_name), v[6].height, v[6].b_index);
		case 8: return ydb_lock_s(t, 8, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index,
								  &(v[5].glo->b_name), v[5].height, v[5].b_index,
								  &(v[6].glo->b_name), v[6].height, v[6].b_index,
								  &(v[7].glo->b_name), v[7].height, v[7].b_index);
		case 9: return ydb_lock_s(t, 9, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index,
								  &(v[5].glo->b_name), v[5].height, v[5].b_index,
								  &(v[6].glo->b_name), v[6].height, v[6].b_index,
								  &(v[7].glo->b_name), v[7].height, v[7].b_index,
								  &(v[8].glo->b_name), v[8].height, v[8].b_index);
		case 10: return ydb_lock_s(t, 0, &(v[0].glo->b_name), v[0].height, v[0].b_index,
								  &(v[1].glo->b_name), v[1].height, v[1].b_index,
								  &(v[2].glo->b_name), v[2].height, v[2].b_index,
								  &(v[3].glo->b_name), v[3].height, v[3].b_index,
								  &(v[4].glo->b_name), v[4].height, v[4].b_index,
								  &(v[5].glo->b_name), v[5].height, v[5].b_index,
								  &(v[6].glo->b_name), v[6].height, v[6].b_index,
								  &(v[7].glo->b_name), v[7].height, v[7].b_index,
								  &(v[8].glo->b_name), v[8].height, v[8].b_index,
								  &(v[9].glo->b_name), v[9].height, v[9].b_index);

	}
	return YDB_ERR_PARAMINVALID;
}

/*  1 */
int ydb_lock(const c_ydb_entry & e, unsigned long long t) {
	vector<c_ydb_entry> v {e};
	return ydb_lock(v, t);
}

/*  2 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1};
	return ydb_lock(v, t);
}

/*  3 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e3, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e3};
	return ydb_lock(v, t);
}

/*  4 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3};
	return ydb_lock(v, t);
}

/*  5 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4};
	return ydb_lock(v, t);
}

/*  6 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, const c_ydb_entry & e5, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4, e5};
	return ydb_lock(v, t);
}

/*  7 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, const c_ydb_entry & e5, const c_ydb_entry & e6, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4, e5, e6};
	return ydb_lock(v, t);
}

/*  8 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, const c_ydb_entry & e5, const c_ydb_entry & e6, const c_ydb_entry & e7, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4, e5, e6, e7};
	return ydb_lock(v, t);
}

/*  9 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, const c_ydb_entry & e5, const c_ydb_entry & e6, const c_ydb_entry & e7, const c_ydb_entry & e8, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4, e5, e6, e7, e8};
	return ydb_lock(v, t);
}

/* 10 */
int ydb_lock(const c_ydb_entry & e0, const c_ydb_entry & e1, const c_ydb_entry & e2, const c_ydb_entry & e3, const c_ydb_entry & e4, const c_ydb_entry & e5, const c_ydb_entry & e6, const c_ydb_entry & e7, const c_ydb_entry & e8, const c_ydb_entry & e9, unsigned long long t) {
	vector<c_ydb_entry> v {e0, e1, e2, e3, e4, e5, e6, e7, e8, e9};
	return ydb_lock(v, t);
}

