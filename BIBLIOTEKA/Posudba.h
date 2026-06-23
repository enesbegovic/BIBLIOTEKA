#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
using namespace std;
class Posudba {
	string isbnKnjige;
	string clanskaClana;
	Datum datumPosudbe;
	bool vracena;
	Datum datumVracanja;
public:
	Posudba(string isbn = "---", string clanska = "---", Datum datPos = Datum(), bool vracena = false, Datum datVracanja = Datum());
	friend ostream& operator<<(ostream& COUT, const Posudba& p);
	string GetISBNKnjige()const;
	string GetClanskaClana()const;
	Datum GetDatumPosudbe()const;
	bool JeVracena()const;
	void SacuvajPosudbuUFajl(ofstream& fajl);
	void UcitajPosudbuIzFajla(ifstream& fajl);
};