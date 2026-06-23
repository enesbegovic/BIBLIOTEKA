#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Knjiga {
	string naslov;
	string autor;
	string ISBN;
public:
	Knjiga(string n = "---", string a = "---", string isbn = "---");
	friend ostream& operator<<(ostream& COUT, const Knjiga& k);
	string GetISBN()const;
};