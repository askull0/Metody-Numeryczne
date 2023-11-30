#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<iomanip>

const unsigned int N = 5;
using namespace std;
const double eps = 1e-12; // stała przybliżenia zera

fstream plik;
//6 kolumna to wyrazy wolne b 

void Gauss(double** a, double* x, double* b, int n)
//a - dwawymair tab wspol, x- niewiadome,b -wolne, n- romzair
{
    for (int k = 0; k < n - 1; k++)//eliminacja a
    {
        for (int i = k + 1; i < n; i++)
        {
            a[i][k] /= a[k][k];
            for (int j = k + 1; j < n + 1; j++)
            {
                if (j == n)
                    b[i] -= a[i][k] * b[k];
                else a[i][j] -= a[i][k] * a[k][j];
            }
            a[i][k] = 0;
        }
    }
    for (int i = n - 1; i >= 0; i--)//niewiadome
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
        {
            if (j == n)
                x[i] -= b[i] * x[j];
            else x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}


int main()
{
    fstream plik;
    string linia, tmp;
   
    double** tab_a = new double* [N];
    for (int i = 0; i < N + 1; i++)
        tab_a[i] = new double[N + 1];

    double** tab_b = new double* [N];
    for (int i = 0; i < N + 1; i++)
        tab_b[i] = new double[N + 1];

    double** tab_c = new double* [N];
    for (int i = 0; i < N + 1; i++)
        tab_c[i] = new double[N + 1];

    double* b_1 = new double[N]; double* b_2 = new double[N]; double* b_3 = new double[N];

    double* tab_x1 = new double[N]; double* tab_x2 = new double[N]; double* tab_x3 = new double[N];

    plik.open("gauss.txt", ios::in);
    if (plik.good() == true)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                plik >> tab_a[i][j];
            }
            plik >> b_1[i];
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                plik >> tab_b[i][j];
            }
            plik >> b_2[i];
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                plik >> tab_c[i][j];
            }
            plik >> b_3[i];
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }
    
    for(int i=0; i<N;i++){
        cout<<b_1[i]<<" ";
      //  cout<<b_2[i]<<" ";
      //  cout<<b_3[i]<<" ";
    }
    cout << endl;
    
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << setw(6) << tab_a[i][j];
           // cout << setw(6) << tab_b[i][j];
           // cout << setw(6) << tab_c[i][j];
        }
        cout << endl;
    }
   
    Gauss(tab_a,tab_x1,b_1,N);
    for (int i = 0; i < N; i++)
        cout <<"x("<<i<<")= " << tab_x1[i] << " ";
    cout << endl;
   /* Gauss(tab_b, tab_x2, b_2, N);
    for (int i = 0; i < N; i++)
        cout << "x(" << i << ")= " << tab_x2[i] << " ";
    cout << endl;
    Gauss(tab_c, tab_x3, b_3, N);
    for (int i = 0; i < N; i++)
        cout << "x(" << i << ")= " << tab_x3[i] << " ";
    cout << endl;
    */
    plik.close();
   return 0;
}

/*
for (k = 1; k < n; k++) {
    int i, j;
    double r, w;
    // Normalizacja elementów macierzowych
    for (i = k; i <= n; i++) {
        r = fabs(a[i][k]);
        for (j = k + 1; j <= n; j++) {
            w = fabs(a[i][j]);
            if (w > r)
                r = w;
        }
        if (r == 0)
            throw "Dzielenie przez zero";
        b[i] /= r;
        for (j = k; j <= n; j++)
            a[i][j] /= r;
    }
    // Wybór dzielnika o największym module
    r = fabs(a[k][k]);
    i = k;
    for (j = k + 1; j <= n; j++) {
        w = fabs(a[j][k]);
        if (w > r) {
            r = w;
            i = j;
        }
    }
    if (i > k) {
        zamiana_wierszy(a[k], a[i]);
        zamiana(b[k], b[i]);
    }
    if (a[k][k] == 0)
        throw "Dzielenie przez zero";
    // Eliminacja
    for (i = k + 1; i <= n; i++) {
        r = a[i][k] / a[k][k];
        b[i] -= r * b[k];
        for (j = k; j <= n; j++)
            a[i][j] -= r * a[k][j];
    }
}
*/

