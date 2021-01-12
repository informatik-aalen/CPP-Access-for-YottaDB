/*
Attention, kills and modifies globals ^g and ^counter

Error handling via method rc()
*/
#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	c_ydb_global _g("^g"), _counter("^counter");
	string ind, v = "Hello world";
	cout << "counter: " << (_counter += 2) << endl;
	_g.kill();
	_g[4][8] = "g_4_8";
	_g["2"] = 222;
	_g[3] = 333;
	_g["A99"] = "This is A99";
	_g["A100"] = v;
	_g["A2"] = v + " - " + v;
	_g[7] = 777;

	ind = ""; // now $ORDER-loop
	while (ind = _g[ind].next(),  ind != "") {
		if (v = _g[ind], !_g.rc())
			cout << ind << " = " << v << endl;
		else
			cout << ind << " = n.d." << endl;
	}
	return 0;
}
