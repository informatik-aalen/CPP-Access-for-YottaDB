/*
Imports a JSON-string in YottaDB
*/
#include <iostream>
#include <sstream>
#include "ydb-global.h"
#include <jsoncpp/json/json.h>
using namespace std;

int main() {
	extern int ydb_global_throw_error;
	int nr;
	extern string json;
	Json::Value val;
	ydb_global_throw_error = 1;
	c_ydb_global _g("^g");
	istringstream iss (json);
	iss >> val, val >> _g[nr = ++_g];
	cout << "have a look at " << _g.getName() << "[" << nr << "]" << endl;
	return 0;
}

string json = R"(
{
	"firstName": "John",
	"lastName" : "Smith",
	"age"      : 25,
	"address"  :
	{
		"streetAddress": "21 2nd Street",
		"city"         : "New York",
		"state"        : "NY",
		"postalCode"   : "10021"
	},
	"phoneNumber":
	[
		{
			"type"  : "",
			"number": "212 555-1234"
		},
		{
			"type"  : "fax",
			"number": "646 555-4567"
		}
	]
}
)";

