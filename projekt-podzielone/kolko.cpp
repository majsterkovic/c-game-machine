#include "definicje.h"

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

//zwraca true, jeśli w jednej linii 3 symbole któregoś z graczy
bool SprawdzWygrana(char plansza[3][3], int w, int k, char znak)
{
    if ((plansza[w][0] == znak) && (plansza[w][0] == plansza[w][1]) && (plansza[w][1] == plansza[w][2]))
    {
        return true;
    }
    if ((plansza[0][k] == znak) && (plansza[0][k] == plansza[1][k]) && (plansza[1][k] == plansza[2][k]))
    {
        return true;
    }
    if ((k+w)%2==0)
    {
        if ((plansza[0][0] == znak) && (plansza[0][0] == plansza[2][2]) && (plansza[1][1] == plansza[2][2]))
        {
            return true;
        }
        if ((plansza[0][2] == znak) && (plansza[0][2] == plansza[2][0]) && (plansza[1][1] == plansza[0][2]))
        {
            return true;
        }
    }
    return false;

}

//zapisuje współrzędne na planszę i automatycznie sprawdza, czy nie spowodowały one wygranej
bool Ruch(char plansza[3][3], int wiersz, int kolumna, char znak) {
    plansza[wiersz][kolumna] = znak;

    return SprawdzWygrana(plansza, wiersz, kolumna, znak);
}

void WczytajWybor(int *wiersz, int *kolumna, char plansza[3][3]) {
    char wsp1, wsp2;
    printf("Podaj wspolrzedne: ");
    scanf(" %c%c", &wsp1, &wsp2);

    //mozna wpisac wspolrzedne obojetnie w jakiej kolejnosci
    if ((wsp1 > 47) && (wsp1 < 51)) { //1. wspolrzedna to liczba
        *wiersz = (int)wsp1 - 48;
        *kolumna = (int)wsp2 - 97;
    }
    else //1. wspolrzedna to litera
    {
        *wiersz = (int)wsp2 - 48;
        *kolumna = (int)wsp1 - 97;
    }

    //jesli podano zle wspolrzedne, funkcja wywoluje sie jeszcze raz i ponownie o nie prosi
    if (*wiersz < 0 || *kolumna < 0 || *kolumna > 2 || *wiersz > 2) {
        printf("Podano zle wspolrzedne\n"); //wspolrzedne poza zakresem
        WczytajWybor(wiersz, kolumna, plansza);
    }

    if (plansza[*wiersz][*kolumna] != ' ') { //wspolrzedne na zajete pole
        printf("Podano zle wspolrzedne\n");
        WczytajWybor(wiersz, kolumna, plansza);
    }
    fflush(stdin);
}


void LosowanieKomputera0(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch* O) {
    //jesli ma szanse na wygrana po jednym ruchu, to go wykonuje
    if (CzyMozliwyKoniecGry(wiersz, kolumna, plansza, O, 'O')) {
        return;
    }
    //jeśli gracz może wygrać w nastepnym ruchu, to go blokuje
    if (CzyMozliwyKoniecGry(wiersz, kolumna, plansza, O, 'X')) {
        return;
    }
    //w pozosyałych przypadkach losowo
    *wiersz = GiveRandom(0, 3);
    *kolumna = GiveRandom(0, 3);
    if (plansza[*wiersz][*kolumna] != ' ') {
        LosowanieKomputera0(wiersz, kolumna, plansza, O);
    }
}


void PierwszyRuchKomputera1(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch *O) {
    //printf("Pierwszy ruch komputera");
    *kolumna = 2 * GiveRandom(0, 2);
    *wiersz = 2 * GiveRandom(0, 2);
    (*O).w = *wiersz;
    (*O).k = *kolumna;
}

void DrugiRuchKomputera1(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch* O) {
    //printf("Drugi ruch komputera\n");
    int w = (*O).w;
    int k = (*O).k;
    int nk = (k == 2) ? k - 2 : k + 2;
    int nw = (w == 2) ? w - 2 : w + 2;

    // sprawdzanie czy gracz blokuje nas poziomo

    if (w == *wiersz) {
        //plansza[nw][k] = 'O';
        *wiersz = nw;
        *kolumna = k;
    }
    else if (k == *kolumna) {
        //plansza[w][nk] = 'O';
        *wiersz = w;
        *kolumna = nk;
    }
    else {
        if (*wiersz != 1) {
            //plansza[wiersz][nk] = 'O';
            *kolumna = k;
        }
        else if (*kolumna != 1) {
            //plansza[nw][kolumna] = 'O'
            *wiersz = w;
        }
    }
    (*O).w = *wiersz;
    (*O).k = *kolumna;

}

bool CzyMozliwyKoniecGry(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch* O, char kto) {
    int counter = 0;
    int w;
    int k;
    if (kto == 'O') {
        w = (*O).w;
        k = (*O).k;
    }
    else {
        w = *wiersz;
        k = *kolumna;
    }
    for (int i = 0; i < 3; i++) {
        if (plansza[w][i] == kto) {
            counter++;
        }
    }
    if (counter == 2) {
        for (int i = 0; i < 3; i++) {
            if (plansza[w][i] == ' ') {
                *wiersz = w;
                *kolumna = i;
                return true;
            }
        }
    }

    counter = 0;
    for (int i = 0; i < 3; i++) {
        if (plansza[i][k] == kto) {
            counter++;
        }
    }
    if (counter == 2) {
        for (int i = 0; i < 3; i++) {
            if (plansza[i][k] == ' ') {
                *wiersz = i;
                *kolumna = k;
                return true;
            }
        }
    }

    counter = 0;
    for (int i = 0; i < 3; i++) {
        if (plansza[i][i] == kto) {
            counter++;
        }
    }
    if (counter == 2) {
        for (int i = 0; i < 3; i++) {
            if (plansza[i][i] == ' ') {
                *wiersz = i;
                *kolumna = i;
                return true;
            }
        }
    }

    counter = 0;
    for (int i = 0; i < 3; i++) {
        if (plansza[i][2-i] == kto) {
            counter++;
        }
    }
    if (counter == 2) {
        for (int i = 0; i < 3; i++) {
            if (plansza[i][2-i] == ' ') {
                *wiersz = i;
                *kolumna = 2-i;
                return true;
            }
        }
    }

    return false;
}

void TrzeciRuchKomputera1(int *wiersz, int *kolumna, char plansza[3][3], struct ostatni_ruch* O)
{

    if (CzyMozliwyKoniecGry(wiersz, kolumna, plansza, O, 'X')) {
        return;
    }

    do {
        *kolumna = 2 * GiveRandom(0, 2);
        *wiersz = 2 * GiveRandom(0, 2);
    } while (plansza[*wiersz][*kolumna] != ' ' || plansza[*wiersz][1] != ' ' || plansza[1][*kolumna] != ' ');

}

void CzwartyRuchKomputera1(int *wiersz, int *kolumna) {
    *wiersz = 1;
    *kolumna = 1;
}

bool CzyZostaloWolnePole(char plansza[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
        {
            if (plansza[i][j] == ' ')
            {
                return true;
            }
        }
    }
    return false;
}


void Kolko() {
    int poziom = GetLevel();
    char plansza[3][3];
    int wiersz, kolumna;
    int *wsk_wiersz = &wiersz;
    int *wsk_kolumna = &kolumna;
    char KOMPUTER = 'O';
    char GRACZ = 'X';
    memset(&plansza, ' ', sizeof plansza);
    struct ostatni_ruch O;
    struct ostatni_ruch* wskO = &O;
    (*wskO).w = -1;
    (*wskO).k = -1;

    if (poziom == 0) {
        while (1)
        {
            WypiszPlansze(plansza);

            WczytajWybor(wsk_wiersz, wsk_kolumna, plansza);
            if (Ruch(plansza, wiersz, kolumna, GRACZ)) {
                WypiszPlansze(plansza);
                printf("Wygrales");
                break;

            }
            if (!CzyZostaloWolnePole(plansza))
            {
                WypiszPlansze(plansza);
                printf("Remis");
                break;
            }
            WypiszPlansze(plansza);

            LosowanieKomputera0(wsk_wiersz, wsk_kolumna, plansza, wskO);
            Wait(3);
            if (Ruch(plansza, wiersz, kolumna, KOMPUTER)) {
                WypiszPlansze(plansza);
                printf("Przegrales");
                break;
            }
        }
    }
    else {
        int counter = 0;
        while (1)
        {
            counter++;

            WypiszPlansze(plansza);

            if (plansza[1][1] == 'X') {
                counter = 10;
            }

            switch (counter) {
                case 1:
                    PierwszyRuchKomputera1(wsk_wiersz, wsk_kolumna, plansza, wskO);
                    break;
                case 2:
                    DrugiRuchKomputera1(wsk_wiersz, wsk_kolumna, plansza, wskO);
                    break;
                case 3:
                    TrzeciRuchKomputera1(wsk_wiersz, wsk_kolumna, plansza, wskO);
                    break;
                case 4:
                    CzwartyRuchKomputera1(wsk_wiersz, wsk_kolumna);
                    break;
                default:
                    LosowanieKomputera0(wsk_wiersz, wsk_kolumna, plansza, wskO);
                    break;
            }

            //LosowanieKomputera1(wiersz, kolumna, plansza);
            Wait(3);
            if (Ruch(plansza, wiersz, kolumna, KOMPUTER)) {
                WypiszPlansze(plansza);
                printf("Przegrales");
                break;

            }
            if (!CzyZostaloWolnePole(plansza))
            {
                WypiszPlansze(plansza);
                printf("Remis");
                break;
            }
            WypiszPlansze(plansza);

            WczytajWybor(wsk_wiersz, wsk_kolumna, plansza);

            if (Ruch(plansza, wiersz, kolumna, GRACZ)) {
                WypiszPlansze(plansza);
                printf("Wygrales");
                break;
            }
        }
    }
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("\n\nNacisnij dowolny klawisz, by wrocic do menu ");
    _getche();

}
