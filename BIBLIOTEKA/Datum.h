#pragma once
#include <iostream>
#include <fstream>
#include "Knjiga.h"
#include "Clan.h"
using namespace std;
class Datum {
	int dan;
	int mjesec;
	int godina;
public:
	Datum(int d = 1, int m = 1, int g = 2000);
	friend ostream& operator<<(ostream& COUT, const Datum& dat);
};