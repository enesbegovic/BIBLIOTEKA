#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
#include "Posudba.h"
using namespace std;
class Biblioteka {
	string naziv;
	map<string, Knjiga> knjige; 
	map<string, Clan> clanovi; 
	vector<Posudba> posudbe;
public:
	Biblioteka(string n = "---");
	friend ostream& operator<<(ostream& COUT, const Biblioteka& b);
	bool DodajKnjigu(Knjiga k);
	bool DodajClana(Clan c);
	bool UkloniKnjigu(string isbn);
	bool UkloniClana(string brojClanskeKarte);
	bool PosudiKnjigu(string isbn, string brojClanskeKarte, Datum datumPosudbe);
	bool VratiKnjigu(string isbn, string brojClanskeKarte, Datum datumVracanja);
	void PregledPosudbi();
};