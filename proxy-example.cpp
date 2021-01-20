// see http://www.cplusplus.com/forum/general/1724/

#include <iostream>
using namespace std;

class Proxy;
class Array;

class Array {
public:
	class Proxy { // Not needed by main-programmer
	public:
		Array & _a;
		int index[32], h;
		Proxy (Array*, int);
		Proxy (Array*);
		Proxy & operator[](int);
		operator string ();
	};


	string _n;
	Array(string); // Normal constructor
	Array(const Array &); // Copy-Constructor
	Array & operator=(const Array &); // Assignment
	Proxy operator[](int);
};



// Code for Array
Array::Array(string name) : _n(name){
	cout  << "name-Constructor " << name << " at address " << this << endl;
}
Proxy Array::operator[](int i) {
	cout << "index 0: " << i << endl;
	return Proxy(this, i);
}

Array & Array::operator=(const Array & re ) {
	cout << _n << "=" << re._n << endl;
	return *this;
}

Array::Array(const Array & re ) {
	_n = re._n;
	cout << "Copy-Constructor " << re._n << " at address " << this << endl;
}


// Code for Proxy
Proxy::Proxy(Array* a, int i) : _a(*a) {
	index[0] = i, h = 1;
	cout << "Proxy-konstruktor " << i << " " << & _a << endl;
}
Proxy::Proxy(Array* a) : _a(*a), h(0) {
}
Proxy & Proxy::operator[](int j) {
	index[h++] =  j;
	return * this;
}
Proxy::operator string (){
	string s = _a._n;
	for (int i = 0; i < h; i++)
		s += " " + to_string(index[i]);
	return s;
}

void operator << (const Proxy & p, int n) {
	cout << "h = " << p.h << endl;
	Proxy p2 = p;
	cout << (string) p2[321][4711] << endl;
}

void operator << (const Array & a, int n) {
	Proxy((Array *)&a)<<n;
}

int main() {
	Array a("^a"), b("^b"), c("^c");
	c = a; // Assignment!!!
	Array d = b; // Copy-Constructor !!!!!
	Array e(b); // Copy-Constructor

	cout << (string) c[4711][2][123] << endl;
	cout << (string) c[321] << endl;
	a[123] << 2;
	a << 321;
	a[-1];
}
