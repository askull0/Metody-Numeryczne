#pragma once
#include <iostream>
using namespace std;
const double PI = 3.141592653589793238463;
const double eps = 1e-12;
#define N 5

int elim_przod(double mat[N][N + 1]);//do formy schodowej, czy macierz jednostkowa
void elim_tyl(double mat[N][N + 1]); //niewiadome

double f(double x) {

    double sinus = sin(x / 2);
    double w = exp(x) * sinus - pow(x, 3);

    return w;
}
double f1(double x) {

    double sinus = sin(x / 2);
    double w = x * (exp(x) * sinus - pow(x, 3));
    return w;
}
double f2(double x) {

    double sinus = sin(x / 2);
    double w = pow(x, 2) * (exp(x) * sinus - pow(x, 3));
    return w;
}
double f3(double x) {

    double sinus = sin(x / 2);
    double w = pow(x, 3) * (exp(x) * sinus - pow(x, 3));
    return w;
}
double f4(double x) {

    double sinus = sin(x / 2);
    double w = pow(x, 4) * (exp(x) * sinus - pow(x, 3));
    return w;
}

double fun0(double x) {
    double w = 1;
    return w;
}
double fun1(double x) {
    double w = x;
    return w;
}
double fun2(double x) {
    double w = pow(x, 2);
    return w;
}
double fun3(double x) {
    double w = pow(x, 3);
    return w;
}
double fun4(double x) {
    double w = pow(x, 4);
    return w;
}
double fun5(double x) {
    double w = pow(x, 5);
    return w;
}
double fun6(double x) {
    double w = pow(x, 6);
    return w;
}
double fun7(double x) {
    double w = pow(x, 7);
    return w;
}
double fun8(double x) {
    double w = pow(x, 8);
    return w;
}

double calka(double a, double b, int n, double(*f)(double)) {
    double result = 0.0;
    int R = n;
    double* w = new double[R]; //wagi
    double* x = new double[R]; //pkt

    switch (n) {
    case 1:
        x[0] = 0.0;
        w[0] = 2.;
        break;
    case 2:
        x[0] = -1. / sqrt(3);
        x[1] = 1. / sqrt(3);
        w[0] = w[1] = 1.0;
        break;
    case 3:
        x[0] = -(sqrt(3. / 5.));
        x[1] = 0.0;
        x[2] = sqrt(3. / 5.);
        w[0] = w[2] = 5.0 / 9.0;
        w[1] = 8.0 / 9.0;
        break;
    case 4:
        x[0] = -sqrt(3. / 7. + (2. / 7. * sqrt(6. / 5.)));
        x[1] = -sqrt(3. / 7. - (2. / 7. * sqrt(6. / 5.)));
        x[2] = sqrt(3. / 7. - (2. / 7. * sqrt(6. / 5.)));
        x[3] = sqrt(3. / 7. + (2. / 7. * sqrt(6. / 5.)));
        w[0] = w[3] = (18. - sqrt(30)) / 36.;
        w[1] = w[2] = (18. + sqrt(30)) / 36.;
        break;
    case 5:
        x[0] = -1 / 3 * sqrt(5. + 2. * sqrt(10 / 7));
        x[1] = -1 / 3 * sqrt(5. - 2. * sqrt(10 / 7));
        x[2] = -0.0;
        x[3] = 1 / 3 * sqrt(5 - 2 * sqrt(10 / 7));
        x[4] = 1 / 3 * sqrt(5 + 2 * sqrt(10 / 7));
        w[0] = w[4] = (322. - 13. * sqrt(70)) / 900;
        w[1] = w[3] = (322. + 13. * sqrt(70)) / 900;
        w[2] = 128. / 225.;
        break;
    default: return 0;
    }


    double alfa = (b - a) / 2.;
    double beta = (a * 1.0 - b * (-1.0)) / 2.;

    for (int i = 0; i < N; i++) {
        result += w[i] * f(alfa * x[i] + beta);
    }
    result *= alfa;

    delete[] w;
    delete[] x;
    return result;
}

double gauss_legendre(double a, double b, int n, double(*f)(double), int podzial) {
    double sum = 0.;
    double h = abs((a - b)) / podzial;
    for (int i = 0; i < podzial; i++) {
        sum += calka(a, a + h, n, f);
        a += h;
    }
    if (sum>-eps && sum<eps) {
        sum = 0.0;
    }
    return sum;
}

void gaussianElimination(double mat[N][N + 1])
{
    int singular_flag = elim_przod(mat); // do formy schodkowej

    if (singular_flag != -1) //czy jednostkowa
    {
        cout << "macierz jednostkowa" << endl;
        if (mat[singular_flag][N]) // if prawa strona row. to 0->nieksonczenie wiele rozw lub niespojny
            cout << "Niespojna " << endl;
        else
            cout << "Nieskonczenie wiele rozwiazan" << endl;
        return;
    }
    elim_tyl(mat);
}

void swap_row(double mat[N][N + 1], int i, int j)//zamiana rzedow
{
    // cout << "Zamiana wierszy " << i + 1 << " i " << j + 1 << ":" << endl;

    for (int k = 0; k <= N; k++)
    {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}

void wyswietl(double mat[N][N + 1])
{
    for (int i = 0; i < N; i++, cout << endl) {

        for (int j = 0; j <= N; j++)
        {
            cout <<setw(8) << setprecision(6) << mat[i][j] << "\t";
            if (j == N - 1)
                cout << "| ";
        }
    }
    cout << endl;
}

int elim_przod(double mat[N][N + 1])
{
    for (int k = 0; k < N; k++)
    {
        //Max wart i indeks dla przestawianego elementu (pivot)
        int i_max = k;
        double v_max = mat[i_max][k];

        for (int i = k + 1; i < N; i++)//if najwieksza amplituda dla obrotu
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        if (!mat[k][i_max])//if przektna = 0 -> macierz jednostkowa->dzielenie przez zero
            return k; // macierz jednostkowa

        if (i_max != k) //zmiana wiersza o najwiekszej wartosci z wierszem biezacym
            swap_row(mat, k, i_max);

        for (int i = k + 1; i < N; i++)
        {
            double f = mat[i][k] / mat[k][k];// wspol. f ustawic na k-ty elem biezacego wiersza na 0, pozniej pozstala k-ta kolumna do 0

            for (int j = k + 1; j <= N; j++)//odejmij f wielokrotnoœæ odpowiednich k - tych element wiersza
                mat[i][j] -= mat[k][j] * f;

            mat[i][k] = 0; //wypelnienie dolnej trojkatnej macierzy zerami
        }

        //    wyswietl(mat);
    }
    // wyswietl(mat);          
    return -1;
}

void elim_tyl(double mat[N][N + 1])
{
    double x[N];

    for (int i = N - 1; i >= 0; i--)// obliczenia od ostatniego równania do pierwszego
    {
        x[i] = mat[i][N]; //zacznij od praw.str.row
        for (int j = i + 1; j < N; j++)//zainicjuj j na i+1, bo macierz jest trojk. gornym 
        {

            x[i] -= mat[i][j] * x[j];//odejmij wart. lewej.str.row, oprocz wspol. zmiennej, ktorego wart. liczymy
        }
        x[i] = x[i] / mat[i][i];// podziel praw.str.row przez wspol. nieznany w trakcie obliczania
    }
    if (N == 5) {
        cout << endl << "Rozwiazania e^x * sin(x/2) - x^3 w przedziale [-1,1]:" << endl;
    }
    else {
        cout << endl << "Rozwiazania sin(x) w przedziale [-1,1]:" << endl;
    }
    for (int i = 0; i < N; i++)
        cout << "a(" << i << ")= " << x[i] << "  ";
    cout << endl;
}

double fs(double x) {
    double sinus = sin(x);
    return sinus;
}
double fsx(double x) {
    double sinus = sin(x);
    return sinus * x;
}
double fsxx(double x) {
    double sinus = sin(x);
    return sinus * x * x;
}