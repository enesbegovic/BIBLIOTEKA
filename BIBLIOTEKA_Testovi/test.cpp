#include "pch.h"
#include "Baza.h"

TEST(BazaTest, DodajKnjiguProvjeriBrojKnjiga) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "111111");
	EXPECT_EQ(testBaza.BrojKnjiga(),1);
}
TEST(BazaTest, DodajDupluKnjiguProvjeriBrojKnjiga) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "111111");
	EXPECT_EQ(testBaza.BrojKnjiga(), 1);
	testBaza.DodajKnjigu("Knjiga2", "Autor2", "111111");
	EXPECT_EQ(testBaza.BrojKnjiga(), 1);
}
TEST(BazaTest, ObrisiKnjiguProvjeriBrojKnjiga) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "111111");
	EXPECT_EQ(testBaza.BrojKnjiga(), 1);
	testBaza.ObrisiKnjigu("111111");
	EXPECT_EQ(testBaza.BrojKnjiga(), 0);
}
TEST(BazaTest, ObrisiNepostojecuKnjiguProvjeriBrojKnjiga) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "111111");
	EXPECT_EQ(testBaza.BrojKnjiga(), 1);
	testBaza.ObrisiKnjigu("000000");
	EXPECT_EQ(testBaza.BrojKnjiga(), 1);
}
TEST(BazaTest, DodajClanaProvjeriBrojClanova) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajClana("Clan1", "111111");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
}
TEST(BazaTest, DodajDuplogClanaProvjeriBrojClanova) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajClana("Clan1", "111111");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	testBaza.DodajClana("Clan111", "111111");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
}
TEST(BazaTest, ObrisiClanaProvjeriBrojClanova) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajClana("Clan1", "111111");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	testBaza.ObrisiClana("111111");
	EXPECT_EQ(testBaza.BrojClanova(), 0);
}
TEST(BazaTest, ObrisiNepostojecegClanaProvjeriBrojClanova) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajClana("Clan1", "111111");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	testBaza.ObrisiClana("321455");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
}
TEST(BazaTest, DodajPosudbuProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	
}
TEST(BazaTest, DodajPosudbuNepostojeciClanProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("111111", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 0);
}
TEST(BazaTest, DodajPosudbuNepostojecaKnjigaProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "111111", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 0);
}
TEST(BazaTest, DodajDupluPosudbuProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
}
TEST(BazaTest, ObrisiPosudbuProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	testBaza.UkloniPosudbu("654321", "123456");
	EXPECT_EQ(testBaza.BrojPosudbi(), 0);

}
TEST(BazaTest, ObrisiPosudbuNepostojeciClanProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	testBaza.UkloniPosudbu("111111", "123456");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
}
TEST(BazaTest, ObrisiPosudbuNepostojecaKnjigaProvjeriBrojPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	testBaza.UkloniPosudbu("654321", "000000");
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
}
TEST(BazaTest, DodajClanaDodajPosudbuProvjeraBrojaClanovaBrojaPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClanaDodajPosudbu("Clan1", "654321", "123456", "2026-08-08");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
}
TEST(BazaTest, DodajClanaDodajPosudbuNepostojecaKnjigaProvjeraBrojaClanovaBrojaPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClanaDodajPosudbu("Clan1", "654321", "000000", "2026-08-08");
	EXPECT_EQ(testBaza.BrojClanova(), 0);
	EXPECT_EQ(testBaza.BrojPosudbi(), 0);
}
TEST(BazaTest, DodajClanaDodajPosudbuDupliClanProvjeraBrojaClanovaBrojaPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	testBaza.DodajClanaDodajPosudbu("Clan1", "654321", "000000", "2026-08-08");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	EXPECT_EQ(testBaza.BrojPosudbi(), 0);
}
TEST(BazaTest, DodajClanaDodajPosudbuDuplaPosudbaProvjeraBrojaClanovaBrojaPosudbi) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-08");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
	testBaza.DodajClanaDodajPosudbu("Clan1", "654321", "123456", "2026-08-08");
	EXPECT_EQ(testBaza.BrojClanova(), 1);
	EXPECT_EQ(testBaza.BrojPosudbi(), 1);
}
TEST(BazaTest, DodajStatusPosudbeProvjeriVrijednostStatusa) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.DodajKnjigu("Knjiga1", "Autor1", "123456");
	testBaza.DodajClana("Clan1", "654321");
	testBaza.PosudiKnjigu("654321", "123456", "2026-08-07");
	testBaza.VratiKnjigu("654321", "123456", "2026-08-21");
	EXPECT_EQ(testBaza.StatusPosudbe("654321", "123456"), 1);
}
TEST(BazaTest, DodajInformacijeBibilotekeProvjeriBrojInformacija) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.PostaviInfoBiblioteke("Naziv1", "Adresa1");
	EXPECT_EQ(testBaza.BrojInfo(), 1);
}
TEST(BazaTest, DodajDupleInformacijeBibilotekeProvjeriBrojInformacija) {
	Baza testBaza(":memory:");
	testBaza.KreirajTabele();
	testBaza.PostaviInfoBiblioteke("Naziv1", "Adresa1");
	EXPECT_EQ(testBaza.BrojInfo(), 1);
	testBaza.PostaviInfoBiblioteke("Naziv1", "Adresa1");
	EXPECT_EQ(testBaza.BrojInfo(), 1);
}