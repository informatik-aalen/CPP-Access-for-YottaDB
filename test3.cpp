

#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	int n;
	c_ydb_global _log("^log");
	_log[++_log] = "hello";
	_log[++_log] = "world";
	_log[++_log] = "foo";
	_log[++_log] = "bar";

	n = stoi(_log);
	for (int i = 1; i <= n; i++)
		cout << i << ": " << _log[i] << endl;
}
