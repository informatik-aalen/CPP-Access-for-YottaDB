/*
 Attention, modifies global ^counter

 Error handling with try-catch
*/

#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	// second parameter leads to error-throws
	c_ydb_global _g("^g", 1), _counter("^counter");
	cout << ++_counter << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << ": ";
		try {
			cout << _g[i];
		}
		catch (int errorcode) {
			cout << "not set";
		}
		cout << endl;
	}
}
