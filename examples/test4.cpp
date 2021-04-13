
#include <iostream>
#include <string>
#include <math.h>
#include "ydb-global.h"
using namespace std;


int main() {
	int n;
	indexList v{"Hallo","Welt"};
	c_ydb_global _log("^log"), _g("^g");
	_log.kill();
	_log[++_log] = "hello";
	_log[++_log] = "world";
	_log[++_log] = "foo";
	_log[++_log] = "bar";
	_log(v) = "more than one indexlist";
	
	cout << "last_error: " << _log.last_error() << endl;
	n = stoi(_log);
	for (int i = 1; i <= n; i++)
	cout << i << ": " << _log[i] << endl;

	_g.kill();
	for (int i = 1; i < 10; i++)
		_g[3.14][pow(10,-i)] = i;
	return 0;
}
