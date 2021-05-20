﻿#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TEXT_DARKGRAY 0x8
#define TEXT_MAGENTA 0x5
#define TEXT_RED 0xC
#define TEXT_GREEN 0xA
#define TEXT_CYAN 0x3
#define TEXT_LIGHTGRAY 0x7
#define TEXT_YELLOW 0xE
#define TEXT_BROWN 0x6

#define PUSTE 0
//#define STATEK 1
#define OTOCZENIE 5
#define TRAFIONY 9
#define PUDLO 8


void Statki();

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

void SetConsoleColor(int k)
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, k);
}

int GiveRandom(int start, int ile_liczb) {
	

	return (rand()%ile_liczb) + start;

}

int GetLevel() {
	int level;
	printf("[0] Latwy\n[1] Trudny\n\nWybierz poziom trudnosci: ");
	scanf(" %d", &level);
	system("cls");
	return level;
	
}

void Wait(int time) {
	for (int i = 0; i < time; i++) {
		printf(".");
		Sleep(555);
	}
	printf("\n");

}



void WypiszLitery(int alfabet[])
{
	for (int i = 0; i < 26; i++) {
		if (alfabet[i] > 0) {
			SetConsoleColor(TEXT_MAGENTA);
			printf(" %c", 35);
			SetConsoleColor(15);
		}
		else {
			printf(" %c", i + 65);
		}
	}
	printf("\n\n");
}

void RysujWisielca(int proba) {
	SetConsoleColor(TEXT_YELLOW);
	char wisielec[9][200] = { "      \n        \n        \n         \n         \n        \n     \n    _____",
							"      \n     |    \n     |      \n     |       \n     |       \n     |      \n     |\n    _|___",
							"      _______\n     |/      \n     |      \n     |       \n     |       \n     |      \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |       \n     |       \n     |      \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |       |\n     |       |\n     |      \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |      \\|\n     |       |\n     |      \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \n     |\n    _|___",
							"      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \\\n     |\n    _|___" };
	printf("%s\n", wisielec[8-proba]);
	printf("\n");
	SetConsoleColor(TEXT_LIGHTGRAY);
}

void WypiszHaslo(char haslo[2][30])
{
	for (unsigned int i = 0; i < strlen(haslo[0]); i++)
	{
		if (haslo[1][i] == '1')
		{
			printf("%c ", haslo[0][i]);

		}
		else
		{
			printf("_ ");
		}
	}
	printf("\n");
}

void WczytajLitere(int poziom, int alfabet[])
{
	printf("Podaj swoja litere: ");

	char litera;
	scanf(" %c", &litera);
	getchar();
	litera = toupper(litera);
	if (poziom == 0) {
		if (alfabet[(int)litera - 65] == 1) {
			printf("\nLitera zostala juz wczesniej wczytana, podaj kolejna.\n");
			WczytajLitere(poziom, alfabet);
		}
	}
	alfabet[(int)litera - 65]++;
}

void OdkryjLitere(int &proby, char haslo[2][30], int alfabet[])
{
	int znaleziono = 0;
	for (int i = 0; i < 26; i++) {
		for (unsigned int j = 0; j < strlen(haslo[0]); j++) {
			if ((haslo[0][j] == (char)(i + 65) && alfabet[i] == 1) && haslo[1][j] == '0') {
				haslo[1][j] = '1';
				znaleziono = 1;
			}
		}
	}
	if (znaleziono == 0) {
		proby--;
	}
}

int hasloOdgadniete(char haslo[2][30])
{
	for (unsigned int i = 0; i < strlen(haslo[1]);  i++) {
		if (haslo[1][i] == '0') {
			return 0;
		}
	}
	return 1;

}

void Wisielec()
{
	int poziom = GetLevel();
	int alfabet[26];
	memset(alfabet, 0, 26*sizeof(int));
	int proby = 8;
	char baza_hasel[10][30] = {
							"INFORMATYKA",
							"PROGRAMOWANIE",
							"NISKOPOZIOMOWE",
							"MATEMATYKA",
							"GUMIAKI"
	};
	char haslo[2][30];  //{ "INFA", "0000" }
	strcpy(haslo[0], baza_hasel[GiveRandom(0,5)]);
	memset(haslo[1], '0', strlen(haslo[0]) * sizeof(char));
	while (1) {
		WypiszHaslo(haslo);
		RysujWisielca(proby);

		if (proby == 0) {
			SetConsoleColor(TEXT_RED);
			printf("\nWykorzystano wszystkie proby, umierasz.\n");
			printf("Haslo, ktore trzeba bylo odgadnac: %s", haslo[0]);
			break;
		}
		else if (hasloOdgadniete(haslo))
		{
			SetConsoleColor(TEXT_GREEN);
			printf("\nWygrana!\n");
			break;
		}
		if (poziom == 0) {
			WypiszLitery(alfabet);
		}
		
		WczytajLitere(poziom, alfabet);
		OdkryjLitere(proby, haslo, alfabet);
		system("cls");


	}
}



void WypiszPlansze(char plansza[3][3]) {
	system("cls");
	SetConsoleColor(TEXT_CYAN);
	printf("\n     a     b     c\n");
	for (int i = 0; i < 3; i++) {
		printf("        |     |     \n");
		printf(" %d   %c  |  %c  |  %c  \n", i, plansza[i][0], plansza[i][1], plansza[i][2]);
		if (i != 2) {
			printf("   _____|_____|_____\n");
		}
	}
	printf("        |     |     \n");
	SetConsoleColor(TEXT_LIGHTGRAY);
}

bool SprawdzWygrana(char plansza[3][3], int w, int k)
{
	if ((plansza[w][0] == plansza[w][1]) && (plansza[w][1] == plansza[w][2]))
	{
		return true;
	}
	if ((plansza[0][k] == plansza[1][k]) && (plansza[1][k] == plansza[2][k]))
	{
		return true;
	}
	if ((k+w)%2==0)
	{
		if ((plansza[0][0] == plansza[2][2]) && (plansza[1][1] == plansza[2][2]))
		{
			return true;
		}
		if ((plansza[0][2] == plansza[2][0]) && (plansza[1][1] == plansza[0][2]))
		{
			return true;
		}
	}
	return false;

}

bool Ruch(char plansza[3][3], int wiersz, int kolumna, char znak) {
	plansza[wiersz][kolumna] = znak;

	return SprawdzWygrana(plansza, wiersz, kolumna);
}

void WczytajWybor(int &wiersz, int &kolumna, char plansza[3][3]) {
	char wsp1, wsp2;
	printf("Podaj wspolrzedne: ");
	scanf(" %c%c", &wsp1, &wsp2);
	
	if ((wsp1 > 47) && (wsp1 < 51)) {
		wiersz = (int)wsp1 - 48;
		kolumna = (int)wsp2 - 97;
	}
	else
	{
		wiersz = (int)wsp2 - 48;
		kolumna = (int)wsp1 - 97;
	}
}

void LosowanieKomputera(int &wiersz, int &kolumna, char plansza[3][3]) {
	wiersz = GiveRandom(0, 3);
	kolumna = GiveRandom(0, 3);
	if (plansza[wiersz][kolumna] != ' ') {
		LosowanieKomputera(wiersz, kolumna, plansza);
	}
}


void Kolko() {
	char plansza[3][3];
	int wiersz, kolumna;
	char KOMPUTER = 'O';
	char GRACZ = 'X';
	memset(&plansza, ' ', sizeof plansza);
	
	while (1)
	{
		WypiszPlansze(plansza);

		WczytajWybor(wiersz, kolumna, plansza);
		if (Ruch(plansza, wiersz, kolumna, GRACZ)) {
			WypiszPlansze(plansza);
			printf("Wygrales\n");
			break;

		}

		LosowanieKomputera(wiersz, kolumna, plansza);
		Wait(3);
		if (Ruch(plansza, wiersz, kolumna, KOMPUTER)) {
			WypiszPlansze(plansza);
			printf("Przegrales\n");
			break;
		}
		
	}
}

//......................................................


void WypiszStatki(char plansza_gracza[10][10], char plansza_strzalow[10][10]) {

	printf("\n    Twoja plansza:\t\t\t  Plansza przeciwnika:\n\n");
	printf("  ");
	for (int g = 0; g < 10; g++) {
		printf("%d ", g);
	}
	printf("\t\t\t   ");
	for (int g = 0; g < 10; g++) {
		SetConsoleColor(TEXT_LIGHTGRAY);
		printf("%d ", g);
	}
	for (int a = 0; a < 10; a++) {
		SetConsoleColor(TEXT_LIGHTGRAY);
		printf("\n%d ", a);
		for (int b = 0; b < 10; b++) {
			switch (plansza_gracza[a][b])
			{
			case 9:
				SetConsoleColor(TEXT_RED);
				printf("%c ", 35);
				break;
			case 8:
				SetConsoleColor(TEXT_DARKGRAY);
				printf("%c ", 207);
				break;
			case 0:
				SetConsoleColor(TEXT_CYAN);
				printf("%c ", 177);
				break;
			case 5:
				SetConsoleColor(TEXT_CYAN);
				printf("%c ", 177);
				break;
			default:
				SetConsoleColor(TEXT_YELLOW);
				printf("%c ", 88);
				break;
			}
			
		}
		SetConsoleColor(TEXT_LIGHTGRAY);
		printf("\t\t\t %d ", a);

		for (int b = 0; b < 10; b++) {
			switch (plansza_strzalow[a][b])
			{
			case 9:
				SetConsoleColor(TEXT_RED);
				printf("%c ", 35);
				break;
			case 8:
				SetConsoleColor(TEXT_DARKGRAY);
				printf("%c ", 207);
				break;
			case 0:
				SetConsoleColor(TEXT_CYAN);
				printf("%c ", 177);
				break;
			case 5:
				SetConsoleColor(TEXT_CYAN);
				printf("%c ", 177);
				break;
			default:
				SetConsoleColor(TEXT_YELLOW);
				printf("%c ", 88);
				break;
			}
			SetConsoleColor(TEXT_LIGHTGRAY);
		}
	}

	printf("\n");
}

bool CzyNalezyDoPlanszy(int x, int y)
{
	if ((x < 0) || (y < 0) || (x > 9) || (y > 9))
	{
		return false;
	}
	return true;
}

void ZerujPlansze(char plansza[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			plansza[i][j] = 0;
		}
	}

}

void TworzStatek(int maszty, char plansza[10][10])
{
	int ile_prob = 0;
	int poziomo;
	int wiersz, kolumna;
	bool flag = false;

	while (!flag)
	{
		ile_prob++;
		if (ile_prob > 1000000) {
			system("cls");
			Statki();
		}
		flag = true;
		poziomo = GiveRandom(0, 2);

		if (poziomo == 1) {
			wiersz = GiveRandom(0, 10);
			kolumna = GiveRandom(0, 10 - maszty + 1);
			for (int i = 0; i < maszty; i++) {
				if (plansza[wiersz][kolumna + i] != 0) {
					flag = false;
					break;
				}
			}

		}
		else {
			kolumna = GiveRandom(0, 10);
			wiersz = GiveRandom(0, 10 - maszty + 1);
			for (int i = 0; i < maszty; i++) {
				if (plansza[wiersz + i][kolumna] != 0) {
					flag = false;
					break;
				}
			}
		}
	}

	if (poziomo == 1)
	{
		for (int j = - 1; j <= 1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz+j, kolumna - 1))
			{
				plansza[wiersz+j][kolumna - 1] = OTOCZENIE;
			}
		}
		for (int i = 0; i < maszty; i++)
		{
			if (CzyNalezyDoPlanszy(wiersz - 1, kolumna + i))
			{
				plansza[wiersz - 1][kolumna + i] = OTOCZENIE;
			}

			plansza[wiersz][kolumna + i] = maszty;
	

			if (CzyNalezyDoPlanszy(wiersz + 1, kolumna + i))
			{
				plansza[wiersz + 1][kolumna + i] = OTOCZENIE;
			}
		}
		for (int j = - 1; j <= + 1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz+j, kolumna + maszty))
			{
				plansza[wiersz+j][kolumna + maszty] = OTOCZENIE;
			}
		}

	}
	else
	{
		for (int j = -1; j <= 1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz - 1, kolumna + j))
			{
				plansza[wiersz - 1][kolumna + j] = OTOCZENIE;
			}
		}

		for (int i = 0; i < maszty; i++)
		{
			if (CzyNalezyDoPlanszy(wiersz + i, kolumna - 1))
			{
				plansza[wiersz + i ][kolumna - 1] = OTOCZENIE;
			}

			plansza[wiersz + i][kolumna] = maszty;

			if (CzyNalezyDoPlanszy(wiersz + i, kolumna + 1))
			{
				plansza[wiersz + i][kolumna + 1] = OTOCZENIE;
			}
		}

		for (int j = -1; j <= +1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz + maszty, kolumna + j))
			{
				plansza[wiersz + maszty][kolumna + j] = OTOCZENIE;
			}
		}

	}
}

void RozrysujStatki(char plansza[10][10])
{
	int statki[4] = { 4, 3, 2, 1 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < statki[i]; j++) {
			TworzStatek(i+1, plansza);
		}
	}

}




bool CzyZatopiony(int maszty, int wiersz, int kolumna, char plansza[10][10])
{
	// sprawdzam czy zatopiony
		// w czterech kierunkach
		// jesli znajde jeszcze jeden klocek o wartosci masztu oddalony o maszty-1 i nie napotkam pudla ani pustego to jest zatopiony

	// w gore
	for (int i = 0; i < maszty; i++)
	{
		if (CzyNalezyDoPlanszy(wiersz - i, kolumna))
		{
			if (plansza[wiersz - i][kolumna] == PUDLO || plansza[wiersz - i][kolumna] == OTOCZENIE)
			{
				break;

			}
			else if (plansza[wiersz - i][kolumna] == maszty)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < maszty; i++)
	{
		if (CzyNalezyDoPlanszy(wiersz + i, kolumna))
		{
			if (plansza[wiersz + i][kolumna] == PUDLO || plansza[wiersz + i][kolumna] == OTOCZENIE)
			{
				break;

			}
			else if (plansza[wiersz + i][kolumna] == maszty)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < maszty; i++)
	{
		if (CzyNalezyDoPlanszy(wiersz, kolumna - i))
		{
			if (plansza[wiersz][kolumna - i] == PUDLO || plansza[wiersz][kolumna - i] == OTOCZENIE)
			{
				break;

			}
			else if (plansza[wiersz][kolumna - i] == maszty)
			{
				return false;
			}
		}
	}
	for (int i = 0; i < maszty; i++)
	{
		if (CzyNalezyDoPlanszy(wiersz, kolumna + i))
		{
			if (plansza[wiersz][kolumna + i] == PUDLO || plansza[wiersz][kolumna + i] == OTOCZENIE)
			{
				break;

			}
			else if (plansza[wiersz][kolumna + i] == maszty)
			{
				return false;
			}
		}
	}
	return true;
}

struct pozostalo_statkow {
	int gracza;
	int komputera;
};

void Obtaczanie(int maszty, int wiersz, int kolumna, char plansza[10][10])
{
	bool poziomo = true;
	while (plansza[wiersz - 1][kolumna] == TRAFIONY) {
		wiersz--;
	}
	while (plansza[wiersz][kolumna - 1] == TRAFIONY) {
		kolumna--;
	}
	if (plansza[wiersz + 1][kolumna] == TRAFIONY) {
		poziomo = false;
	}

	if (poziomo)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz + j, kolumna - 1))
			{
				plansza[wiersz + j][kolumna - 1] = PUDLO;
			}
		}
		for (int i = 0; i < maszty; i++)
		{
			if (CzyNalezyDoPlanszy(wiersz - 1, kolumna + i))
			{
				plansza[wiersz - 1][kolumna + i] = PUDLO;
			}


			if (CzyNalezyDoPlanszy(wiersz + 1, kolumna + i))
			{
				plansza[wiersz + 1][kolumna + i] = PUDLO;
			}
		}
		for (int j = -1; j <= +1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz + j, kolumna + maszty))
			{
				plansza[wiersz + j][kolumna + maszty] = PUDLO;
			}
		}

	}
	else
	{
		for (int j = -1; j <= 1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz - 1, kolumna + j))
			{
				plansza[wiersz - 1][kolumna + j] = PUDLO;
			}
		}

		for (int i = 0; i < maszty; i++)
		{
			if (CzyNalezyDoPlanszy(wiersz + i, kolumna - 1))
			{
				plansza[wiersz + i][kolumna - 1] = PUDLO;
			}



			if (CzyNalezyDoPlanszy(wiersz + i, kolumna + 1))
			{
				plansza[wiersz + i][kolumna + 1] = PUDLO;
			}
		}

		for (int j = -1; j <= +1; j++)
		{
			if (CzyNalezyDoPlanszy(wiersz + maszty, kolumna + j))
			{
				plansza[wiersz + maszty][kolumna + j] = PUDLO;
			}
		}

	}
}

// plansza gracza
void StrzelanieKomputera0(char plansza[10][10], struct pozostalo_statkow *P)
{

	int wiersz = GiveRandom(0, 10);
	int kolumna = GiveRandom(0, 10);

	while (plansza[wiersz][kolumna] >= 8)
	{
		wiersz = GiveRandom(0, 10);
		kolumna = GiveRandom(0, 10);

	}
	if ((plansza[wiersz][kolumna] == 0) || (plansza[wiersz][kolumna] == 5)) {
		plansza[wiersz][kolumna] = PUDLO;
		printf("\nPudlo komputera\n");
	}
	else {
		int maszty = plansza[wiersz][kolumna];
		plansza[wiersz][kolumna] = TRAFIONY;
		(*P).gracza--;


		if (!CzyZatopiony(maszty, wiersz, kolumna, plansza))
		{
			//niezatopuiony
			printf("\nKomputer trafil w Twoj statek\n");

		}
		else {
			Obtaczanie(maszty, wiersz, kolumna, plansza);
			printf("\nKomputer zatopil Ci statek\n");
		}

	}

}

void StrzelanieKomputera1(char plansza[10][10], struct pozostalo_statkow* P, int wspol[3][2])
{
	int x = 0;
	int kolumna = wspol[x][1];
	int wiersz = wspol[x][0];
	int w, k;

	int ile = 0;

	if (kolumna != -1) {
		do {
			int kierunek = GiveRandom(0, 4);

			ile++;
			if (ile == 1000)
			{
				x++;
				printf("x: %d", x);
				ile = 0;
				kolumna = wspol[x][1];
				wiersz = wspol[x][0];
			}


			switch (kierunek)
			{
			case 0:
				k = -1;
				w = 0;
				break;
			case 1:
				k = 1;
				w = 0;
				break;
			case 2:
				k = 0;
				w = -1;
				break;
			case 3:
				k = 0;
				w = 1;
				break;
			}
		} while ((!CzyNalezyDoPlanszy(wiersz + w, kolumna + k)) || (plansza[wiersz + w][kolumna + k] == TRAFIONY) || (plansza[wiersz + w][kolumna + k] == PUDLO));

		//printf("koniec while'a\n");
		wiersz = wiersz + w;
		kolumna = kolumna + k;
	}
	else {
		do
		{
			wiersz = GiveRandom(0, 10);
			kolumna = GiveRandom(0, 10);
		} while (plansza[wiersz][kolumna] >= 8);
	}
	//printf("strzelam: %d %d\n", wiersz, kolumna);
	if ((plansza[wiersz][kolumna] == 0) || (plansza[wiersz][kolumna] == OTOCZENIE)) {
		plansza[wiersz][kolumna] = PUDLO;
		printf("\nPudlo komputera\n");
		//return wspol;
	}
	else {
		int maszty = plansza[wiersz][kolumna];
		plansza[wiersz][kolumna] = TRAFIONY;
		(*P).gracza--;
		if (!CzyZatopiony(maszty, wiersz, kolumna, plansza))
		{
			//niezatopuiony
			printf("\nKomputer trafil w Twoj statek\n");
			//return { wiersz, kolumna };
			//wspol = { wiersz, kolumna };
			wspol[2][0] = wspol[1][0];
			wspol[2][1] = wspol[1][1];

			wspol[1][0] = wspol[0][0];
			wspol[1][1] = wspol[0][1];


			wspol[0][0] = wiersz;
			wspol[0][1] = kolumna;

		}
		else {
			Obtaczanie(maszty, wiersz, kolumna, plansza);
			printf("\nKomputer zatopil Ci statek\n");
			for (int i = 0; i < 3; i++)
			{
				wspol[i][0] = -1;
				wspol[i][1] = -1;
			}
		}
	}
}

void StrzelanieGracza(char plansza[10][10], struct pozostalo_statkow* P)
{
	int wiersz, kolumna;
	bool zle = false;
	
	do
	{
		zle = false;
		printf("\nPodaj wiersz i kolumne rozdzielone spacja: ");
		scanf(" %d %d", &wiersz, &kolumna);
		if (CzyNalezyDoPlanszy(wiersz, kolumna) == false)
		{
			printf("\nWspolrzedne poza plansza\n");
			zle = true;
		}
		else if ((plansza[wiersz][kolumna] == TRAFIONY)|| (plansza[wiersz][kolumna] == PUDLO))
		{
			printf("\nJuz tu strzelales\n");
			zle = true;
		}
	} while (zle);

	if ((plansza[wiersz][kolumna] == 0) || (plansza[wiersz][kolumna] == 5)) {
		plansza[wiersz][kolumna] = PUDLO;
		printf("Pudlo\n");
	}
	else {
		int maszty = plansza[wiersz][kolumna];
		plansza[wiersz][kolumna] = TRAFIONY;
		(*P).komputera--;


		if (!CzyZatopiony(maszty, wiersz, kolumna, plansza))
		{
			//niezatopuiony
			printf("\nTrafiles w statek komputera\n");

		}
		else {
			Obtaczanie(maszty, wiersz, kolumna, plansza);
			printf("\nZatopiles statek komputera\n");
		}

	}
	

}

bool CzyKoniecStatkow(struct pozostalo_statkow* P)
{
	if ((*P).gracza == 0)
	{
		printf("\nPrzegrales\n");
		return true;
	}
	else if ((*P).komputera == 0)
	{
		printf("\nWygrales!\n");
		return true;
	}
	else
	{
		return false;
	}
}


void Statki() {

	// 4 x 1   3 x 2   2 x 3 1 x 4
	int poziom = GetLevel();
	struct pozostalo_statkow* P = (struct pozostalo_statkow*)malloc(sizeof(struct pozostalo_statkow));
	*P = { 20, 20 };

	//0 nie ma, 1 jest, 2 nic nie moze byc
	char plansza_gracza[10][10] =
	{
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
	};

	char plansza_komputera[10][10] =
	{
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
	};
	int ostatni_traf[3][2] = { { -1, -1 }, {-1, -1}, {-1, -1} };
	RozrysujStatki(plansza_gracza);
	RozrysujStatki(plansza_komputera);
	WypiszStatki(plansza_gracza, plansza_komputera);
	bool koniec = false;
	while (!koniec) {
		
		StrzelanieGracza(plansza_komputera, P);
		printf("Komputer strzela");
		Wait(3);
		if (poziom == 0) {
			StrzelanieKomputera0(plansza_gracza, P);
		}
		else {
			StrzelanieKomputera1(plansza_gracza, P, ostatni_traf);
		}
		Sleep(700);
		system("cls");
		WypiszStatki(plansza_gracza, plansza_komputera);
		koniec = CzyKoniecStatkow(P);
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	//SetWindow(200, 100);
	
	//printf("Witaj!\n\nGry do wyboru:\n1. Statki\n2. Cztery w linii\n3. Wisielec\n4. Kolko i krzyzyk\n\nPodaj nr gry, w ktora chcesz zagrac: ");
	//int wybor;

	//Wisielec();
	//Kolko();
	Statki();
	//scanf("%d", &wybor);
	//switch (wybor) {
	//case 1:
	//	//statki();
	//case 2:
	//	//kulki();
	//case 3:
	//	//Wisielec();
	//case 4:
	//	//kolko();
	//default:
	//	printf("Podany zly nr gry");
	//}
	SetConsoleColor(0);
	return 1;
}


