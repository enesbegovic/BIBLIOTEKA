#include <iostream>
#include <string>
#include <fstream>
#include "Knjiga.h"
#include "Clan.h"
using namespace std;
Clan::Clan(string ip, string bck) {
	imePrezime = ip;
	brojClanskeKarte = bck;
}
ostream& operator<<(ostream& COUT, const Clan& c) {
	COUT << "Ime i Prezime: " << c.imePrezime << endl;
	COUT << "Broj Clanske Karte: " << c.brojClanskeKarte << endl;
	return COUT;
}
string Clan::GetBrojClanskeKarte()const {
	return brojClanskeKarte;
}