/*
 Exports ^g(1) (in M-syntax) to JSON-string
 Winfried Bantel, Aalen University, 2021
*/

#include <jsoncpp/json/json.h>
#include "ydb-global.h"

using namespace std;

int main(int argc, char * argv[]) {
	Json::Value val;
	c_ydb_global _g("^g");
	string json;
	
	_g[1].kill();
	_g[1]["m"][0] = "YottaDB";
	_g[1]["m"][1] = "Reference Standard M";

	val << _g[1]; // ^g(1) is copied to JSON-Value val
	
	Json::StreamWriterBuilder builder;
	builder.settings_["precision"] = 10;
	json = Json::writeString(builder, val);
	cout << json << endl;

	return 0;
}
