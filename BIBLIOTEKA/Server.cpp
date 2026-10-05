#include<httplib.h>
#include<nlohmann/json.hpp>
#include <iostream>
#include "Baza.h"
using json = nlohmann::json;

int main() {
	Baza baza("C:\\Users\\enesb\\source\\repos\\BIBLIOTEKA\\BIBLIOTEKA.db");
	httplib::Server server;
	server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
		res.set_content("Server Radi!", "text/plain");
		});
	server.Get("/knjige", [&baza](const httplib::Request& req, httplib::Response& res) {
		std::vector<Knjiga>knjige = baza.UzmiSveKnjige();
		std::cout << "Broj Knjiga Vracen Iz Baze:" << knjige.size() << std::endl;
		json rezultat = json::array();
		for (const auto& k : knjige) {
			json jk;
			jk["ID"] = k.ID;
			jk["Naslov"] = k.Naslov;
			jk["Autor"] = k.Autor;
			jk["ISBN"] = k.ISBN;
			rezultat.push_back(jk);
		}
		res.set_content(rezultat.dump(4), "application/json");
		});
	server.Post("/knjige", [&baza](const httplib::Request& req, httplib::Response& res) {
		try {
			json tijelo = json::parse(req.body);

			string naslov = tijelo.at("naslov");
			string autor = tijelo.at("autor");
			string isbn = tijelo.at("isbn");

			baza.DodajKnjigu(naslov, autor, isbn);

			json odgovor;
			odgovor["Poruka:"] = "Knjiga uspijesno dodana";
			res.status = 201;
			res.set_content(odgovor.dump(4), "application/json");
		}
		catch(const std::exception&e){
			json greska;
			greska["Greska:"] = e.what();
			res.status = 400;
			res.set_content(greska.dump(4), "application/json");
		}
		});
	server.Delete("/knjige/:isbn", [&baza](const httplib::Request& req, httplib::Response& res) {
		string isbn = req.path_params.at("isbn");

		baza.ObrisiKnjigu(isbn);

		json odgovor;
		odgovor["Poruka"] = "Knjiga Uspijesno obrisana";
		res.set_content(odgovor.dump(4), "application/json");
		});
	server.Get("/knjige/:isbn", [&baza](const httplib::Request& req, httplib::Response& res) {
		string isbn = req.path_params.at("isbn");
		std::vector<Knjiga>knjige = baza.UzmiSveKnjige();
		for (const auto& k : knjige) {
			if (k.ISBN == isbn) {
				json jk;
				jk["ID"] = k.ID;
				jk["Naslov"] = k.Naslov;
				jk["Autor"] = k.Autor;
				jk["ISBN"] = k.ISBN;
				res.set_content(jk.dump(4), "application/json");
				return;
			}
		}
		json Greska;
		Greska["greska"] = "Nepostoji knjiga sa trazenim ISBN-om";
		res.status = 404;
		res.set_content(Greska.dump(4), "application/json");
		});
	server.Get("/Clanovi", [&baza](const httplib::Request& req, httplib::Response& res) {
		std::vector<Clanovi>clanovi = baza.UzmiSveClanove();
		std::cout << "Broj Clanova Vracen Iz Baze:" << clanovi.size() << endl;
		json rezultat = json::array();
		for (const auto& c : clanovi) {
			json jc;
			jc["ID"] = c.ID;
			jc["Ime i Prezime"] = c.ImePrezime;
			jc["Broj Clanske Kartice"] = c.BrojClanskeKartice;
			rezultat.push_back(jc);
		}
		res.set_content(rezultat.dump(4), "application/json");
		});
	server.Post("/Clanovi", [&baza](const httplib::Request& req, httplib::Response& res) {
		try {
			json tijelo = json::parse(req.body);

			string ImePrezime = tijelo.at("Ime i Prezime");
			string BrojClanskeKartice = tijelo.at("Broj Clanske Kartice");

			baza.DodajClana(ImePrezime, BrojClanskeKartice);

			json Odgovor;
			Odgovor["Poruka:"] = "Clan uspijesno registrovan";
			res.status = 201;
			res.set_content(Odgovor.dump(4), "application/json");
		}
		catch (const std::exception& e) {
			json Greska;
			Greska["Greska:"] = e.what();
			res.status = 400;
			res.set_content(Greska.dump(4), "application/json");
		}
		});
	server.Delete("/Clanovi/:BrojClanskeKartice", [&baza](const httplib::Request& req, httplib::Response& res) {
		string BrojClanskeKartice = req.path_params.at("BrojClanskeKartice");
		baza.ObrisiClana(BrojClanskeKartice);
		json Odgovor;
		Odgovor["Poruka:"] = "Clan uspijesno uklonjen";
		res.set_content(Odgovor.dump(4), "application/json");
		});
	server.Get("/Clanovi/:BrojClanskeKartice", [&baza](const httplib::Request& req, httplib::Response& res) {
		string brojclanskekartice = req.path_params.at("BrojClanskeKartice");
		std::vector<Clanovi>clanovi = baza.UzmiSveClanove();
		for (const auto& c : clanovi) {
			if (c.BrojClanskeKartice == brojclanskekartice) {
				json jc;
				jc["ID"] = c.ID;
				jc["Ime i Prezime"] = c.ImePrezime;
				jc["Broj Clanske Kartice"] = c.BrojClanskeKartice;
				res.set_content(jc.dump(4), "application/json");
				return;
			}
		}
		json Greska;
		Greska["Greska:"] = "Ne postoji clan sa trazenom clanskom karticom";
		res.status = 404;
		res.set_content(Greska.dump(4), "application/json");
		});
	server.Get("/Posudbe", [&baza](const httplib::Request& req, httplib::Response& res) {
		std::vector<Posudbe>posudbe = baza.UzmiSvePosudbe();
		std::cout << "Broj posudbi vracen iz baze:" << posudbe.size() << endl;
		json rezultat = json::array();
		for (const auto& p : posudbe) {
			json jp;
			jp["Ime i Prezime Clana"] = p.ImeClana;
			jp["Broj Clanske Kartice:"] = p.BrojClanske;
			jp["Naslov Knjige:"] = p.NaslovKnjige;
			jp["Datum Posudbe"] = p.DatumPosudbe;
			jp["Vracena"] = p.Vracena;
			jp["Datum Vracanja"] = p.DatumVracanja;
			rezultat.push_back(jp);
		}
		res.set_content(rezultat.dump(4), "application/json");
		});
	server.Post("/Posudbe", [&baza](const httplib::Request& req, httplib::Response& res) {
		try {
			json tijelo = json::parse(req.body);
			string Clanska = tijelo.at("ClanskaKartica");
			string Isbn = tijelo.at("ISBN");
			string DatumPosudbe = tijelo.at("DatumPosudbe");
			baza.PosudiKnjigu(Clanska, Isbn, DatumPosudbe);
			json Odgovor;
			Odgovor["Poruka:"] = "Knjiga uspijesno posudjena";
			res.set_content(Odgovor.dump(4), "application/json");
		}
		catch(const std::exception&e){
			json Greska;
			Greska["Greska:"] = e.what();
			res.set_content(Greska.dump(4), "application/json");
		}
		});
	server.Post("/Posudbe/vrati", [&baza](const httplib::Request& req, httplib::Response& res) {
		try {
			json tijelo = json::parse(req.body);
			string Clanska = tijelo.at("ClanskaKartica");
			string Isbn = tijelo.at("ISBN");
			string DatumVracanja = tijelo.at("DatumVracanja");
			baza.VratiKnjigu(Clanska, Isbn, DatumVracanja);
			json Odgovor;
			Odgovor["Poruka:"] = "Knjiga uspijesno vracena";
			res.set_content(Odgovor.dump(4), "application/json");
		}
		catch (const std::exception& e) {
			json Greska;
			Greska["Greska:"] = e.what();
			res.set_content(Greska.dump(4), "application/json");
		}
		});
	server.Get("/knjige/autor/:autor", [&baza](const httplib::Request& req, httplib::Response& res) {
			string Autor = req.path_params.at("autor");
			std::vector<Knjiga>knjige = baza.UzmiSveKnjige();
			json rezultat = json::array();
			for (const auto& k : knjige) {
				if (k.Autor == Autor) {
					json jk;
					jk["ID"] = k.ID;
					jk["Naslov"] = k.Naslov;
					jk["Autor"] = k.Autor;
					jk["ISBN"] = k.ISBN;
					rezultat.push_back(jk);
				}
			}
			if (!rezultat.empty()) {
				res.set_content(rezultat.dump(4), "application/json");
				return;
			}
			json Greska;
			Greska["Greska"] = "Nepostoje Knjige Od Trazenog Autora";
			res.status = 404;
			res.set_content(Greska.dump(4), "application/json");
		
		});
	std::cout << "Server pokrenut na http://localhost:8080" << std::endl;
	server.listen("localhost", 8080);
	return 0;
}

