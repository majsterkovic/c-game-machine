#include "definicje.h"

//czy w danym polu mozna umiescic kulke
bool CzyMozliwaKulka(int w, int k, char plansza[10][10]) {
    if (w == 9)
    {
        if (plansza[w][k] == 0)
        {
            return true;
        }
    }
    else if (plansza[w + 1][k] != 0) {
        if (plansza[w][k] == 0) {
            return true;
        }
    }
    return false;
}

void WypiszKulki(char plansza[10][10]) {
    system("cls");
    printf("  ");
    for (int g = 0; g < 10; g++) {
        printf("%d ", g);
    }
    for (int i = 0; i < 10; i++) {
        printf("\n  ");
        for (int j = 0; j < 10; j++) {
            switch (plansza[i][j]) {
                case 0:
                    SetConsoleColor(TEXT_DARKGRAY);
                    printf("%c ", 177);
                    SetConsoleColor(TEXT_LIGHTGRAY);
                    break;
                case 1:
                    SetConsoleColor(TEXT_YELLOW);
                    printf("%c ", 254);
                    SetConsoleColor(TEXT_LIGHTGRAY);
                    break;
                case 2:
                    SetConsoleColor(TEXT_BLUE);
                    printf("%c ", 254);
                    SetConsoleColor(TEXT_LIGHTGRAY);
                    break;
            }
        }
    }
}

void KulkaGracza(struct ostatni_strzal *O, char plansza[10][10]) {
    int w, k;
    w = 0;
    printf("\n\nPodaj kolumne, do ktorej chcesz wrzucic kulke: ");
    scanf(" %d", &k);
    //jesli podano zla kolumne, to pyta o nia jeszcze raz
    if (!CzyNalezyDoPlanszy(w, k) || plansza[0][k] != 0) {
        printf("Zla kolumna");
        Sleep(300);
        KulkaGracza(O, plansza);
    }
    //obliczanie wiersza
    while (plansza[w][k] == 0 && CzyNalezyDoPlanszy(w, k)) {
        w++;
    }
    w--;

    //MessageBeep(MB_ICONWARNING);

    plansza[w][k] = 1;
    (*O).k = k;
    (*O).w = w;
    (*O).kto = 1;

    fflush(stdin);
}

//losowe
void KulkaKomputera0(struct ostatni_strzal* O, char plansza[10][10]) {
    int w, k;

    do {
        w = GiveRandom(0, 10);
        k = GiveRandom(0, 10);
    } while (!CzyMozliwaKulka(w, k, plansza));

    printf("w: %d, k: %d\n", w, k);
    plansza[w][k] = 2;
    (*O).k = k;
    (*O).w = w;
    (*O).kto = 2;
}

//obliczanie jaka jest maksymalna liczba kulek w liniach przecinajacych punkt okreslony wspolrzednymi
int MaxKulekWLinii(int wiersz, int kolumna, char plansza[10][10], int kto) {
    int w = wiersz;
    int k = kolumna;

    int stan[4] = { 1, 1, 1, 1 };
    //0 dolgora
    //1 lewoprawo
    //2 lewodol->prawogora
    //3 prawodol->lewogora

    while (plansza[w - 1][k] == kto) {
        if (w == 0) {
            break;
        }
        stan[0]++;
        w--;
    }
    w = wiersz;
    while (plansza[w + 1][k] == kto) {
        if (w == 9) {
            break;
        }
        stan[0]++;
        w++;
    }
    w = wiersz;
    k = kolumna;

    while (plansza[w][k - 1] == kto) {
        if (k == 0) {
            break;
        }
        stan[1]++;
        k--;
    }
    k = kolumna;
    while (plansza[w][k + 1] == kto) {
        if (k == 9) {
            break;
        }
        stan[1]++;
        k++;
    }


    w = wiersz;
    k = kolumna;

    while (plansza[w - 1][k + 1] == kto) {
        if (k == 9 || w == 0) {
            break;
        }
        stan[2]++;
        w--;
        k++;
    }

    w = wiersz;
    k = kolumna;

    while (plansza[w + 1][k - 1] == kto) {
        if (k == 0 || w == 9) {
            break;
        }
        stan[2]++;
        w++;
        k--;
    }

    w = wiersz;
    k = kolumna;

    while (plansza[w + 1][k + 1] == kto) {
        if (k == 9 || w == 9) {
            break;
        }
        stan[3]++;
        w++;
        k++;
    }

    w = wiersz;
    k = kolumna;

    while (plansza[w - 1][k - 1] == kto) {
        if (k == 0 || w == 0) {
            break;
        }
        stan[3]++;
        w--;
        k--;
    }
    int maks = stan[0];
    for (int i = 1; i < 4; i++) {
        maks = max(maks, stan[i]);
    }
    return maks;
}

void KulkaKomputera1(struct ostatni_strzal* O, char plansza[10][10]) {
    int w, k;
    int tmpw, tmpk;
    int ile = 1;

    if (CzyMozliwaKulka((*O).w, (*O).k + 1, plansza)){
        w = (*O).w;
        k = (*O).k + 1;
        ile = MaxKulekWLinii(w, k, plansza, 2);
    }
    else {
        do {
            w = GiveRandom(0, 10);
            k = GiveRandom(0, 10);
        } while (!CzyMozliwaKulka(w, k, plansza));
    }


    for (int i = 0; i < 10; i++) {
        do {
            tmpw = GiveRandom(0, 10);
            tmpk = i;
        } while (!CzyMozliwaKulka(tmpw, tmpk, plansza));
        //jesli znajdzie dla siebie szanse na wygrana to ja wykorzystuje
        if (MaxKulekWLinii(tmpw, tmpk, plansza, 2) > 3) {
            w = tmpw;
            k = tmpk;
            break;
            //jesli gracz ma szanse na wygrana w nastepnej turze to go blokuje
        } else if (MaxKulekWLinii(tmpw, tmpk, plansza, 1) > 3) {
            w = tmpw;
            k = tmpk;
            break;
            //jesli zadne z powyzszych, to stawia tam, gdzie bedzie mial najwiecej kulek w linii
        } else if (MaxKulekWLinii(tmpw, tmpk, plansza, 2) > ile) {
            ile = MaxKulekWLinii(tmpw, tmpk, plansza, 2);
            w = tmpw;
            k = tmpk;
        }
    }
    plansza[w][k] = 2;
    (*O).k = k;
    (*O).w = w;
    (*O).kto = 2;
}

//sprawdza, czy gdzies istnieja 4 kulki w linii
bool CzyKoniecKulek(char plansza[10][10], struct ostatni_strzal *O)
{
    if (MaxKulekWLinii((*O).w, (*O).k, plansza, (*O).kto) >= 4) {
        return true;
    }
    return false;
}

void Kulki() {

    int poziom = GetLevel();
    char plansza[10][10] =
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
    struct ostatni_strzal O;
    struct ostatni_strzal *wskO = &O;

    while (true) {
        WypiszKulki(plansza);
        KulkaGracza(wskO, plansza);
        if (CzyKoniecKulek(plansza, wskO))
        {
            WypiszKulki(plansza);
            printf("\n\nWygral gracz");
            break;
        }
        WypiszKulki(plansza);
        printf("\n\nKomputer strzela");
        Wait(3);
        if (poziom == 0) {
            KulkaKomputera0(wskO, plansza);
        }
        else {
            KulkaKomputera1(wskO, plansza);
        }
        if (CzyKoniecKulek(plansza, wskO))
        {
            WypiszKulki(plansza);
            printf("\n\nWygral komputer");
            break;
        }
    }
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("\n\nNacisnij dowolny klawisz, by wrocic do menu ");
    _getche();

}

