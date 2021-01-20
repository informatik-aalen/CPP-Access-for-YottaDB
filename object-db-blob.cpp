/*
 Converts an object to a blob and stores it
 (not implemented for root nodes)
 */
#include <iostream>
#include <string>
#include <map>
#include "ydb-global.h"
using namespace std;

class c_customer {
public:
	string ln, fn;
};

// Following two operators must be implemented one time class-specific
// customer 2 YottaDB
void operator << (const c_ydb_entry & e, c_customer c) {
	// 1) Create blob from object
	c_ydb_entry e1(e);
	cout << "==> " << c.ln << endl;;
	size_t n = 2 * sizeof (size_t) + c.ln.length() + c.fn.length();
	char * p = new char (n), * p2 = p;
	*(size_t *) p2 = c.ln.length(), p2 += sizeof (size_t);
	memcpy(p2, c.ln.c_str(), c.ln.length()), p2 += c.ln.length();
	*(size_t *) p2 = c.fn.length(), p2 += sizeof (size_t);
	memcpy(p2, c.fn.c_str(), c.fn.length()), p2 += c.fn.length();
	// 2) now store blob
	e1 = string(p, n);
	delete p;
}

// YottaDB 2 customer
void operator << (c_customer & c, c_ydb_entry e) {
	string s = e;
	char * n = (char *) s.c_str();
	c.ln = string(n + sizeof(size_t), *(size_t *) n), n += sizeof(size_t) + *(size_t *) n;
	c.fn = string(n + sizeof(size_t), *(size_t *) n), n += sizeof(size_t) + *(size_t *) n;
}

int main() {
	c_customer c_1 = {"Doe", "John"}, c_2;
	c_ydb_global _g("^g");
	int nr = ++_g;
	_g[nr] << c_1; // Stores the complete object c_1 as a blob in ^g(nr)
	c_2 << _g[nr]; // retrieves the blob ^g(nr) and converts it to object c_2
	cout << "nr " << nr << ": " << c_2.ln << ", " << c_2.fn << endl;
}
