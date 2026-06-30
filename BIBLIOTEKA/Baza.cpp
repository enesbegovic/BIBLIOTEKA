#include <iostream>
#include "Baza.h"
using namespace std;
Baza::Baza() {
	sqlite3_open("BIBLIOTEKA.db", &db);
}
Baza::~Baza() {
	sqlite3_close(db);
}
void Baza::KreirajTabele() {
	char * errMsg = nullptr;
	string KreirajKnjige=
	"CREATE TABLE IF NOT EXISTS Knjige("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"Naslov TEXT NOT NULL,"
		"Autor TEXT NOT NULL,"
		"ISBN TEXT NOT NULL UNIQUE);";
	sqlite3_exec(db, KreirajKnjige.c_str(), nullptr, nullptr, &errMsg);

	string KreirajClanove =
		"CREATE TABLE IF NOT EXISTS Clanovi("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"ImePrezime TEXT NOT NULL,"
		"BrojClanskeKartice TEXT NOT NULL UNIQUE);";
	sqlite3_exec(db, KreirajClanove.c_str(), nullptr, nullptr, &errMsg);

	string KreirajPosudbe =
		"CREATE TABLE IF NOT EXISTS Posudbe("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"ISBN TEXT NOT NULL,"
		"Clanska TEXT NOT NULL,"
		"DatumPosudbe TEXT NOT NULL,"
		"Vracena INTEGER DEFAULT 0,"
		"DatumVracanja TEXT);";
	sqlite3_exec(db, KreirajPosudbe.c_str(), nullptr, nullptr, &errMsg);

	string KreirajInfoBiblioteke =
		"CREATE TABLE IF NOT EXISTS InfoBiblioteke("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"Naziv TEXT NOT NULL,"
		"Adresa TEXT NOT NULL)";
	sqlite3_exec(db, KreirajInfoBiblioteke.c_str(), nullptr, nullptr, &errMsg);
}
bool Baza::PostaviInfoBiblioteke(string Naziv, string Adresa) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM InfoBiblioteke WHERE Naziv='" + Naziv + "' AND Adresa='" + Adresa + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count > 0)
		return false;
	string sql =
		"INSERT INTO InfoBiblioteke (Naziv,Adresa) VALUES('"
		+ Naziv + "', '" + Adresa + "');";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
void Baza::PrikaziInfoBiblioteke() {
	string sql =
		"SELECT * FROM InfoBiblioteke;";
	sqlite3_exec(db, sql.c_str(),
		[](void*, int kolone, char** podaci, char** nazivKolone) {
			for (int i = 0; i < kolone; i++)
				cout << nazivKolone[i] << ": " << podaci[i] << endl;
			cout << "---" << endl;
			return 0;
		}, nullptr, nullptr);
}
bool Baza::DodajKnjigu(string naslov, string autor, string isbn) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Knjige WHERE ISBN='" + isbn + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data,int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count > 0)
		return false;
	string sql =
		"INSERT INTO Knjige (naslov,autor,ISBN) VALUES('"
		+ naslov + "', '" + autor + "', '" + isbn + "');";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;

}
bool Baza::ObrisiKnjigu(string isbn) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Knjige WHERE ISBN='" + isbn + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count == 0)
		return false;
	string sql =
		"DELETE FROM Knjige WHERE ISBN='" + isbn + "';";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
void Baza::PrikaziSveKnjige() {
	string sql =
		"SELECT * FROM Knjige;";
	sqlite3_exec(db, sql.c_str(),
		[](void*, int kolone, char** podaci, char** nazivKolene) {
			for (int i = 0; i < kolone; i++)
				cout << nazivKolene[i] << ": " << podaci[i] << endl;
			cout << "---" << endl;
			return 0;

		}, nullptr, nullptr);
}
bool Baza::DodajClana(string imePrezime, string brojClanskeKartice) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Clanovi WHERE brojClanskeKartice='" + brojClanskeKartice + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count > 0)
		return false;
	string sql =
		"INSERT INTO Clanovi (imePrezime, brojClanskeKartice) VALUES('"
		+ imePrezime + "', '" + brojClanskeKartice + "');";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
bool Baza::ObrisiClana(string brojClanskeKartice) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Clanovi WHERE brojClanskeKartice='" + brojClanskeKartice + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count == 0)
		return false;
	string sql =
		"DELETE FROM Clanovi WHERE brojClanskeKartice='" + brojClanskeKartice + "';";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
void Baza::PrikaziSveClanove() {
	string sql =
		"SELECT * FROM Clanovi;";
	sqlite3_exec(db, sql.c_str(),
		[](void*, int kolone, char** podaci, char** nazivKolone) {
			for (int i = 0; i < kolone; i++)
				cout << nazivKolone[i] << ": " << podaci[i] << endl;
			cout << "---" << endl;
			return 0;
		}, nullptr, nullptr);
}
bool Baza::PosudiKnjigu(string isbn, string Clanska, string DatumPosudbe) {
	char* errMsg = nullptr;
	int countKnjiga = 0; 
	int countClan = 0; 
	int countPosudba = 0;
	string ProvjeraKnjiga =
		"SELECT COUNT(*) FROM Knjige WHERE ISBN='" + isbn + "';";
	sqlite3_exec(db, ProvjeraKnjiga.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &countKnjiga, nullptr);
	string ProvjeraClana =
		"SELECT COUNT(*) FROM Clanovi WHERE BrojClanskeKartice='" + Clanska + "';";
	sqlite3_exec(db, ProvjeraClana.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &countClan, nullptr);
	string ProvjeraPosudbe =
		"SELECT COUNT(*) FROM Posudbe WHERE ISBN='" + isbn + "' AND Vracena=0;";
	sqlite3_exec(db, ProvjeraPosudbe.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &countPosudba, nullptr);
	if (countKnjiga == 0 || countClan == 0 || countPosudba > 0)
		return false;
	string sql =
		"INSERT INTO Posudbe (ISBN, Clanska, DatumPosudbe,Vracena) VALUES('"
		+ isbn + "', '" + Clanska + "', '" + DatumPosudbe + "', 0);";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
bool Baza::VratiKnjigu(string isbn, string Clanska, string DatumVracanja) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Posudbe WHERE ISBN='" + isbn + "'AND Clanska='" + Clanska + "' AND Vracena=1;";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count > 0)
		return false;
	string sql =
		"UPDATE Posudbe SET Vracena=1, DatumVracanja='" + DatumVracanja + "'WHERE ISBN='" + isbn + "'AND Clanska='" + Clanska + "' AND Vracena= 0;";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}
void Baza::PregledPosudbi() {
	string sql =
		"SELECT ID, ISBN, Clanska, DatumPosudbe, "
		"CASE WHEN Vracena=1 THEN 'Da' ELSE 'Ne' END AS Vracena, "
		"CASE WHEN DatumVracanja IS NULL THEN '---' ELSE DatumVracanja END AS DatumVracanja "
		"FROM Posudbe;";
	sqlite3_exec(db, sql.c_str(),
		[](void*, int kolone, char** podaci, char** nazivKolone) {
			for (int i = 0; i < kolone; i++)
				cout << nazivKolone[i] << ": " << (podaci[i] ? podaci[i] : "NULL") << endl;
			cout << "---" << endl;
			return 0;
		}, nullptr, nullptr);
}
bool Baza::UkloniPosudbu(string isbn, string Clanska) {
	char* errMsg = nullptr;
	int count = 0;
	string Provjera =
		"SELECT COUNT(*) FROM Posudbe WHERE ISBN='" + isbn + "' AND Clanska='" + Clanska + "';";
	sqlite3_exec(db, Provjera.c_str(),
		[](void* data, int, char** podaci, char**) {
			*(int*)data = atoi(podaci[0]);
			return 0;
		}, &count, nullptr);
	if (count == 0)
		return false;
	string sql =
		"DELETE FROM Posudbe WHERE ISBN='" + isbn + "' AND Clanska='" + Clanska + "';";
	sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	return true;
}