/*
 Imports contents of a JSON-file to ^g(1) (in M-syntax)
 Winfried Bantel, Aalen University, 2021
*/

#include <fstream>
#include <jsoncpp/json/json.h>
#include "ydb-global.h"

using namespace std;

int main(int argc, char * argv[]) {
	Json::Value val;
	c_ydb_global _g("^g");
	ifstream("alice.json") >> val;
	_g[1] << val;
	cout << _g[1]["book"] << endl;
	return 0;
}
