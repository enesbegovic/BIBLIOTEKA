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
	for (const auto& x : b.knjige) {
		COUT << x.second << endl;
	}
	COUT << "Clanovi:" << endl;
	for (const auto& x : b.clanovi) {
		COUT << x.second << endl;
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