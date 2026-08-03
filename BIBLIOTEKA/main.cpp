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
		cout << "4.Dodaj clana i posudi knjigu" << endl;
		cout << "5.Vrati knjigu" << endl;
		cout << "6.Pregled posudbi" << endl;
		cout << "7.Ukloni knjigu" << endl;
		cout << "8.Ukloni clana" << endl;
		cout << "9.Ukloni posudbu" << endl;
		cout << "10.Pregled knjiga" << endl;
		cout << "11.Pregled clanova" << endl;
		cout << "12.Izlaz" << endl;
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
			baza.DodajKnjigu(naslov, autor, isbn);
			break;
		}
		case 2: {
			string imePrezime, brojClanskeKarte;
			cout << "Unesite ime i prezime: ";
			getline(cin, imePrezime);
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			baza.DodajClana(imePrezime, brojClanskeKarte);
			break;
		}
		case 3: {
			string isbn, brojClanskeKarte;
			int dan, mjesec, godina;
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			cout << "Unesite ISBN knjige: ";
			getline(cin, isbn);
			cout << "Unesite dan posudbe: ";
			cin >> dan;
			cout << "Unesite mjesec posudbe: ";
			cin >> mjesec;
			cout << "Unesite godinu posudbe: ";
			cin >> godina;
			cin.ignore();
			string datumPosudbeISO = to_string(godina) + "-" + (mjesec < 10 ? "0" : "") + to_string(mjesec) + "-" + (dan < 10 ? "0" : "") + to_string(dan);
			baza.PosudiKnjigu(brojClanskeKarte, isbn, datumPosudbeISO);
			break;
		}
		case 4:
		{
			string ime;
			cout << "Unesite ime i prezime: ";
			getline(cin, ime);
			string Clanska;
			cout << "Unesite broj clasnke kartice: ";
			getline(cin, Clanska);
			string isbn;
			cout << "Unesite isbn knjige: ";
			getline(cin, isbn);
			int dan, mjesec, godina;
			cout << "Unesite dan posudbe: ";
			cin >> dan;
			cout << "Unesite mjesec posudbe: ";
			cin >> mjesec;
			cout << "Unesite godinu posudbe: ";
			cin >> godina;
			cin.ignore();
			string datumPosudbeISO = to_string(godina) + "-" + (mjesec < 10 ? "0" : "") + to_string(mjesec) + "-" + (dan < 10 ? "0" : "") + to_string(dan);
			baza.DodajClanaDodajPosudbu(ime, Clanska, isbn, datumPosudbeISO);
			break;
		}
		case 5: {
			string isbn, brojClanskeKarte;
			int dan, mjesec, godina;
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			cout << "Unesite ISBN knjige: ";
			getline(cin, isbn);
			cout << "Unesite dan vracanja: ";
			cin >> dan;
			cout << "Unesite mjesec vracanja: ";
			cin >> mjesec;
			cout << "Unesite godinu vracanja: ";
			cin >> godina;
			cin.ignore();
			string datumVracanjaISO = to_string(godina) + "-" + (mjesec < 10 ? "0" : "") + to_string(mjesec) + "-" + (dan < 10 ? "0" : "") + to_string(dan);
			baza.VratiKnjigu(brojClanskeKarte, isbn, datumVracanjaISO);
			break;
		}
		case 6: {
			baza.PregledPosudbi();
			break;
		}
		case 7: {
			string isbn;
			cout << "Unesite ISBN knjige za uklanjanje: ";
			getline(cin, isbn);
			baza.ObrisiKnjigu(isbn);
			break;
		}
		case 8: {
			string brojClanskeKarte;
			cout << "Unesite broj clanske karte za uklanjanje: ";
			getline(cin, brojClanskeKarte);
			baza.ObrisiClana(brojClanskeKarte);
			break;
		}
		case 9: {
			string isbn, brojClanskeKarte;
			cout << "Unesite broj clanske karte: ";
			getline(cin, brojClanskeKarte);
			cout << "Unesite ISBN knjige: ";
			getline(cin, isbn);
			baza.UkloniPosudbu(brojClanskeKarte,isbn);
			break;
		}
		case 10: {
			baza.PrikaziSveKnjige();
			break;
		}
		case 11:
		{
			baza.PrikaziSveClanove();
			break;
		}
		case 12: {
			cout << "DOVIDJENJE!" << endl;
			break;
		}
		default: {
			cout << "Nepostojeca opcija." << endl;
			break;
		}
		}
	}while (izbor != 12);
	
}