#include <iostream>
#include <string>
#include "ydb-global.h"
using namespace std;


int main() {
	indexList l{};
	c_ydb_global _g("^g");
	while (l = _g(l).query(), !_g.last_error()) {
		for (unsigned int i = 0; i < l.size(); i++)
			cout << l[i] << " " ;
		cout << "=" <<_g(l)<< endl;
	}
	return 0;
}
