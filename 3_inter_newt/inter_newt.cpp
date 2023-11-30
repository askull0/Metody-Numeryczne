#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <cmath>
#define N 119     

using namespace std;

double post_natur(vector<double> wsp, int st, double x) {   
    double suma = wsp[0];
    for (int i = 1; i <= st; i++) {
       suma += pow(x, i)*wsp[i];   
    }
    return suma;
}
  
double horner(vector<double> wsp, int st, double x)//wartosc  w pkt x
{
    double wynik = wsp[st];

    for (int i = 1; i <= st; i++)
        wynik = wynik * x + wsp[st-i];

    return wynik;
}

void ilorazy(double x[], double y[][N], int n) //liczy ilorazy roznicowe
{
    for (int i = 1; i < n - 1; i++) {
        for (int j = 0; j < n - i; j++) {
            y[j][i] = (y[j][i - 1] - y[j + 1][i - 1]) / (x[j] - x[i + j]);

        }
    }
}
double pro(int i, double x, double xw[])// oblicza iloraz (x-x0)(x-x1)...
{
    double pro = 1;
    for (int j = 0; j < i; j++) {
        pro = pro * (x - xw[j]);
    }
    return pro;
}

double newton_interp(double value, double xw[], double iloraz[][N], int n)
{
    double wynik = iloraz[0][0];//y

    for (int i = 1; i < n; i++) {
        wynik = wynik + (pro(i, value, xw) * iloraz[0][i]);
    }
    return wynik;
}

void wyswietl_wspl(double y[][N], int n)
{
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "]= " << setprecision(5) << y[0][i] << endl;
    }
    cout << endl;
}

int main()
{
    vector<double>atab;
    vector<double>xtab;
    fstream hplik;
    string zm;

    clock_t start = 0;
    clock_t end = 0;


    hplik.open("inter_h.txt", ios::in);
    if (hplik.good() == true)
    {
        double pom = 0.0;
        while (!hplik.eof()) {
            hplik >> zm;
            if (!zm.find('a')) {
                pom = stod(zm.substr(3));
                atab.push_back(pom);
            }
            else if (!zm.find('x')) {}
            else {
                xtab.push_back(stod(zm));
            }
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }
    cout << "wspolczynniki a: " << endl;
    for (int i = 0; i < atab.size(); i++) {
        cout <<"a["<<i<<"]= " << atab[i] << setw(13);
    }
    cout <<endl<< "wartosci x: " << endl;
    for (int i = 0; i < xtab.size(); i++) {
        cout << "x[" << i << "]= " << xtab[i] << "\t\t ";
    }

    cout << endl << "----------------------------------------------------" << endl;
    
    cout << endl << "wyniki w.naturlny" << endl;
    for (int i = 0; i < xtab.size(); i++) {
        cout << " w(" << xtab[i] << ")= " << setprecision(15) << post_natur(atab, atab.size() - 1, xtab[i]) << endl;
    }

    start = clock();
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < xtab.size(); j++) {
            post_natur(atab, atab.size() - 1, xtab[j]);
        }
    }
    end = clock();
    double czas_n = double(end - start) / CLOCKS_PER_SEC;
    cout << "czas postac natur: " << setprecision(20) << czas_n << endl;
  
    cout <<endl<< "wyniki horner" << endl;
    for (int i = 0; i < xtab.size(); i++) {
        cout << " w(" << xtab[i] << ")= " << setprecision(15) << horner(atab, atab.size() - 1, xtab[i]) << endl; 
    }

    start = clock();
    for (int i = 0; i < 1000;i++) {
        for (int j = 0; j < xtab.size(); j++) {
            horner(atab, atab.size() - 1, xtab[j]);
        }
    }
    end = clock();
    double czas_h = double(end - start) / CLOCKS_PER_SEC;
    cout << "czas horner: " <<setprecision(20) << czas_h << endl;
    //dokladnosc
    cout << endl<<"roznica w obliczeniach: " << endl;
    for (int i = 0; i < xtab.size(); i++) {
        cout << setprecision(15) << fabs(horner(atab, atab.size() - 1, xtab[i])- post_natur(atab, atab.size() - 1, xtab[i]) )<< endl;
    }

    cout << endl << "------------------- czesc 2 ------------------------" << endl;
  
    double x_wart[N];
    double y_wart[N][N];

    fstream nplik_x, nplik_y;
    string zm1;

    nplik_x.open("nplik_x.txt", ios::in);
    nplik_y.open("nplik_y.txt", ios::in);
    if ((nplik_x.good() || nplik_y.good()) == true)
    {
        for (int i = 0; i < N; i++) {
            nplik_x >> x_wart[i];
        }
        for (int i = 0; i < N; i++) {
            nplik_y >> y_wart[i][0];
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }
/*
        //z pliku jakie x = y
        for (int i = 0; i <N; i++) {
            cout << "f[" << x_wart[i] << "]= " <<setprecision(12) << y_wart[i][0] << endl;
        }
 */
    ilorazy(x_wart, y_wart, N);
    wyswietl_wspl(y_wart, N);
/*
    for (int i = 0; i < N; i++) {
        cout << " dla x(" << x_wart[i] << ") = " << newton_interp(x_wart[i], x_wart, y_wart, N) << endl;

    }
*/
    double wartosc;
    cout << endl << "wprowadz wartosc - interpolacja newtona:  " ; cin >> wartosc;
    cout << newton_interp(wartosc, x_wart, y_wart, N)<<endl;

    return 0;
}