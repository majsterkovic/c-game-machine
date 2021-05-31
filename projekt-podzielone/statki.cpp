#include "definicje.h"

void WypiszStatki(char plansza_gracza[10][10], char plansza_strzalow[10][10], struct ostatni_strzal O, int koniec) {
    system("cls");
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
                    if (O.kto == 1 && O.w == a && O.k == b)
                    {
                        SetConsoleColor(TEXT_GREEN);
                    }
                    printf("%c ", 35);
                    break;
                case 8:
                    SetConsoleColor(TEXT_DARKGRAY);
                    if (O.kto == 1 && O.w == a && O.k == b)
                    {
                        SetConsoleColor(TEXT_GREEN);
                    }

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
        if (koniec == false) {
            for (int b = 0; b < 10; b++) {
                switch (plansza_strzalow[a][b])
                {
                    case 9:
                        SetConsoleColor(TEXT_RED);
                        if (O.kto == 0 && O.w == a && O.k == b)
                        {
                            SetConsoleColor(TEXT_GREEN);
                        }

                        printf("%c ", 35);
                        break;
                    case 8:
                        SetConsoleColor(TEXT_DARKGRAY);
                        if (O.kto == 0 && O.w == a && O.k == b)
                        {
                            SetConsoleColor(TEXT_GREEN);
                        }

                        printf("%c ", 207);
                        break;
                    default:
                        SetConsoleColor(TEXT_CYAN);
                        printf("%c ", 177);
                        break;
                        /*case 5:
                            SetConsoleColor(TEXT_CYAN);
                            printf("%c ", 177);
                            break;
                        default:
                            SetConsoleColor(TEXT_YELLOW);
                            printf("%c ", 88);
                            break;*/
                }
                SetConsoleColor(TEXT_LIGHTGRAY);
            }
        }
        else {
            for (int b = 0; b < 10; b++) {
                switch (plansza_strzalow[a][b])
                {
                    case 9:

                        SetConsoleColor(TEXT_RED);
                        if (O.kto == 1 && O.w == a && O.k == b)
                        {
                            SetConsoleColor(TEXT_GREEN);
                        }
                        printf("%c ", 35);
                        break;
                    case 8:
                        SetConsoleColor(TEXT_DARKGRAY);
                        if (O.kto == 1 && O.w == a && O.k == b)
                        {
                            SetConsoleColor(TEXT_GREEN);
                        }

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
        for (int j = -1; j <= 1; j++)
        {
            if (CzyNalezyDoPlanszy(wiersz + j, kolumna - 1))
            {
                plansza[wiersz + j][kolumna - 1] = OTOCZENIE;
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
        for (int j = -1; j <= +1; j++)
        {
            if (CzyNalezyDoPlanszy(wiersz + j, kolumna + maszty))
            {
                plansza[wiersz + j][kolumna + maszty] = OTOCZENIE;
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
                plansza[wiersz + i][kolumna - 1] = OTOCZENIE;
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
            TworzStatek(i + 1, plansza);
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
void StrzelanieKomputera0(char plansza[10][10], struct pozostalo_statkow* P)
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

void StrzelanieKomputera1(char plansza[10][10], struct pozostalo_statkow* P, struct strzelanie* S, struct ostatni_strzal* O)
{
    int x = 0;
    int kolumna = (*S).trafiony[1];
    int wiersz = (*S).trafiony[0];
    int w, k, kierunek;
    bool znal = false;

    if ((*S).stan == 1)
    {
        do
        {
            kierunek = GiveRandom(0, 4);

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



    else if ((*S).stan > 1)
    {
        if ((*S).kierunek > 1)
        {
            for (int i = 0; i < (*S).maszty; i++)
            {
                if (CzyNalezyDoPlanszy(wiersz - i, kolumna))
                {
                    if (plansza[wiersz - i][kolumna] == PUDLO)
                    {
                        break;
                    }

                    if (plansza[wiersz - i][kolumna] != TRAFIONY)
                    {
                        wiersz = wiersz - i;
                        znal = true;
                        break;
                    }
                }
            }
            if (znal == false)
            {
                for (int i = 0; i < (*S).maszty; i++)
                {
                    if (CzyNalezyDoPlanszy(wiersz + i, kolumna))
                    {
                        if (plansza[wiersz + i][kolumna] == PUDLO)
                        {
                            break;
                        }

                        if (plansza[wiersz + i][kolumna] != TRAFIONY)
                        {
                            wiersz = wiersz + i;
                            znal = true;
                            break;
                        }
                    }
                }

            }
        }
        else if ((*S).kierunek < 2)
        {
            for (int i = 0; i < (*S).maszty; i++)
            {
                if (CzyNalezyDoPlanszy(wiersz, kolumna - i))
                {

                    if (plansza[wiersz][kolumna - i] == PUDLO)
                    {
                        break;
                    }

                    if (plansza[wiersz][kolumna - i] != TRAFIONY)
                    {
                        kolumna = kolumna - i;
                        znal = true;
                        break;
                    }
                }
            }
            if (znal == false)
            {
                for (int i = 0; i < (*S).maszty; i++)
                {
                    if (CzyNalezyDoPlanszy(wiersz, kolumna + i))
                    {
                        if (plansza[wiersz][kolumna + i] == PUDLO)
                        {
                            break;
                        }
                        if (plansza[wiersz][kolumna + i] != TRAFIONY)
                        {
                            kolumna = kolumna + i;
                            znal = true;
                            break;
                        }
                    }
                }

            }
        }

    }

    else {
        do
        {
            wiersz = GiveRandom(0, 10);
            kolumna = GiveRandom(0, 10);
        } while (plansza[wiersz][kolumna] >= 8);
    }

    (*O).w = wiersz;
    (*O).k = kolumna;
    (*O).kto = 1;

    if ((plansza[wiersz][kolumna] == 0) || (plansza[wiersz][kolumna] == OTOCZENIE)) {
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

            if ((*S).stan == 1)
            {
                (*S).kierunek = kierunek;
            }

            ((*S).stan)++;
            (*S).trafiony[0] = wiersz;
            (*S).trafiony[1] = kolumna;
            (*S).maszty = maszty;


        }
        else {
            Obtaczanie(maszty, wiersz, kolumna, plansza);
            printf("\nKomputer zatopil Ci statek\n");
            (*S).stan = 0;
            (*S).maszty = 0;
            (*S).trafiony[1] = -1;
            (*S).trafiony[0] = -1;

        }
    }
}

void StrzelanieGracza(char plansza[10][10], struct pozostalo_statkow* P, struct ostatni_strzal* O)
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
        else if ((plansza[wiersz][kolumna] == TRAFIONY) || (plansza[wiersz][kolumna] == PUDLO))
        {
            printf("\nJuz tu strzelales\n");
            zle = true;
        }
    } while (zle);

    (*O).w = wiersz;
    (*O).k = kolumna;
    (*O).kto = 0;

    if ((plansza[wiersz][kolumna] == 0) || (plansza[wiersz][kolumna] == 5)) {
        plansza[wiersz][kolumna] = PUDLO;
        printf("\nPudlo\n");
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
    Sleep(400);

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

void InstrukcjaStatkow() {
    system("cls");
    printf("Przed Toba gra w statki\n\nPo lewej stronie znajduje sie plansza, na ktorej umieszcone sa Twoje statki,\nnatomiast po prawej plansza komputera, do ktorej strzelasz");
    printf("\nStatki sa koloru ");
    SetConsoleColor(TEXT_YELLOW);
    printf("zoltego,\n");
    SetConsoleColor(TEXT_CYAN);
    printf("niebieskie ");
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("pola oznaczaja wode\n");
    SetConsoleColor(TEXT_RED);
    printf("czerwone ");
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("natomiast zatopiony statek\n");
    SetConsoleColor(TEXT_GREEN);
    printf("zielone ");
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("pokazuja ostatni strzal,\na ");
    SetConsoleColor(TEXT_DARKGRAY);
    printf("szare ");
    SetConsoleColor(TEXT_LIGHTGRAY);
    printf("to pudla.");
    printf("\n\nNacisnij dowolny klawisz, by kontynuowac ");
    _getche();


}


void Statki() {

    // 4 x 1   3 x 2   2 x 3 1 x 4
    int poziom = GetLevel();

    InstrukcjaStatkow();

    struct pozostalo_statkow* P = (struct pozostalo_statkow*)malloc(sizeof(struct pozostalo_statkow));

    (*P).gracza = 20;
    (*P).komputera = 20;

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



    struct strzelanie S;
    S.kierunek = 0;
    S.stan = 0;
    S.trafiony[0] = -1;
    S.trafiony[1] = -1;
    S.maszty = 0;

    struct strzelanie* wskS = &S;

    struct ostatni_strzal O;
    O.w = -1;
    O.k = -1;
    O.kto = 0;
    struct ostatni_strzal* wskO = &O;

    RozrysujStatki(plansza_gracza);
    RozrysujStatki(plansza_komputera);


    bool koniec = false;
    while (!koniec) {

        WypiszStatki(plansza_gracza, plansza_komputera, O, koniec);
        StrzelanieGracza(plansza_komputera, P, wskO);
        WypiszStatki(plansza_gracza, plansza_komputera, O, koniec);


        printf("\nKomputer strzela");
        Wait(3);
        if (poziom == 0) {
            StrzelanieKomputera0(plansza_gracza, P);
        }
        else {
            StrzelanieKomputera1(plansza_gracza, P, wskS, wskO);
        }
        Sleep(700);

        koniec = CzyKoniecStatkow(P);
    }
    WypiszStatki(plansza_gracza, plansza_komputera, O, koniec);
    printf("\nNacisnij dowolny klawisz, by wrocic do menu ");
    _getche();
}

