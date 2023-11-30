#include <iostream>
#include <iomanip>
#include <fstream>
const int N = 5;
using namespace std;
const double eps = 1e-12;

void wyswietl(double mat[N][N]);
void wyswietl_wspl(double mat[N][N + 1]);

void luDecomposition(double mat[N][N+1], double lower[N][N], double upper[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int k = i; k < N; k++)// Upper Triangular
        {
            if (k > i) { lower[i][k] = 0; }
            // Summation of L(i, j) * U(j, k)
            double sum = 0.;
            for (int j = 0; j < i; j++) {
                sum += (lower[i][j] * upper[j][k]);
            }
           upper[i][k] = mat[i][k] - sum;  // Evaluating U(i, k)
        }
        for (int k = i; k < N; k++)// Lower Triangular
        {
            if (i == k) lower[i][i] = 1; // Diagonal as 1
            else
            {
                // Summation of L(k, j) * U(j, i)
                double sum = 0.;
                for (int j = 0; j < i; j++) {
                    sum += (lower[k][j] * upper[j][i]);
                }
                lower[k][i]= (mat[k][i] - sum) / upper[i][i];// Evaluating L(k, i)
            }
        }
        for (int j = 0; j < N; j++) {
            if (i > j) {
                upper[i][j] = 0;
            }
        }
    }
}
/*
void swap_row(double mat[N][N + 1], int i, int j)//zamiana rzedow
{

    for (i; i < j;i++) {
        cout << "Zamiana wierszy " << i + 1 << " i " << j + 1 << ":" << endl;
        for (int k = 0; k <= N; k++)
        {
            double temp = mat[i][k];
            mat[i][k] = mat[j][k];
            mat[j][k] = temp;
        }
        j--;
        wyswietl_wspl(mat); cout << endl;
    }

}
void swap_col(double mat[N][N + 1], int i, int j)
{
    for (i; i < j; i++) {
     cout << "Zamiana kolumn " << i + 1 << " i " << j + 1 << ":" << endl;
        for (int k = 0; k < N; k++)
        {
            double temp = mat[k][i];
            mat[k][i] = mat[k][j];
            mat[k][j] = temp;
        }
        j--;
        wyswietl_wspl(mat); cout << endl;
    }
}
*/

void elim_tyl(double mat[N][N + 1],double x[])
{
    for (int i = N - 1; i >= 0; i--)// obliczenia od ostatniego równania do pierwszego
    {
        double sum = 0.;
        x[i] = mat[i][N]; //zacznij od praw.str.row
        if (i != 4) {
            cout << "suma = (";
        }
        for (int j = i + 1; j < N; j++)//zainicjuj j na i+1, bo macierz jest trojk. gornym 
        {
          cout <<"(" << mat[i][j] << ") * (" << x[j] << ")";
           
            sum += mat[i][j] * x[j];
            if (N - 1 == j) {
                cout << " = " << sum;
            }
            else { cout << " + "; }
            x[i] -= mat[i][j] * x[j];//odejmij wart. lewej.str.row, oprocz wspol. zmiennej, ktorego wart. liczymy
        }
        x[i] = x[i] / mat[i][i];// podziel praw.str.row przez wspol. nieznany w trakcie obliczania
        cout << endl << "Niewiadoma x[" << i + 1 << "]  = (";
        if (i == 4) {
            cout << "(" << mat[i][N] << ") / (" << mat[i][i] << ") = " << x[i] << endl << endl;
        }
        else {
            cout << "(" << mat[i][N] << ") - (" << sum << ")) / (" << mat[i][i] << ") = " << x[i] << endl << endl;
        }
    }
    cout << endl;
   // cout << endl << "Rozwiazania:" << endl;
    for (int i = 0; i < N; i++)
        cout << "x(" << i + 1 << ")= " << x[i] << "  ";
}

void elim_przod(double A[][N], double B[N], double x[N]) {

    x[0] = B[0];
    cout << "Niewiadoma x[1]  = ";
    cout << x[0]<<" / 1 = "<<x[0]<<endl<<endl;
    // od pierwszego do ostatniego
    for (int i = 1; i < N; i++)
    {
        double suma = 0;
        // wspolczynniki macierzy B
        for (int j = 0; j < i; j++)
        {
            cout << "suma = (" << A[i][j] << ") * (" << x[j] << ")";
            suma += A[i][j] * x[j];
            if (i == 1) {
                cout << " = " << suma;
            }
            else if (j  == i - 1) {
                cout << " = " << suma;
            }
            else {
                cout << " + " ;
            }
        }
        cout<<endl << "Niewiadoma x[" << i+1 << "]  = ";
        cout <<"( " << B[i] << " - (" << suma << ")) / 1 = ";
        x[i] = B[i] - suma;
        cout << x[i] << endl<<endl;
       // wyswietl_wspl(A);
    }

    // cout << endl << "Rozwiazania:" << endl;
    for (int i = 0; i < N; i++)
        cout << "x(" << i + 1 << ")= " << x[i] << "  ";
}


void mnozenie(double mats[N][N], double mat1[N][N], double mat2[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            double s = 0;
            for (int k = 0; k < N; k++) s += mat1[i][k] * mat2[k][j];
            mats[i][j] = s;
        }
}
void mnozenie_wek(double mats[N], double mat1[N][N+1], double wek[N]) {
    for (int i = 0; i < N; i++)
    {   
        double s = 0;
        for (int j = 0; j < N; j++)
        {
          s += mat1[i][j] * wek[j];
          mats[i] = s;
        }
    }
}
void wyswietl(double mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(12) << mat[i][j];
        }
        cout << endl;
    }
}

void wyswietl_wspl(double mat[N][N+1]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << setw(12) << mat[i][j];
            if (j == N - 1) { cout << " | "; }
        }
        cout << endl;
    }
}

int main()
{
    fstream plik;
    double mat_a[N][N+1], mat_l[N][N], mat_u[N][N];

    plik.open("mat1.txt", ios::in); //mat1 dobyr plik
    if (plik.good() == true)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N+1; j++) { 
                plik >> mat_a[i][j];
            }
        }
    }
    else {
        cout << "brak pliku" << endl;
        exit(0);
    }
    cout <<"maierz A" << endl; 
    wyswietl_wspl(mat_a); cout << endl;
   
    luDecomposition(mat_a,mat_l,mat_u);
    cout << "macierz L " << endl; wyswietl(mat_l);
    cout << endl << "macierz U" << endl; wyswietl(mat_u);

    cout << endl << "------------------------------------------------------------------------------" << endl;
  double mat_spr[N][N];
      mnozenie(mat_spr,mat_l,mat_u);
      cout << "Sprawdzenie czy macierz L*U = A " << endl; wyswietl(mat_spr);
      cout << endl << "-----------------------------------------------------------------------------" << endl;
  
      //przypisanie wspl-b z mat_a (6 kol)
  double mat_lb[N][N+1], mat_uz[N][N+1];
      for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
          mat_lb[i][j] = mat_l[i][j];
          mat_uz[i][j] = mat_u[i][j];
          }
      }
      double b[N];
      for (int i = 0; i < N; i++) {
          b[i] = mat_a[i][N];//1 mat_lb[i][N] = mat_a[i][N];
          mat_lb[i][N] = b[i];
      }
    
     cout << "Maceirz L z wspl B" << endl; wyswietl_wspl(mat_lb); cout << endl;
  //   cout << endl << "----    ----    ----    ----    ----    ----    ----    ----    ----    ----" << endl;
//1 swap_row(mat_lb,0,4); swap_col(mat_lb,0,4);
  //   cout << endl << "----    ----    ----    ----    ----    ----    ----    ----    ----    ----" << endl;
     
     //rozwiazania z[]
     double z[N];
//1 cout <<endl <<"rozwiazania z[]: (Lz=b)" << endl; elim_tyl(mat_lb, z); cout << endl;
    elim_przod(mat_l,b, z);
/*1
     double temp;
     for (int i = 0; i < N / 2; i++) {
        temp = z[N - i - 1];
        z[N - i - 1] = z[i];
        z[i] = temp;
      }
1*/
     //przypisanie z[] do mat_uz
      for (int i = 0; i < N; i++) {
        mat_uz[i][N] = z[i];
      }
     cout << endl << "-----------------------------------------------------------------------------" << endl;
     double x[N];
     cout << "Macierz U z rozw z " << endl;
     wyswietl_wspl(mat_uz); cout << endl;
      //rozwiazania x[]
     cout << endl << "rozwiazania x[]: (Ux=z)" << endl; elim_tyl(mat_uz, x); cout << endl;
      cout << endl << "------------------------------------------------------------------------------" << endl;
     
      double wynik_b[N];
      mnozenie_wek(wynik_b,mat_a,x);
      cout <<endl<< "Sprawdzenie czy macierz A*x = b; Rozwiazania b: " << endl;
      for (int i = 0; i < N; i++) {
          cout<<wynik_b[i]<<"   ";
      }
      cout << endl;

       return 0;

}