#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Knjiga.h"
using namespace std;
class Clan {
	string imePrezime;
	string brojClanskeKarte;
public:
	Clan(string ip = "---", string bck = "---");
	friend ostream& operator<<(ostream& COUT, const Clan& c);
	string GetBrojClanskeKarte()const;
};