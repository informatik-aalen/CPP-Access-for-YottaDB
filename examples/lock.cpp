#include <iostream>
#include <unistd.h>
#include "ydb-global.h"
using namespace std;


int main() {
	c_ydb_global _g("^g");
	cout << "start this programm in multiple parallel jobs!" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Waiting for lock ..." << endl;
		_g.lock_inc(10 * 1000000000Ull);
		cout << "go ahead ..." << endl;
		sleep(1);
		cout << "releasing ..." << endl;
		_g.lock_dec();
	}
	return 0;
}
