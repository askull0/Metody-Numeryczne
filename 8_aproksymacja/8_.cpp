#include <iostream>
#include <cmath>
#include <iomanip>
#include "biblioteka.h"
using namespace std;


int main()
{
    int n = 4;//wezly kwadratury
    int ile = 1000;//podzialy
    double wyn_a[N][N + 1];
    double wyn_b[N];

    wyn_a[0][0] = gauss_legendre(-1, 1, n, fun0, ile);

    wyn_a[0][1] = wyn_a[1][0] = gauss_legendre(-1, 1, n, fun1, ile);//0

    wyn_a[0][2] = wyn_a[2][0] = wyn_a[1][1]= gauss_legendre(-1, 1, n, fun2, ile);

    wyn_a[0][3] = wyn_a[2][1] = wyn_a[1][2] = wyn_a[3][0] = gauss_legendre(-1, 1, n, fun3, ile);//0

    wyn_a[0][4] = wyn_a[4][0] = wyn_a[3][1] = wyn_a[2][2] = wyn_a[1][3] = gauss_legendre(-1, 1, n, fun4, ile);

    wyn_a[1][4] = wyn_a[4][1] = wyn_a[3][2] = wyn_a[2][3] = gauss_legendre(-1, 1, n, fun5, ile);//0

    wyn_a[2][4] = wyn_a[4][2] = wyn_a[3][3] = gauss_legendre(-1, 1, n, fun6, ile);

    wyn_a[3][4] = wyn_a[4][3] = gauss_legendre(-1, 1, n, fun7, ile);//0

    wyn_a[4][4] = gauss_legendre(-1, 1, n, fun8, ile);
    
    wyn_b[0] = gauss_legendre(-1, 1, n, f, ile);
    wyn_b[1] = gauss_legendre(-1, 1, n, f1, ile);
    wyn_b[2] = gauss_legendre(-1, 1, n, f2, ile);
    wyn_b[3] = gauss_legendre(-1, 1, n, f3, ile);
    wyn_b[4] = gauss_legendre(-1, 1, n, f4, ile);
    
    for (int i = 0; i < N; i++)
    {
        wyn_a[i][N] = wyn_b[i];
    }

    wyswietl(wyn_a);    gaussianElimination(wyn_a);
    /*     //sinus - zmien romzair 
    cout << endl;
    wyn_a[0][0] = gauss_legendre(0, PI / 2, n, fun0, ile);
    wyn_a[0][1] = gauss_legendre(0, PI / 2, n, fun1, ile);
    wyn_a[1][0] = gauss_legendre(0, PI / 2, n, fun1, ile);

    wyn_a[0][2] = gauss_legendre(0, PI / 2, n, fun2, ile);
    wyn_a[1][1] = gauss_legendre(0, PI / 2, n, fun2, ile);
    wyn_a[2][0] = gauss_legendre(0, PI / 2, n, fun2, ile);

    wyn_a[1][2] = gauss_legendre(0, PI / 2, n, fun3, ile);
    wyn_a[2][1] = gauss_legendre(0, PI / 2, n, fun3, ile);

    wyn_a[2][2] = gauss_legendre(0, PI / 2, n, fun4, ile);


    cout << endl;
    wyn_b[0] = gauss_legendre(0, PI / 2, n, fs, ile);
    wyn_b[1] = gauss_legendre(0, PI / 2, n, fsx, ile);
    wyn_b[2] = gauss_legendre(0, PI / 2, n, fsxx, ile);

      for (int i = 0; i < N; i++)
    {
        wyn_a[i][N] = wyn_b[i];
    }

    wyswietl(wyn_a);    gaussianElimination(wyn_a);
    */
    return 0;
}

//szukamy a0, a1...
//Ax=b wyliczmay z stworzonej macierzy z calek gdzie b to tez wyliczone calki
//^ to z ukladu rownan
