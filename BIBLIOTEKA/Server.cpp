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
			jk["Naslov"] = k.Nasol;
			jk["Autor"] = k.Autor;
			jk["ISBN"] = k.ISBN;
			rezultat.push_back(jk);
		}
		res.set_content(rezultat.dump(4), "application/json");
		});
	std::cout << "Server pokrenut na http://localhost:8080" << std::endl;
	server.listen("localhost", 8080);
	return 0;
}

