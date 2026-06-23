#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Knjiga.h"
#include "Clan.h"
#include "Datum.h"
#include "Posudba.h"
#include "Biblioteka.h"
using namespace std;
int main() {
	Biblioteka biblioteka;
	biblioteka.UcitajBibliotekuIzFajla();
	int izbor;
	do {
		cout << "MENI IZBORNIKA:" << endl;
		cout << "1.Dodaj knjigu" << endl;
		cout << "2.Dodaj clana" << endl;
		cout << "3.Posudi knjigu" << endl;
		cout << "4.Vrati knjigu" << endl;
		cout << "5.Pregled posudbi" << endl;
		cout << "6.Ukloni knjigu" << endl;
		cout << "7.Ukloni clana" << endl;
		cout << "8.Ukloni posudbu" << endl;
		cout << "9.Pregled biblioteke" << endl;
		cout << "10.Izlaz" << endl;
		cin >> izbor;
		cin.ignore();
		switch (izbor) {
		case 1: {
			string naslov, autor, isbn;
			cout << "Unesite naslov knjige: ";
			getline(cin, naslov);
			cout << "Unesite autora: ";
			getline(cin, autor);
			cout << "Unesite ISBN: ";
			getline(cin, isbn);
			Knjiga k(naslov, autor, isbn);
			if (biblioteka.DodajKnjigu(k)) {
				cout << "Knjiga dodana." << endl;
			}
			else {
				cout << "Knjiga sa istim ISBN vec postoji." << endl;
			}
			break;
		}
		case 2: {
			string imePrezime, brojClanskeKarte;
			cout << "Unesite ime i prezime clana: ";
			getline(cin, imePrezime);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			Clan c(imePrezime, brojClanskeKarte);
			if (biblioteka.DodajClana(c)) {
				cout << "Clan dodan." << endl;
			}
			else {
				cout << "Clan sa istim brojem clanske karte vec postoji." << endl;
			}
			break;
		}
		case 3: {
			string isbn, brojClanskeKarte;
			int dan, mjesec, godina;
			cout << "Unesite ISBN knjige: ";
			getline(cin, isbn);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			cout << "Unesite dan posudbe: ";
			cin >> dan;
			cout << "Unesite mjesec posudbe: ";
			cin >> mjesec;
			cout << "Unesite godinu posudbe: ";
			cin >> godina;
			cin.ignore();
			Datum datumPosudbe(dan, mjesec, godina);
			if (biblioteka.PosudiKnjigu(isbn, brojClanskeKarte, datumPosudbe)) {
				cout << "Knjiga posudjena." << endl;
			}
			else {
				cout << "Greska pri posudbi knjige." << endl;
			}
			break;
		}
		case 4: {
			string isbn, brojClanskeKarte;
			int dan, mjesec, godina;
			cout << "Unesite ISBN knjige: ";
			getline(cin, isbn);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			cout << "Unesite dan vracanja: ";
			cin >> dan;
			cout << "Unesite mjesec vracanja: ";
			cin >> mjesec;
			cout << "Unesite godinu vracanja: ";
			cin >> godina;
			cin.ignore();
			Datum datumVracanja(dan, mjesec, godina);
			if (biblioteka.VratiKnjigu(isbn, brojClanskeKarte, datumVracanja)) {
				cout << "Knjiga vracena." << endl;
			}
			else {
				cout << "Greska pri vracanju knjige." << endl;
			}
			break;
		}
		case 5: {
			biblioteka.PregledPosudbi();
			break;
		}
		case 6: {
			string isbn;
			cout << "Unesite ISBN knjige za uklanjanje: ";
			getline(cin, isbn);
			if (biblioteka.UkloniKnjigu(isbn)) {
				cout << "Knjiga uklonjena." << endl;
			}
			else {
				cout << "Greska pri uklanjanju knjige." << endl;
			}
			break;
		}
		case 7: {
			string brojClanskeKarte;
			cout << "Unesite broj clanske karte za uklanjanje: ";
			getline(cin, brojClanskeKarte);
			if (biblioteka.UkloniClana(brojClanskeKarte)) {
				cout << "Clan uklonjen." << endl;
			}
			else {
				cout << "Greska pri uklanjanju clana." << endl;
			}
			break;
		}
		case 8: {
			string isbn, brojClanskeKarte;
			cout << "Unesite ISBN knjige za uklanjanje: ";
			getline(cin, isbn);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			if (biblioteka.UkloniPosudbu(isbn, brojClanskeKarte)) {
				cout << "Posudba uklonjena." << endl;
			}
			else {
				cout << "Greska pri uklanjanju posudbe." << endl;
			}
			break;
		}
		case 9: {
			cout << biblioteka << endl;
			break;
		}
		case 10: {
			biblioteka.SacuvajBibliotekuUFajl();
			cout << "DOVIDJENJE!" << endl;
			break;
		}
		default: {
			cout << "Nepostojeca opcija." << endl;
			break;
		}
		}
	}while (izbor != 10);
	
}