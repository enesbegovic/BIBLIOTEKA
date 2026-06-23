#include <iostream>
#include <fstream>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
using namespace std;
Datum::Datum(int d, int m, int g) {
	dan = d;
	mjesec = m;
	godina = g;
}
ostream& operator<<(ostream& COUT, const Datum& dat) {
	COUT << dat.dan << "." << dat.mjesec << "." << dat.godina << endl;
	return COUT;
}