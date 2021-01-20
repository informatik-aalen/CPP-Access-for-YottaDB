/*
 Converts an object to a tree (global structure) and stores it
 (not implemented for root nodes)
 */
#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;

extern int ydb_global_throw_error;

class c_customer {
public:
	string ln, fn;
	int birthday;
};

// Following two operators must be implemented one time class-specific
// customer 2 YottaDB
void operator << (const c_ydb_entry & e, c_customer c) {
	c_ydb_entry e1(e),e2(e), e3(e); // little bit tricky because no member of class c_ydb_global...
	e1["ln"] = c.ln, e2["fn"] = c.fn, e3["bd"] = c.birthday;
 }

// YottaDB 2 customer
void operator << (c_customer & c, c_ydb_entry e) {
	c.ln = (string) c_ydb_entry(e)["ln"];
	c.fn = (string) c_ydb_entry(e)["fn"];
	c.birthday = + c_ydb_entry(e)["bd"];
}

int main() {
	ydb_global_throw_error = 1;

	c_customer c_1 = {"Doe", "John", 19700101}, c_2;
	c_ydb_global _g("^g");
	int nr = ++_g;
	_g[nr] << c_1; // Stores the complete object c_1 as a tree in ^g(nr)
	c_2 << _g[nr]; // retrieves the tree ^g(nr) and converts it to object c_2
	cout << "nr " << nr << ": " << c_2.ln << ", " << c_2.fn << " * " << c_2.birthday << endl;
}
