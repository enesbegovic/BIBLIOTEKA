# BIBLIOTEKA

Konzolna C++ aplikacija za upravljanje bibliotekom (knjige, clanovi, posudbe), sa SQLite bazom podataka. Sav rad sa bazom ide preko prepared statements.

## Tehnologije

- C++ (Visual Studio, konzolna aplikacija)
- SQLite3
- Git / GitHub za verzionisanje

## Struktura baze

### InfoBiblioteke
- `ID` (PRIMARY KEY AUTOINCREMENT)
- `Naziv`
- `Adresa`

### Knjige
- `ID` (PRIMARY KEY AUTOINCREMENT)
- `Naslov`
- `Autor`
- `ISBN` (UNIQUE)

### Clanovi
- `ID` (PRIMARY KEY AUTOINCREMENT)
- `ImePrezime`
- `BrojClanskeKartice` (UNIQUE)

### Posudbe
- `ID` (PRIMARY KEY AUTOINCREMENT)
- `ClanID` (FOREIGN KEY -> Clanovi, ON DELETE RESTRICT)
- `KnjigaID` (FOREIGN KEY -> Knjige, ON DELETE RESTRICT)
- `DatumPosudbe`
- `Vracena` (0 = nije vracena, 1 = vracena, DEFAULT 0)
- `DatumVracanja` (NULL dok knjiga nije vracena)

## Funkcionalnosti

**Knjige**
- Dodaj / ukloni / prikazi sve knjige

**Clanovi**
- Dodaj / ukloni / prikazi sve clanove
- Dodaj clana i odmah zakazi posudbu (jedna transakcija/poziv)

**Posudbe**
- Posudi knjigu (clan + knjiga + datum posudbe)
- Vrati knjigu (postavlja Vracena=1 i upisuje DatumVracanja)
- Ukloni posudbu
- Pregled svih posudbi (JOIN Clanovi + Knjige, sa CASE WHEN za citljiv status)

**Info biblioteke**
- Postavi / prikazi osnovne podatke o biblioteci (naziv, adresa)

## Kljucni koncepti koristeni u projektu

- Prepared statements za sve upite (bind/step/finalize umjesto sqlite3_exec)
- FOREIGN KEY constraint-i sa ON DELETE RESTRICT (PRAGMA foreign_keys=ON)
- Provjera postojanja/duplikata prije INSERT/UPDATE/DELETE (SELECT COUNT)
- CASE WHEN u SQL-u za citljiv prikaz statusa posudbe
- JOIN upiti kroz Posudbe -> Clanovi/Knjige
- Paznja na redoslijed bind() poziva - mora odgovarati redoslijedu ? znakova u upitu, ne redoslijedu promjenljivih u kodu

## Pokretanje

1. Otvoriti `.slnx` fajl u Visual Studio-u
2. Build (Debug/x64)
3. Pokrenuti - baza (`BIBLIOTEKA.db`) se automatski kreira pri prvom pokretanju ako ne postoji
