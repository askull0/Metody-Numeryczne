#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>

const unsigned int N = 5;//wymiar
using namespace std;
const double eps = 1e-12;

fstream plik;
//6 kolumna to wyrazy wolne b 

int elim_przod(double mat[N][N + 1]);//do formy schodowej, czy macierz jednostkowa
void elim_tyl(double mat[N][N + 1]); //niewiadome

void gaussianElimination(double mat[N][N + 1])
{
    int singular_flag = elim_przod(mat); // do formy schodkowej

    if (singular_flag != -1) //czy jednostkowa
    {
       cout<<"macierz jednostkowa"<<endl;
        if (mat[singular_flag][N]) // if prawa strona row. to 0->nieksonczenie wiele rozw lub niespojny
            cout<<"Niespojna "<<endl;
        else
           cout<<"Nieskonczenie wiele rozwiazan"<<endl;
        return;
    }
   elim_tyl(mat);
}

void swap_row(double mat[N][N + 1], int i, int j)//zamiana rzedow
{
    cout << "Zamiana wierszy " << i+1 << " i " << j+1 << ":"<<endl;

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
            cout << setprecision(4) << mat[i][j] << "\t";
            if (j == N-1)
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
        int v_max = mat[i_max][k];

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

            for (int j = k + 1; j <= N; j++)//odejmij f wielokrotność odpowiednich k - tych element wiersza
                mat[i][j] -= mat[k][j] * f;

            mat[i][k] = 0; //wypelnienie dolnej trojkatnej macierzy zerami
        }

      wyswietl(mat);       
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

    cout<<endl<<"Rozwiazania:"<<endl;
    for (int i = 0; i < N; i++)
        cout<<"x("<<i+1<<")= " << x[i]<< "  ";
}

int main()
{
    fstream plik;
    string linia, tmp;
 
    double tab_a[N][N+1];
    double tab_b[N][N+1];
    double tab_c[N][N+1];

    plik.open("gauss.txt", ios::in);
    if (plik.good() == true)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N+1; j++) {
                plik >> tab_a[i][j];
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N+1; j++) {
                plik >> tab_b[i][j];
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N+1; j++) {
                plik >> tab_c[i][j];
            }
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }

    cout << "MACIERZ A" << endl;
    wyswietl(tab_a);
    gaussianElimination(tab_a); cout << endl;
    cout << "-------------------------------------------------------------------------------"<<endl<<endl;
    cout << "MACIERZ B" << endl;
    wyswietl(tab_b); 
    gaussianElimination(tab_b); cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl<<endl;
    cout << "MACIERZ C" << endl;
    wyswietl(tab_c); 
    gaussianElimination(tab_c); cout << endl;
 
    plik.close();
    return 0;
}
