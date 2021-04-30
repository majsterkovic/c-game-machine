#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TEXT_DARKGRAY 0x8
#define TEXT_MAGENTA 0x5
#define TEXT_RED 0xC
#define TEXT_GREEN 0xA
#define TEXT_CYAN 0x3

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



void WypiszLitery(int alfabet[])
{
	for (int i = 0; i < 26; i++) {
		if (alfabet[i] == 1) {
			SetConsoleColor(TEXT_MAGENTA);
			printf(" %c", 35);
			SetConsoleColor(15);
		}
		else {
			printf(" %c", i + 65);
		}
	}
	printf("\n");
}

void RysujWisielca(int proba) {
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

void WczytajLitere(int alfabet[])
{
	printf("Podaj swoja litere: ");
	fflush(stdin);
	char litera;
	scanf("%c", &litera);
	getchar();
	litera = toupper(litera);
	if (alfabet[(int)litera - 65] == 1) {
		printf("\nLitera zostala juz wczesniej wczytana, podaj kolejna.\n");
		WczytajLitere(alfabet);
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

void Wisielec(int poziom)
{
	
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
			printf("\nWykorzystano wszystkie proby, umierasz\n");
			break;
		}
		else if (hasloOdgadniete(haslo))
		{
			SetConsoleColor(TEXT_GREEN);
			printf("\nWygrana!\n");
			break;
		}

		WypiszLitery(alfabet);
		
		WczytajLitere(alfabet);
		OdkryjLitere(proby, haslo, alfabet);
		system("cls");


	}




}



int main()
{
	srand((unsigned int)time(NULL));
	//SetWindow(200, 100);
	
	//printf("Witaj!\n\nGry do wyboru:\n1. Statki\n2. Cztery w linii\n3. Wisielec\n4. Kolko i krzyzyk\n\nPodaj nr gry, w ktora chcesz zagrac: ");
	//int wybor;

	Wisielec(1);
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


