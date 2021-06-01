//
// Created by Inspion 7000 on 31.05.2021.
//

#ifndef PROJEKT_PODZIELONE_DEFINICJE_H
#define PROJEKT_PODZIELONE_DEFINICJE_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define TEXT_DARKGRAY 0x8
#define TEXT_MAGENTA 0x5
#define TEXT_RED 0xC
#define TEXT_GREEN 0xA
#define TEXT_CYAN 0x3
#define TEXT_LIGHTGRAY 0x7
#define TEXT_YELLOW 0xE
#define TEXT_BROWN 0x6
#define TEXT_BLUE 0xB

#define PUSTE 0
#define OTOCZENIE 5
#define TRAFIONY 9
#define PUDLO 8

//funkcje uniwersalne
void SetConsoleColor(int k);
int GiveRandom(int start, int ile_liczb);
int GetLevel();
void Wait(int time);
void MenuGlowne();

struct ostatni_ruch {
    int w;
    int k;
};
struct ostatni_strzal {
    int w;
    int k;
    int kto;
};

struct pozostalo_statkow {
    int gracza;
    int komputera;
};

struct strzelanie {
    int kierunek; // 0 = poziomo  1 = pionowo
    int stan;
    int trafiony[2];
    int maszty;
};

//wisielec
void WypiszLitery(int alfabet[]);
void RysujWisielca(int proba);
void WypiszHaslo(char haslo[2][30]);
void WczytajLitere(int poziom, int alfabet[]);
void OdkryjLitere(int *proby, char haslo[2][30], int alfabet[]);
int hasloOdgadniete(char haslo[2][30]);
void Wisielec();

//kolko i krzyzyk
void WypiszPlansze(char plansza[3][3]);
bool SprawdzWygrana(char plansza[3][3], int w, int k, char znak);
bool Ruch(char plansza[3][3], int wiersz, int kolumna, char znak);
void WczytajWybor(int *wiersz, int *kolumna, char plansza[3][3]);
void LosowanieKomputera0(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch* O);
void PierwszyRuchKomputera1(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch *O);
void DrugiRuchKomputera1(int* wiersz, int* kolumna, char plansza[3][3], struct ostatni_ruch* O);
bool CzyMozliwyKoniecGry(int* wiersz, int* kolumna, char plansza[3][3], struct ostatni_ruch* O, char kto);
void TrzeciRuchKomputera1(int* wiersz, int* kolumna, char plansza[3][3], struct ostatni_ruch* O);
void CzwartyRuchKomputera1(int *wiersz, int *kolumna);
bool CzyZostaloWolnePole(char plansza[3][3]);
void Kolko();

//statki
void WypiszStatki(char plansza_gracza[10][10], char plansza_strzalow[10][10], struct ostatni_strzal O, int koniec);
bool CzyNalezyDoPlanszy(int x, int y);
void TworzStatek(int maszty, char plansza[10][10]);
void RozrysujStatki(char plansza[10][10]);
bool CzyZatopiony(int maszty, int wiersz, int kolumna, char plansza[10][10]);
void Obtaczanie(int maszty, int wiersz, int kolumna, char plansza[10][10]);
void StrzelanieKomputera0(char plansza[10][10], struct pozostalo_statkow* P);
void StrzelanieKomputera1(char plansza[10][10], struct pozostalo_statkow* P, struct strzelanie* S, struct ostatni_strzal* O);
void StrzelanieGracza(char plansza[10][10], struct pozostalo_statkow* P, struct ostatni_strzal* O);
bool CzyKoniecStatkow(struct pozostalo_statkow* P);
void InstrukcjaStatkow();
void Statki();

//4 w linii
bool CzyMozliwaKulka(int w, int k, char plansza[10][10]);
void WypiszKulki(char plansza[10][10]);
void KulkaGracza(struct ostatni_strzal *O, char plansza[10][10]);
void KulkaKomputera0(struct ostatni_strzal* O, char plansza[10][10]);
int MaxKulekWLinii(int wiersz, int kolumna, char plansza[10][10], int kto);
void KulkaKomputera1(struct ostatni_strzal* O, char plansza[10][10]);
bool CzyKoniecKulek(char plansza[10][10], struct ostatni_strzal *O);
void Kulki();

#endif //PROJEKT_PODZIELONE_DEFINICJE_H
