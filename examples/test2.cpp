/*
 Attention, modifies global ^counter

 Error handling with try-catch
*/

#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;

extern int ydb_global_throw_error;

int main() {
	string ind;
	c_ydb_global _g("^g");
	
	_g.kill();
	for (int i = 1; i <=20; i+= 3)
		_g[i] = i*i;
	ind = "", ydb_global_throw_error = 0;
	while (ind = (string) _g[ind].nextSibling(), ind != "")
		cout << ind << " " << (string) _g[ind] << endl;
	ydb_global_throw_error = 1;

for (int i = 0; i <= 20; i++) {
		cout << i << ": ";
		try {
			cout << _g[i];
		}
		catch (int errorcode) {
			cout << "error " << errorcode;
		}
		cout << endl;
	}
}
