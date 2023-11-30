#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
const int N = 4;
using namespace std;

double horner(double wspolczynniki[], int stopien, double x)
{
    double wynik = wspolczynniki[0];

    for (int i = 1; i <= stopien; i++)
        wynik = wynik * x + wspolczynniki[i];
    return wynik;
}
/*
double f(double x, double wspl[N + 1])
{
    double w = horner(wspl, N, x);
    return w;
}

double f2(double x, double wspl[N + 1])
{
    double cs = cos(x);
    double w = x * x * cs * cs * cs;
    return w;
}
*/
double f0(double x, double wspl[N + 1], int numer)
{
    switch (numer) {
    case 1:
    {
        double w = horner(wspl, N, x);
        return w;
        exit;
    }
    case 2:
    {
        double cs = cos(x);
        double w = x * x * cs * cs * cs;
        return w;
        exit;
    }
    default:
        cout << "blad" << endl;
        exit;
    }
}
double trapez(double a, double b, double n, double wspl[N + 1], int numer)
{
    double suma = 0;

    double h = (b - a) / n;//szerokosc

    for (int i = 0; i < n; i++)
    {
        double fa = a + h * i;
        double fb = a + h * (i + 1);

        suma += (f0(fa, wspl, numer) + f0(fb, wspl, numer)) / 2 * h;
    }

    return suma;
}

double simpson(double a, double b, double n, double wspl[N + 1], int numer) {

    double h = (b - a) / n;

    double calka = 0;
    double s = 0;
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        s += f0(x - h / 2, wspl, numer);
        calka += f0(x, wspl, numer);
    }
    s += f0(b - h / 2, wspl, numer);
    calka = (h / 6) * (f0(a, wspl, numer) + f0(b, wspl, numer) + 2 * calka + 4 * s);
    return calka;
}

int main()
{
    fstream plik;
    double wspl[N + 1];
    double gp, gk;

    plik.open("dane.txt", ios::in);

    if (plik.good() == true)
    {
        for (int i = N; i >= 0; i--) {
            plik >> wspl[i];
        }
        for (int i = 0; i < 2; i++) {
            plik >> gp;
            plik >> gk;
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }
    //1: horner | 2: x^2cos^3
    int n = 10; //podzialy

    for (int i = 0; i < 5; i++) {
        cout << "dla n = " << n << endl;
        cout << "\ndla danych z pliku " << endl;
        cout << "met trapez: " << trapez(gp, gk, n, wspl, 1) << endl;
        cout << "met simsona: " << simpson(gp, gk, n, wspl, 1) << endl;
        cout << "\ndla podanej calki z pdf: " << endl;
        cout << "met trapez: " << trapez(2, 6, n, wspl, 2) << endl;
        cout << "met simsona: " << simpson(2, 6, n, wspl, 2) << endl;
        cout << "--------------------------" << endl;
        n = n * 10;
    }
    cout << "dla n = 1000, wyniki pokrywaja sie z wynikami z kalkulatora dla obu metod\n";
    return 0;
}