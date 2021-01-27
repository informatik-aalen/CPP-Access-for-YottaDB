#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	c_ydb_global _log("^log"), _g("^g");
	_log[++_log] = "Hallo";
	cout << _log << endl;
	indexList l, l2 {"2","3"};
	cout <<  _g(l2) << endl;;
	while (l = _g(l).query(), l.size()) {
		for (unsigned int i = 0; i < l.size(); i++)
		cout << " " << l[i];
		cout << ":" << _g(l)<< endl;
	}
}
