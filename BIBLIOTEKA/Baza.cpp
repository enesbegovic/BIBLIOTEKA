#include <iostream>
#include "Baza.h"
using namespace std;
Baza::Baza() {
	sqlite3_open("BIBLIOTEKA.db", &db);
	sqlite3_exec(db, "PRAGMA foreign_keys=ON;", nullptr, nullptr, nullptr);
}
Baza::~Baza() {
	sqlite3_close(db);
}
void Baza::IzvrsiUpit(string sql, string PORUKAGRESKE) {
	char* errMsg = nullptr;
	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		cout << PORUKAGRESKE << errMsg << endl;
		sqlite3_free(errMsg);
	}
}
void Baza::KreirajTabele() {
	char * errMsg = nullptr;
	string KreirajKnjige=
	    "CREATE TABLE IF NOT EXISTS Knjige("
	    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
	    "Naslov TEXT NOT NULL,"
	    "Autor TEXT NOT NULL,"
	    "ISBN TEXT NOT NULL UNIQUE);";
	IzvrsiUpit(KreirajKnjige, "GRESKA PRI KREIRANJU TABELE KNJIGE");

	string KreirajClanove =
		"CREATE TABLE IF NOT EXISTS Clanovi("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"ImePrezime TEXT NOT NULL,"
		"BrojClanskeKartice TEXT NOT NULL UNIQUE);";
	IzvrsiUpit(KreirajClanove, "GRESKA PRI KREIRANJU TABELE CLANOVI");

	string KreirajPosudbe =
		"CREATE TABLE IF NOT EXISTS Posudbe("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"ClanID INTEGER NOT NULL,"
		"KnjigaID INTEGER NOT NULL,"
		"DatumPosudbe TEXT NOT NULL,"
		"Vracena INTEGER DEFAULT 0,"
		"DatumVracanja TEXT,"
		"FOREIGN KEY (ClanID) REFERENCES Clanovi(ID) ON DELETE RESTRICT,"
		"FOREIGN KEY (KnjigaID) REFERENCES Knjige(ID) ON DELETE RESTRICT);";
	IzvrsiUpit(KreirajPosudbe, "GRESKA PRI KREIRANJU TABELE POSUDBE");

	string KreirajInfoBiblioteke =
		"CREATE TABLE IF NOT EXISTS InfoBiblioteke("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"Naziv TEXT NOT NULL,"
		"Adresa TEXT NOT NULL)";
	IzvrsiUpit(KreirajInfoBiblioteke, "GRESKA PRI KREIRANJU TABELE INFO BIBLIOTEKE");
}
void Baza::PostaviInfoBiblioteke(string Naziv, string Adresa) {
	sqlite3_stmt* stmtProvjera;
	int count = 0;
	string Provjera =
		"SELECT COUNT (*) FROM InfoBiblioteke WHERE Naziv=? AND Adresa=?;";
	int rc = sqlite3_prepare_v2(db, Provjera.c_str(), -1, &stmtProvjera, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE BIBLIOTEKE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtProvjera, 1, Naziv.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmtProvjera, 2, Adresa.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjera) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtProvjera, 0);
	}
	sqlite3_finalize(stmtProvjera);
	if (count > 0) {
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"INSERT INTO InfoBiblioteke(Naziv, Adresa) VALUES(?, ?);";
	int rc1 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA INFORMACIJA O BIBLIOTECI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, Naziv.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, Adresa.c_str(), -1, SQLITE_TRANSIENT);
	rc1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc1 != SQLITE_DONE) {
		cout << "GRESKA PRI DODAVANJU INFORMACIJA O BIBLIOTECI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "USPJESNO DODANE INFORMACIJE O BIBLIOTECI" << endl;
}
void Baza::PrikaziInfoBiblioteke() {
	sqlite3_stmt* stmt;
	string sql =
		"SELECT * FROM InfoBiblioteke;";
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PRIKAZA INFORMACIJA BIBLIOTEKE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int ID = sqlite3_column_int(stmt, 0);
		string Naziv = (const char*)sqlite3_column_text(stmt, 1);
		string Adresa = (const char*)sqlite3_column_text(stmt, 2);

		cout << "ID:" << ID << endl;
		cout << "Biblioteka:" << Naziv << endl;
		cout << "Adresa:" << Adresa << endl;
		cout << "---" << endl;
	}
	sqlite3_finalize(stmt);
}
void Baza::DodajKnjigu(string naslov, string autor, string isbn) {
	sqlite3_stmt* stmtProvjera;
	int count = 0;
	string Provjera =
		"SELECT COUNT (*) FROM Knjige WHERE ISBN=?;";
	int rc = sqlite3_prepare_v2(db, Provjera.c_str(), -1, &stmtProvjera, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtProvjera, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjera) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtProvjera, 0);
	}
	sqlite3_finalize(stmtProvjera);
	if (count > 0) {
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"INSERT INTO Knjige(Naslov, Autor, ISBN) VALUES(?, ?, ?);";
	int rc1 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, naslov.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, autor.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, isbn.c_str(), -1, SQLITE_TRANSIENT);
	rc1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc1 != SQLITE_DONE) {
		cout << "GRESKA PRI DODAVANJU KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "KNJIGA USPJESNO DODANA" << endl;
}
void Baza::ObrisiKnjigu(string isbn) {
	sqlite3_stmt* stmtProvjera;
	int count = 0;
	string Provjera =
		"SELECT COUNT (*) FROM Knjige WHERE ISBN=?;";
	int rc = sqlite3_prepare_v2(db, Provjera.c_str(), -1, &stmtProvjera, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE KNJIGE" << endl;
		return;
	}
	sqlite3_bind_text(stmtProvjera, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjera) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtProvjera, 0);
	}
	sqlite3_finalize(stmtProvjera);
	if (count == 0) {
		cout << "GRESKA PRI UKLANJANJU KNJIGE-TRAZENA KNJIGA NE POSTOJI" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"DELETE FROM Knjige WHERE ISBN=?;";
	int rc1 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI UKLANJANJA KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	rc1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc1 != SQLITE_DONE) {
		cout << "GRESKA PRI UKLANJANJU KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "KNJIGA USPIJESNO UKLONJENA" << endl;
}
void Baza::PrikaziSveKnjige() {
	sqlite3_stmt* stmt;
	string sql =
		"SELECT * FROM Knjige;";
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PRIKAZA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int ID = sqlite3_column_int(stmt, 0);
		string Naslov = (const char*)sqlite3_column_text(stmt, 1);
		string Autor = (const char*)sqlite3_column_text(stmt, 2);
		string ISBN = (const char*)sqlite3_column_text(stmt, 3);

		cout << "ID:" << ID << endl;
		cout << "Naslov Knjige:" << Naslov << endl;
		cout << "Autor:" << Autor << endl;
		cout << "ISBN:" << ISBN << endl;
		cout << "---" << endl;
	}
	sqlite3_finalize(stmt);
}
void Baza::DodajClana(string imePrezime, string brojClanskeKartice) {
	sqlite3_stmt* stmtProvjera;
	int count = 0;
	string Provjera =
		"SELECT COUNT (*) FROM Clanovi WHERE brojClanskeKartice=?;";
	int rc = sqlite3_prepare_v2(db, Provjera.c_str(), -1, &stmtProvjera, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE CLANA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtProvjera, 1, brojClanskeKartice.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjera) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtProvjera, 0);
	}
	sqlite3_finalize(stmtProvjera);
	if (count > 0) {
		cout << "GRESKA PRI DODAVANJU CLANA-CLAN VEC POSTOJI" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"INSERT INTO Clanovi(imePrezime, brojClanskeKartice) VALUES(?, ?);";
	int rc1 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, imePrezime.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, brojClanskeKartice.c_str(), -1, SQLITE_TRANSIENT);
	rc1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc1 != SQLITE_DONE) {
		cout << "GRESKA PRI DODAVANJU CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "USPJESNO DODAN CLAN" << endl;
}
void Baza::ObrisiClana(string brojClanskeKartice) {
	sqlite3_stmt* stmtProvjera;
	int count = 0;
	string Provjera =
		"SELECT COUNT (*) FROM Clanovi WHERE brojClanskeKartice=?;";
	int rc = sqlite3_prepare_v2(db, Provjera.c_str(), -1, &stmtProvjera, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtProvjera, 1, brojClanskeKartice.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjera) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtProvjera, 0);
	}
	sqlite3_finalize(stmtProvjera);
	if (count == 0) {
		cout << "GRESKA PRI UKLANJANJU CLANOVA-TRAZENI CLAN NE POSTOJI" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"DELETE FROM Clanovi WHERE brojClanskeKartice=?;";
	int rc1 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI UKLANJANJA CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, brojClanskeKartice.c_str(), -1, SQLITE_TRANSIENT);
	rc1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc1 != SQLITE_DONE) {
		cout << "GRESKA PRI UKLANJANJU CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "CLAN USPJESNO UKLONJEN" << endl;
}
void Baza::PrikaziSveClanove() {
	sqlite3_stmt* stmt;
	string sql =
		"SELECT * FROM Clanovi;";
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PRIKAZA CLANOVA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int ID = sqlite3_column_int(stmt, 0);
		string Ime = (const char*)sqlite3_column_text(stmt, 1);
		string Karitca = (const char*)sqlite3_column_text(stmt, 2);

		cout << "ID:" << ID << endl;
		cout << "Ime I Prezime Clana:" << Ime << endl;
		cout << "Broj Clanske Kartice:" << Karitca << endl;
		cout << "---" << endl;
	}
	sqlite3_finalize(stmt);
}
void Baza::PosudiKnjigu(string Clanska, string isbn, string DatumPosudbe) {
	sqlite3_stmt* stmtClan;
	int ClanID=0;
	string ProvjeraClana =
		"SELECT ID FROM Clanovi WHERE BrojClanskeKartice=?;";
	int rc = sqlite3_prepare_v2(db, ProvjeraClana.c_str(), -1, &stmtClan, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE CLANA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtClan, 1, Clanska.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtClan) == SQLITE_ROW) {
		ClanID = sqlite3_column_int(stmtClan, 0);
	}
	sqlite3_finalize(stmtClan);
	sqlite3_stmt* stmtKnjiga;
	int KnjigaID = 0;
	string ProvjeraKnjige =
		"SELECT ID FROM Knjige WHERE ISBN=?;";
	int rc1 = sqlite3_prepare_v2(db, ProvjeraKnjige.c_str(), -1, &stmtKnjiga, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtKnjiga, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtKnjiga) == SQLITE_ROW) {
		KnjigaID = sqlite3_column_int(stmtKnjiga, 0);
	}
	sqlite3_finalize(stmtKnjiga);
	sqlite3_stmt* stmtPosudbe;
	int count = 0;
	string ProvjeraPosudbe =
		"SELECT COUNT (*) FROM Posudbe WHERE ClanID=? AND KnjigaID=? AND DatumPosudbe=?;";
	int rc2 = sqlite3_prepare_v2(db, ProvjeraPosudbe.c_str(), -1, &stmtPosudbe, nullptr);
	if (rc2 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE POSUDBI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_int(stmtPosudbe, 1, ClanID);
	sqlite3_bind_int(stmtPosudbe, 2, KnjigaID);
	sqlite3_bind_text(stmtPosudbe, 3, DatumPosudbe.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtPosudbe) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtPosudbe, 0);
	}
	sqlite3_finalize(stmtPosudbe);
	if (ClanID == 0 || KnjigaID == 0 || count > 0) {
		cout << "GRESKA PRI DODAVANJU POSUDBE-NEPOSTOJECI CLAN-NEPOSTOJECA KNJIGA-POSUDBA VEC POSTOJI" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"INSERT INTO Posudbe(ClanID, KnjigaID, DatumPosudbe) VALUES(?, ?, ?);";
	int rc3 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc3 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA POSUDBE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_int(stmt, 1, ClanID);
	sqlite3_bind_int(stmt, 2, KnjigaID);
	sqlite3_bind_text(stmt, 3, DatumPosudbe.c_str(), -1, SQLITE_TRANSIENT);
	rc3 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc3 != SQLITE_DONE) {
		cout << "GRESKA PRI DODABANJU POSUDBE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "POSUDBA USPJESNO DODANA" << endl;
}
void Baza::VratiKnjigu(string Clanska, string isbn, string DatumVracanja) {
	sqlite3_stmt* stmtClan;
	int ClanID=0;
	string ProvjeraClana =
		"SELECT ID FROM Clanovi WHERE BrojClanskeKartice=?;";
	int rc = sqlite3_prepare_v2(db, ProvjeraClana.c_str(), -1, &stmtClan, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE CLANA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtClan, 1, Clanska.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtClan) == SQLITE_ROW) {
		ClanID = sqlite3_column_int(stmtClan, 0);
	}
	sqlite3_finalize(stmtClan);
	sqlite3_stmt* stmtKnjiga;
	int KnjigaID = 0;
	string ProvjeraKnjige =
		"SELECT ID FROM Knjige WHERE ISBN=?;";
	int rc1 = sqlite3_prepare_v2(db, ProvjeraKnjige.c_str(), -1, &stmtKnjiga, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRIP PRIPREMI PROVJERE KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtKnjiga, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtKnjiga) == SQLITE_ROW) {
		KnjigaID = sqlite3_column_int(stmtKnjiga, 0);
	}
	sqlite3_finalize(stmtKnjiga);
	sqlite3_stmt* stmtPosudbe;
	int count = 0;
	string ProvjeraPosudbe =
		"SELECT COUNT (*) FROM Posudbe WHERE ClanID=? AND KnjigaID=?;";
	int rc2 = sqlite3_prepare_v2(db, ProvjeraPosudbe.c_str(), -1, &stmtPosudbe, nullptr);
	if (rc2 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE POSUDBI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_int(stmtPosudbe, 1, ClanID);
	sqlite3_bind_int(stmtPosudbe, 2, KnjigaID);
	if (sqlite3_step(stmtPosudbe) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtPosudbe, 0);
	}
	sqlite3_finalize(stmtPosudbe);
	if (ClanID == 0 || KnjigaID == 0 || count == 0) {
		cout << "GRESKA PRI VRACANJU KNJIGE-NEPOSTOJECI CLAN-NEPOSTOJECA KNJIGA-NEPOSTOJECA POSUDBA" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"UPDATE Posudbe SET Vracena=1, DatumVracanja=? WHERE ClanID=? AND KnjigaID=? AND Vracena=0;";
	int rc3 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc3 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI VRACANJA KJNIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmt, 1, DatumVracanja.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, ClanID);
	sqlite3_bind_int(stmt, 3, KnjigaID);
	rc3 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc3 != SQLITE_DONE) {
		cout << "GRESKA PRI VRACANJU KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "KNJIGA USPJESNO VRACENA" << endl;
}
void Baza::PregledPosudbi() {
	sqlite3_stmt* stmt;
	string sql =
		"SELECT Clanovi.ImePrezime, Clanovi.BrojClanskeKartice, Knjige.Naslov, Posudbe.DatumPosudbe, "
		"CASE WHEN Vracena=1 THEN 'Da' ELSE 'Ne' END AS Vracena, "
		"CASE WHEN DatumVracanja IS NULL THEN '---' ELSE DatumVracanja END AS DatumVracanja "
		"FROM Posudbe "
		"JOIN Clanovi ON Posudbe.ClanID=Clanovi.ID "
		"JOIN Knjige ON Posudbe.KnjigaID=Knjige.ID;";
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PRIKAZA POSUDBI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		string Ime = (const char*)sqlite3_column_text(stmt, 0);
		string Clanska = (const char*)sqlite3_column_text(stmt, 1);
		string Naslov = (const char*)sqlite3_column_text(stmt, 2);
		string DatumPosudbe = (const char*)sqlite3_column_text(stmt, 3);
		string Vracena = (const char*)sqlite3_column_text(stmt, 4);
		string DatumVracanja = (const char*)sqlite3_column_text(stmt, 5);

		cout << "Ime I Prezime Clana:" << Ime << endl;
		cout << "Broj Clanske Kartice:" << Clanska << endl;
		cout << "Knjiga:" << Naslov << endl;
		cout << "Datum Posudbe:" << DatumPosudbe << endl;
		cout << "Da Li Je Knjiga Vracena:" << Vracena << endl;
		cout << "Datum Vracanja:" << DatumVracanja << endl;
		cout << "---" << endl;
	}
	sqlite3_finalize(stmt);
}
void Baza::UkloniPosudbu(string Clanska, string isbn) {
	sqlite3_stmt* stmtClan;
	int ClanID=0;
	string ProvjeraClana =
		"SELECT ID FROM Clanovi WHERE BrojClanskeKartice=?;";
	int rc = sqlite3_prepare_v2(db, ProvjeraClana.c_str(), -1, &stmtClan, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE CLANA:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtClan, 1, Clanska.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtClan) == SQLITE_ROW) {
		ClanID = sqlite3_column_int(stmtClan, 0);
	}
	sqlite3_finalize(stmtClan);
	sqlite3_stmt* stmtKnjiga;
	int KnjigaID = 0;
	string ProvjeraKnjige =
		"SELECT ID FROM Knjige WHERE ISBN=?;";
	int rc1 = sqlite3_prepare_v2(db, ProvjeraKnjige.c_str(), -1, &stmtKnjiga, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRIP PRIPREMI PROVJERE KNJIGE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_text(stmtKnjiga, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtKnjiga) == SQLITE_ROW) {
		KnjigaID = sqlite3_column_int(stmtKnjiga, 0);
	}
	sqlite3_finalize(stmtKnjiga);
	sqlite3_stmt* stmtPosudbe;
	int count = 0;
	string ProvjeraPosudbe =
		"SELECT COUNT (*) FROM Posudbe WHERE ClanID=? AND KnjigaID=?;";
	int rc2 = sqlite3_prepare_v2(db, ProvjeraPosudbe.c_str(), -1, &stmtPosudbe, nullptr);
	if (rc2 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE POSUDBI:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_int(stmtPosudbe, 1, ClanID);
	sqlite3_bind_int(stmtPosudbe, 2, KnjigaID);
	if (sqlite3_step(stmtPosudbe) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtPosudbe, 0);
	}
	sqlite3_finalize(stmtPosudbe);
	if (ClanID == 0 || KnjigaID == 0 || count == 0) {
		cout << "GRESKA PRI UKLANJANJU POSUDBE-NEPOSTOJECI CLAN-NEPOSTOJECA KNJIGA-NEPOSTOJECA POSUDBA" << endl;
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"DELETE FROM Posudbe WHERE ClanID=? AND KnjigaID=?;";
	int rc3 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc3 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI BRISANJA POSUDBE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	sqlite3_bind_int(stmt, 1, ClanID);
	sqlite3_bind_int(stmt, 2, KnjigaID);
	rc3 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc3 != SQLITE_DONE) {
		cout << "GRESKA PRI BRISANJU POSUDBE:" << sqlite3_errmsg(db) << endl;
		return;
	}
	cout << "POSUDBA USPJESNO UKLONJENA" << endl;
}
void Baza::DodajClanaDodajPosudbu(string ImePrezime, string Clanska, string isbn, string DatumPosudbe) {
	IzvrsiUpit("BEGIN TRANSACTION;", "GRESKA PRI POKRETANJU TRANSAKCIJE");
	sqlite3_stmt* stmtClan;
	string sqlClan =
		"INSERT INTO Clanovi(ImePrezime, BrojClanskeKartice) VALUES(?, ?);";
	int rc = sqlite3_prepare_v2(db, sqlClan.c_str(), -1, &stmtClan, nullptr);
	if (rc != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA CLANA:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_bind_text(stmtClan, 1, ImePrezime.c_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmtClan, 2, Clanska.c_str(), -1, SQLITE_TRANSIENT);
	rc = sqlite3_step(stmtClan);
	sqlite3_finalize(stmtClan);
	if (rc != SQLITE_DONE) {
		cout << "GRESKA PRI DODAVANJU CLANA:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	
	int ClanID = sqlite3_last_insert_rowid(db);

	sqlite3_stmt* stmtProvjeraKnjige;
	int KnjigaID = 0;
	string sqlProvjeraKnjige =
		"SELECT ID FROM Knjige WHERE ISBN=?;";
	int rc1 = sqlite3_prepare_v2(db, sqlProvjeraKnjige.c_str(), -1, &stmtProvjeraKnjige, nullptr);
	if (rc1 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE KNJIGE:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_bind_text(stmtProvjeraKnjige, 1, isbn.c_str(), -1, SQLITE_TRANSIENT);
	if (sqlite3_step(stmtProvjeraKnjige) == SQLITE_ROW) {
		KnjigaID = sqlite3_column_int(stmtProvjeraKnjige, 0);
	}
	sqlite3_finalize(stmtProvjeraKnjige);
	if (KnjigaID == 0) {
		cout << "GRESKA PRI DODAVANJU POSUDBE-NE POSTOJECA KNJIGA" << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_stmt* stmtPosudbe;
	int count = 0;
	string ProvjeraPosudbe =
		"SELECT COUNT (*) FROM Posudbe WHERE ClanID=? AND KnjigaID=?;";
	int rc2 = sqlite3_prepare_v2(db, ProvjeraPosudbe.c_str(), -1, &stmtPosudbe, nullptr);
	if (rc2 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI PROVJERE POSUDBI:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_bind_int(stmtPosudbe, 1, ClanID);
	sqlite3_bind_int(stmtPosudbe, 2, KnjigaID);
	if (sqlite3_step(stmtPosudbe) == SQLITE_ROW) {
		count = sqlite3_column_int(stmtPosudbe, 0);
	}
	sqlite3_finalize(stmtPosudbe);
	if (count > 0) {
		cout << "GRESKA PRI DODAVANJU POSUDBE,POSUDBA VEC POSTOJI" << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_stmt* stmt;
	string sql =
		"INSERT INTO Posudbe(ClanID, KnjigaID, DatumPosudbe) VALUES(?, ?, ?);";
	int rc3 = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
	if (rc3 != SQLITE_OK) {
		cout << "GRESKA PRI PRIPREMI DODAVANJA POSUDBE:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	sqlite3_bind_int(stmt, 1, ClanID);
	sqlite3_bind_int(stmt, 2, KnjigaID);
	sqlite3_bind_text(stmt, 3, DatumPosudbe.c_str(), -1, SQLITE_TRANSIENT);
	rc3 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (rc3 != SQLITE_DONE) {
		cout << "GRESKA PRI DODAVANJU POSUDBE:" << sqlite3_errmsg(db) << endl;
		IzvrsiUpit("ROLLBACK;", "GRESKA PRI ROLLBACK-u");
		return;
	}
	IzvrsiUpit("COMMIT;", "GRESKA PRI COMMIT-u");
	cout << "TRANSAKCIJA USPJESNA-USPJESNO DODANI CLAN I POSUDBA" << endl;
}