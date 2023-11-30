#include <iostream>
#include <cmath>
using namespace std;

double fun(double x, double y) {
    double w;
    double alfa = pow(10, -12);
    double beta = 0;
    w = (-1) * alfa * (pow(y, 4) - beta);
    return w;
}


void metEuler(double x0, double y, double h, double x, double(*f) (double, double))
{
    double temp = -0.;
    // Iterating till the point at which we need approximation
    while (x0 < x) {
        temp = y;
        y = y + h * f(x0, y);
        x0 = x0 + h;
    }
    cout << y << endl;
}




int main()
{

    double x0 = 0.;
    double y0 = 1200.;
    double h = 0.05;
    double x = 1.;
    cout << "dla h = 0,05" << endl;
    for (int i = 0; i < 300; i++) {
        cout << "w " << x << " s wartosc = ";
        metEuler(x0, y0, h, x, fun);
        x++;
    }


    double x1 = 1.;
    double h1 = 0.005;
    cout << endl << "dla h = 0,005" << endl;
    for (int i = 0; i < 300; i++) {
        cout << "w " << x1 << " s wartosc = ";
        metEuler(x0, y0, h1, x1, fun);
        x1++;
    }


    double x2 = 1.;
    double h2 = 0.001;
    cout << endl << "dla h = 0,001" << endl;

    for (int i = 0; i < 300; i++) {
        cout << "w " << x2 << " s wartosc = ";
        metEuler(x0, y0, h2, x2, fun);
        x2++;
    }
    return 0;
}
