#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
#include "Posudba.h"
#include "Biblioteka.h"
using namespace std;
Biblioteka::Biblioteka(string n) {
	naziv = n;
}
ostream& operator<<(ostream& COUT, const Biblioteka& b) {
	COUT << "Naziv Biblioteke: " << b.naziv << endl;
	COUT << "Knjige:" << endl;
	for (const auto& x1 : b.knjige) {
		COUT << x1.second << endl;
	}
	COUT << "Clanovi:" << endl;
	for (const auto& x2 : b.clanovi) {
		COUT << x2.second << endl;
	}
	COUT << "Posudbe:" << endl;
	for (const auto& posudba : b.posudbe) {
		COUT << posudba << endl;
	}
	return COUT;
}
bool Biblioteka::DodajKnjigu(Knjiga k) {
	if (knjige.find(k.GetISBN()) != knjige.end()) {
		return false; 
	}
	knjige[k.GetISBN()] = k;
	return true;
}
bool Biblioteka::DodajClana(Clan c) {
	if (clanovi.find(c.GetBrojClanskeKarte()) != clanovi.end()) {
		return false;
	}
	clanovi[c.GetBrojClanskeKarte()] = c;
	return true;
}
bool Biblioteka::UkloniKnjigu(string isbn) {
	auto it = knjige.find(isbn);
	if (it != knjige.end()) {
		knjige.erase(it);
		return true;
	}
	return false;
}
bool Biblioteka::UkloniClana(string brojClanskeKarte) {
	auto it = clanovi.find(brojClanskeKarte);
	if (it != clanovi.end()) {
		clanovi.erase(it);
		return true;
	}
	return false;
}
bool Biblioteka::PosudiKnjigu(string isbn, string brojClanskeKarte, Datum datumPosudbe) {
	if (knjige.find(isbn) == knjige.end() || clanovi.find(brojClanskeKarte) == clanovi.end()) {
		return false;
	}
	for (const auto& posudba : posudbe) {
		if (posudba.GetISBNKnjige() == isbn && !posudba.JeVracena()) {
			return false;
		}
	}
	posudbe.emplace_back(isbn, brojClanskeKarte, datumPosudbe, false);
	return true;
}
bool Biblioteka::VratiKnjigu(string isbn, string brojClanskeKarte, Datum datumVracanja) {
	for (auto& posudba : posudbe) {
		if (posudba.GetISBNKnjige() == isbn && posudba.GetClanskaClana() == brojClanskeKarte && !posudba.JeVracena()) {
			posudba = Posudba(isbn, brojClanskeKarte, posudba.GetDatumPosudbe(), true, datumVracanja);
			return true;
		}
	}
	return false;
}
void Biblioteka::PregledPosudbi() {
	for (const auto& posudba : posudbe) {
		cout << posudba << endl;
	}
}
bool Biblioteka::UkloniPosudbu(string isbn, string brojClanskeKarte) {
	for (auto it = posudbe.begin(); it != posudbe.end(); ++it) {
		if (it->GetISBNKnjige() == isbn && it->GetClanskaClana() == brojClanskeKarte) {
			posudbe.erase(it);
			return true;
		}
	}
	return false;
}