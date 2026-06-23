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
void Biblioteka::SacuvajBibliotekuUFajl() {
	ofstream fajl("biblioteka.txt");
	if (!fajl) {
		cerr << "Greska pri otvaranju fajla za cuvanje!" << endl;
		return;
	}
	fajl << naziv << endl;
	fajl << knjige.size() << endl;
	for (auto x1 : knjige) {
		x1.second.SacuvajKnjiguUFajl(fajl);
	}
	fajl << clanovi.size() << endl;
	for (auto x2 : clanovi) {
		x2.second.SacuvajClanaUFajl(fajl);
	}
	fajl << posudbe.size() << endl;
	for (auto posudba : posudbe) {
		posudba.SacuvajPosudbuUFajl(fajl);
	}
	fajl.close();
}
void Biblioteka::UcitajBibliotekuIzFajla() {
	ifstream fajl("biblioteka.txt");
	if (!fajl) {
		cerr << "Greska pri otvaranju fajla za ucitavanje!" << endl;
		return;
	}
	getline(fajl, naziv);
	int brojKnjiga;
	fajl >> brojKnjiga;
	fajl.ignore();
	for (size_t i = 0; i < brojKnjiga; ++i) {
		Knjiga k;
		k.UcitajKnjiguIzFajla(fajl);
		knjige[k.GetISBN()] = k;
	}
	int brojClanova;
	fajl >> brojClanova;
	fajl.ignore();
	for (size_t i = 0; i < brojClanova; ++i) {
		Clan c;
		c.UcitajClanaIzFajla(fajl);
		clanovi[c.GetBrojClanskeKarte()] = c;
	}
	int brojPosudbi;
	fajl >> brojPosudbi;
	fajl.ignore();
	for (size_t i = 0; i < brojPosudbi; ++i) {
		Posudba p;
		p.UcitajPosudbuIzFajla(fajl);
		posudbe.push_back(p);
	}
	fajl.close();
}