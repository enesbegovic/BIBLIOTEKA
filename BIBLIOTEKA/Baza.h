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
	void IzvrsiUpit(string sql, string PORUKAGRESKE);
	void PostaviInfoBiblioteke(string Naziv,string Adresa);
	void PrikaziInfoBiblioteke();
	void DodajKnjigu(string naslov,string autor,string isbn);
	void ObrisiKnjigu(string isbn);
	void PrikaziSveKnjige();
	void DodajClana(string imePrezime,string brojClanskeKartice);
	void ObrisiClana(string brojClanskeKartice);
	void PrikaziSveClanove();
	void PosudiKnjigu(string Clanska, string isbn,string DatumPosudbe);
	void VratiKnjigu(string Clanska, string isbn, string DatumVracanja);
	void PregledPosudbi();
	void UkloniPosudbu(string Clanska, string isbn);
	void DodajClanaDodajPosudbu(string ImePrezime, string Clanska, string isbn, string DatumPosudbe);
};