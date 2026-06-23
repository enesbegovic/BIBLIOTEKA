#include <iostream>
#include <fstream>
#include <string>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
#include "Posudba.h"
using namespace std;
Posudba::Posudba(string isbn, string clanska, Datum datPos, bool vracena, Datum datVracanja) {
	isbnKnjige = isbn;
	clanskaClana = clanska;
	datumPosudbe = datPos;
	this->vracena = vracena;
	datumVracanja = datVracanja;
}
ostream& operator<<(ostream& COUT, const Posudba& p) {
	COUT << "ISBN Knjige: " << p.isbnKnjige << endl;
	COUT << "Clanska kartica Clana: " << p.clanskaClana << endl;
	COUT << "Datum Posudbe: " << p.datumPosudbe;
	if (p.vracena) {
		COUT << "Datum Vracanja: " << p.datumVracanja;
	}
	else {
		COUT << "Knjiga nije vracena!" << endl;
	}
	return COUT;
}
string Posudba::GetISBNKnjige()const {
	return isbnKnjige;
}
string Posudba::GetClanskaClana()const {
	return clanskaClana;
}
Datum Posudba::GetDatumPosudbe()const {
	return datumPosudbe;
}
bool Posudba::JeVracena()const {
	return vracena;
}