/* count and report word frequencies for http://www.cs.duke.edu/csed/code/code2007/
 
 uses C++-wrapper for yottadb
 Winfried Bantel
 */

#include "libyottadb.h"	/* for ydb_* macros/prototypes/typedefs */
#include <iostream>
#include <string>
#include <algorithm>
#include "ydb-global.h"
using namespace std;

int main()
{
	string w, n;
	c_ydb_global _word("word"),_index("index");
	_word.kill(), _index.kill();
	while(cin >> w) {
		transform(w.begin(), w.end(), w.begin(), [](unsigned char c){ return std::tolower(c); });
		_word[w]++;
	}
	w="";
	while(w = _word[w].nextSibling(), w != "")
		_index[_word[w]][w]="";
	n = w = "";
	while(n = _index[n].previousSibling(), n != "")
		while(w = _index[n][w].nextSibling(), w != "")
			cout << n << "\t" << w << "\n";
	return 0;
}
