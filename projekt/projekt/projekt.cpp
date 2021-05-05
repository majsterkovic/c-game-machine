#include <windows.h>
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
	for (int i = 0; i < strlen(haslo[0]); i++)
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
		for (int j = 0; j < strlen(haslo[0]); j++) {
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
	for (int i = 0; i < strlen(haslo[1]);  i++) {
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

bool SprawdzWygrana(int k, int w)
{
	if ()
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ruch(char plansza[3][3], int wiersz, int kolumna, char znak) {
	plansza[wiersz][kolumna] = znak;

	return SprawdzWygrana(wiersz, kolumna);
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
	int wiersz = GiveRandom(0, 3);
	int kolumna = GiveRandom(0, 3);
	if (plansza[wiersz][kolumna] != ' ') {
		LosowanieKomputera(plansza);
	}
}




void Kolko() {
	char plansza[3][3];
	int wiersz, kolumna;
	char KOMPUTER = 'O';
	char GRACZ = 'X';
	memset(&plansza, ' ', sizeof plansza);
	
	while (1) {
		WypiszPlansze(plansza);
		WczytajWybor(wiersz, kolumna, plansza);
		Ruch(plansza, wiersz, kolumna, GRACZ);
		LosowanieKomputera(wiersz, kolumna, plansza);
		Ruch(plansza, wiersz, kolumna, KOMPUTER);

		
	}
}



int main()
{
	srand((unsigned int)time(NULL));
	//SetWindow(200, 100);
	
	//printf("Witaj!\n\nGry do wyboru:\n1. Statki\n2. Cztery w linii\n3. Wisielec\n4. Kolko i krzyzyk\n\nPodaj nr gry, w ktora chcesz zagrac: ");
	//int wybor;

	//Wisielec();
	Kolko();
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


