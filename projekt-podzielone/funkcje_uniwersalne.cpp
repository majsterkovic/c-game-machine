#include "definicje.h"

void SetConsoleColor(int k)
{
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Handle, k);
}

int GiveRandom(int start, int ile_liczb) {
    return (rand()%ile_liczb) + start;
}

int GetLevel() {
    system("cls");
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

void MenuGlowne() {
    system("cls");

    printf("Witaj!\n\nGry do wyboru:\n");
    SetConsoleColor(TEXT_CYAN);
    printf("[1] Statki\n");
    SetConsoleColor(TEXT_BROWN);
    printf("[2] Cztery w linii\n");
    SetConsoleColor(TEXT_MAGENTA);
    printf("[3] Wisielec\n");
    SetConsoleColor(TEXT_GREEN);
    printf("[4] Kolko i krzyzyk\n");
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("\n[0] Wyjscie\n\n");
    printf("Podaj numer akcji: ");
    int wybor;
    scanf(" %d", &wybor);

    switch (wybor) {
        case 0:
            exit(0);
        case 1:
            Statki();
            break;
        case 2:
            Kulki();
            break;
        case 3:
            Wisielec();
            break;
        case 4:
            Kolko();
            break;
        default:
            MenuGlowne();
    }
    MenuGlowne();
}




