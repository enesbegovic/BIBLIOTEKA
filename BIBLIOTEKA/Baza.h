#pragma once
#include "sqlite3.h"
#include <string>
using namespace std;
class Baza {
	sqlite3* db;
public:
	Baza(string putanjaBaze = "BIBLIOTEKA.db");
	~Baza();
	void KreirajTabele();
	void IzvrsiUpit(string sql, string PORUKAGRESKE);
	void PostaviInfoBiblioteke(string Naziv,string Adresa);
	void PrikaziInfoBiblioteke();
	int BrojInfo();
	void DodajKnjigu(string naslov,string autor,string isbn);
	void ObrisiKnjigu(string isbn);
	void PrikaziSveKnjige();
	int BrojKnjiga();
	void DodajClana(string imePrezime,string brojClanskeKartice);
	void ObrisiClana(string brojClanskeKartice);
	void PrikaziSveClanove();
	int BrojClanova();
	void PosudiKnjigu(string Clanska, string isbn,string DatumPosudbe);
	void VratiKnjigu(string Clanska, string isbn, string DatumVracanja);
	int StatusPosudbe(string Clanska,string isbn);
	void PregledPosudbi();
	int BrojPosudbi();
	void UkloniPosudbu(string Clanska, string isbn);
	void DodajClanaDodajPosudbu(string ImePrezime, string Clanska, string isbn, string DatumPosudbe);
};