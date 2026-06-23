#include <iostream>
#include <string>
#include <fstream>
#include "Knjiga.h"
using namespace std;
Knjiga::Knjiga(string n, string a, string isbn) {
	naslov = n;
	autor = a;
	ISBN = isbn;
}
ostream& operator<<(ostream& COUT, const Knjiga& k) {
	COUT << "Naslov Knjige: " << k.naslov << endl;
	COUT << "Autor: " << k.autor << endl;
	COUT << "ISBN: " << k.ISBN << endl;
	return COUT;
}