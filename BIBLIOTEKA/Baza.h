#pragma once
#include "sqlite3.h"
#include <string>
using namespace std;
class Baza {
	sqlite3* db;
public:
	Baza();
	~Baza();
	void KreirajTabele();
	bool PostaviInfoBiblioteke(string Naziv,string Adresa);
	void PrikaziInfoBiblioteke();
	bool DodajKnjigu(string naslov,string autor,string isbn);
	bool ObrisiKnjigu(string isbn);
	void PrikaziSveKnjige();
	bool DodajClana(string imePrezime,string brojClanskeKartice);
	bool ObrisiClana(string brojClanskeKartice);
	void PrikaziSveClanove();
	bool PosudiKnjigu(string isbn, string Clanska,string DatumPosudbe);
	bool VratiKnjigu(string isbn, string Clanska, string DatumVracanja);
	void PregledPosudbi();
	bool UkloniPosudbu(string isbn, string Clasnka);
};