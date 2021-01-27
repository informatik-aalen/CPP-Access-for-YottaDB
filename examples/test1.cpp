/*
Attention, kills and modifies globals ^g and ^counter

Error handling via method last_error()
*/
#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	c_ydb_global _g("^g"), _counter("^counter");
	int a;
	string v = "Hello world";
	cout << "counter: " << --_counter << endl;
	cout << "counter: " << (_counter += 2) << endl;
	_g.kill();
	_g[4][8] = "g_4_8";
	_g = 4712;
	_g["4"][8] = "g_4_8 2";
	_g["2"]["3"] = 222;
	_g[3] = 333;
	_g["A99"] = "This is A99";
	_g["A100"] = v;
	_g["A2"] = v + " - " + v;
	_g[7] = 777;
	v =  _g["A99"];
	a = +_g[7];
	cout << a << " " << _g << endl;
	indexList l = indexList{"2"};
	cout << _g(l)[3] << endl;
	return 0;
}
