#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x) {
	double sinus = sin(x);
	double wynik = x * x * sinus * sinus * sinus;
	return wynik;
}

double f1(double x) {
	double wynik = exp(x * x) * (1 - x);
	return wynik;
}


double calka(double a, double b, int n, double(*f)(double)) {
    double result = 0.0;
    int N = n;
    double* w = new double[N]; //wagi
    double* x = new double[N]; //pkt

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
        x[0] = -(sqrt(3./5.));
        x[1] = 0.0;
        x[2] = sqrt(3./5.);
        w[0] = w[2] = 5.0 / 9.0;
        w[1] = 8.0 / 9.0;
        break;
    case 4:
        x[0] = -sqrt(3. / 7. + (2. / 7. * sqrt(6. / 5.)));
        x[1] = -sqrt(3. / 7. - (2. / 7. * sqrt(6. / 5.)));
        x[2] = sqrt(3. / 7. - (2. / 7. * sqrt(6. / 5.)));
        x[3] = sqrt(3. / 7. + (2. / 7. * sqrt(6. / 5.)));
        w[0] = w[3] = (18.-sqrt(30))/36.;
        w[1] = w[2] = (18. + sqrt(30)) / 36.;
        break;
    case 5:
        x[0] = -1 / 3 * sqrt(5 + 2 * sqrt(10. / 7.));
        x[1] = -1/3*sqrt(5 - 2 * sqrt(10. / 7.));
        x[2] = -0.0;
        x[3] = 1 / 3 * sqrt(5 - 2 * sqrt(10. / 7.));
        x[4] = 1 / 3 * sqrt(5 + 2 * sqrt(10. / 7.));
        w[0] = w[4] = (322 - 13 * sqrt(70)) / 900;
        w[1] = w[3] = (322 + 13 * sqrt(70)) / 900;
        w[2] = 128./225.;
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
    return sum;
}

int main()
{
    
    int n = 2; //wezly kwadratury
    for (int i = 0; i < 3; i++) {
        int ile = 10; //ilosc podziałow
        for (int j = 0; j < 3; j++) {
            cout << "obliczenia za pomoca " << n << " wezlow kwadratury GL, przy podziale na " << ile << endl;
            cout << setprecision(8) << gauss_legendre(1, 4.8, n, f, ile) << endl;
            cout << setprecision(8)<< gauss_legendre(-1.5, 3.2, n, f1, ile) << endl;
            
            ile = ile * 10;
        }
        cout << "\n---------------------------------------------------------------------\n";
        n++;
    }
    return 0;
}