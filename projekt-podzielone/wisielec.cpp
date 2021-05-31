#include "definicje.h"

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

void OdkryjLitere(int *proby, char haslo[2][30], int alfabet[])
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
        (*proby)--;
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
    int *wsk_proby = &proby;
    char baza_hasel[10][30] = {
            "INFORMATYKA",
            "PROGRAMOWANIE",
            "NISKOPOZIOMOWE",
            "MATEMATYKA",
            "PROBABILISTYKA",
            "ALGORYTMIKA",
            "ELEKTONIKA"
    };
    char haslo[2][30];  //{ "INFA", "0000" }
    strcpy(haslo[0], baza_hasel[GiveRandom(0,7)]);
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
        OdkryjLitere(wsk_proby, haslo, alfabet);
        system("cls");

    }

    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("\n\nNacisnij dowolny klawisz, by wrocic do menu ");
    _getche();
}

