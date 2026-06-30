#include <iostream>
#include <string>
#include "Baza.h"
using namespace std;
int main() {
	Baza baza;
	baza.KreirajTabele();
	baza.PostaviInfoBiblioteke("GRADSKA BIBLIOTEKA MOSTAR", "BULEVAR BR.77");
	baza.PrikaziInfoBiblioteke();
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
		cout << "9.Pregled knjiga" << endl;
		cout << "10.Pregled clanova" << endl;
		cout << "11.Izlaz" << endl;
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
			if (baza.DodajKnjigu(naslov,autor,isbn)) {
				cout << "Knjiga dodana." << endl;
			}
			else {
				cout << "GRESKA PRI DODAVANJU!!!" << endl;
			}
			break;
		}
		case 2: {
			string imePrezime, brojClanskeKarte;
			cout << "Unesite ime i prezime clana: ";
			getline(cin, imePrezime);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			if (baza.DodajClana(imePrezime,brojClanskeKarte)) {
				cout << "Clan dodan." << endl;
			}
			else {
				cout << "GRESKA PRI DODAVANJU!!!" << endl;
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
			string datumPosudbeStr = to_string(dan) + "." + to_string(mjesec) + "." + to_string(godina);
			if (baza.PosudiKnjigu(isbn,brojClanskeKarte,datumPosudbeStr)) {
				cout << "Knjiga posudjena." << endl;
			}
			else {
				cout << "GRESKA PRI POSUDBI!!!" << endl;
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
			string datumVracanjaStr = to_string(dan) + "." + to_string(mjesec) + "." + to_string(godina);
			if (baza.VratiKnjigu(isbn,brojClanskeKarte,datumVracanjaStr)) {
				cout << "Knjiga vracena." << endl;
			}
			else {
				cout << "GRESKA PRI VRACANJU KNJIGE!!!" << endl;
			}
			break;
		}
		case 5: {
			baza.PregledPosudbi();
			break;
		}
		case 6: {
			string isbn;
			cout << "Unesite ISBN knjige za uklanjanje: ";
			getline(cin, isbn);
			if (baza.ObrisiKnjigu(isbn)) {
				cout << "Knjiga uklonjena." << endl;
			}
			else {
				cout << "GRESKA PRI UKLANJANJU KNJIGE!!!" << endl;
			}
			break;
		}
		case 7: {
			string brojClanskeKarte;
			cout << "Unesite broj clanske karte za uklanjanje: ";
			getline(cin, brojClanskeKarte);
			if (baza.ObrisiClana(brojClanskeKarte)) {
				cout << "Clan uklonjen." << endl;
			}
			else {
				cout << "GRESKA PRI UKLANJANJU CLANA!!!" << endl;
			}
			break;
		}
		case 8: {
			string isbn, brojClanskeKarte;
			cout << "Unesite ISBN knjige za uklanjanje: ";
			getline(cin, isbn);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			if (baza.UkloniPosudbu(isbn,brojClanskeKarte)) {
				cout << "Posudba uklonjena." << endl;
			}
			else {
				cout << "GRESKA PRI UKLANJANJU POSUDBE!!!" << endl;
			}
			break;
		}
		case 9: {
			baza.PrikaziSveKnjige();
			break;
		}
		case 10:
		{
			baza.PrikaziSveClanove();
			break;
		}
		case 11: {
			cout << "DOVIDJENJE!" << endl;
			break;
		}
		default: {
			cout << "Nepostojeca opcija." << endl;
			break;
		}
		}
	}while (izbor != 11);
	
}