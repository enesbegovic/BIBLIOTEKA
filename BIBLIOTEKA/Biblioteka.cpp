#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
#include "Posudba.h"
#include "Biblioteka.h"
using namespace std;
Biblioteka::Biblioteka(string n) {
	naziv = n;
}
ostream& operator<<(ostream& COUT, const Biblioteka& b) {
	COUT << "Naziv Biblioteke: " << b.naziv << endl;
	COUT << "Knjige:" << endl;
	for (const auto& x : b.knjige) {
		COUT << x.second << endl;
	}
	COUT << "Clanovi:" << endl;
	for (const auto& x : b.clanovi) {
		COUT << x.second << endl;
	}
	COUT << "Posudbe:" << endl;
	for (const auto& posudba : b.posudbe) {
		COUT << posudba << endl;
	}
	return COUT;
}