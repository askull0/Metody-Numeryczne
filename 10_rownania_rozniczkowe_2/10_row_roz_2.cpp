#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double fun(double x, double y) {
    double beta = 0;
    double alfa = pow(10, -12);
    double w = (-1) * alfa * (pow(y, 4) - beta);
    return w;
}

//--------------------------------------------------------------------------
// predicts the next value for a given (x, y) and step size h using Euler method
double przewidywana(double x, double y, double h, double(*f) (double, double))
{
    // value of next y(predicted) is returned
    double y1p = y + h * f(x, y);
    return y1p;
}
// corrects the predicted value using Modified Euler method
double correct(double x, double y, double x1, double y1, double h, double(*f) (double, double))
{
    // (x, y) are of previous step and x1 is the increased x for next step and y1 is predicted y for next step
    double e = 0.00001;
    double y1c = y1;

    do {
        y1 = y1c;
        y1c = y + 0.5 * h * (f(x, y) + f(x1, y1));
    } while (fabs(y1c - y1) > e);

    // every iteration is correcting the value of y using average slope
    return y1c;
}

void metMiddle(double x, double xn, double y, double h, double(*f) (double, double))
{

    while (x < xn) {
        double x1 = x + h;
        double y1p = przewidywana(x, y, h, f);
        double y1c = correct(x, y, x1, y1p, h, f);
        x = x1;
        y = y1c;
    }

    // at every iteration first the value of for next step is first predicted and then corrected.
 //   cout << "met pkt srodkowe - wartosc y( " << x << ") = " << y << endl;
    cout << y;

}
//--------------------------4rzedu
void rungeKutta4(double x0, double y0, double x, double h, double(*f) (double, double))
{
    // Count number of iterations using step size or step height h
    int n = (int)((x - x0) / h);

    double k1, k2, k3, k4, k5;

    // Iterate for number of iterations
    double y = y0;
    for (int i = 1; i <= n; i++)
    {
        // Apply Runge Kutta Formulas to find next value of y
        k1 = h * f(x0, y);
        k2 = h * f(x0 + 0.5 * h, y + 0.5 * k1);
        k3 = h * f(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * f(x0 + h, y + k3);

        // Update next value of y
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);;

        // Update next value of x
        x0 = x0 + h;
    }
    //  cout << "met runge kutaa 4 - wartosc y( " << x << ") = " << y << endl;
    cout << y;
    // return y;
}


void heun(double y, double x0, double h, double x, double(*f) (double, double)) {
    double Tn, dT1, dT2;
    while (x0 <= x) {
        dT1 = f(x0, y);
        Tn = y + h * dT1;
        dT2 = f(Tn, y);
        y += h / 2.0 * (dT1 + dT2);
        x0 += h;
    }
    cout << y;
}


int main()
{

    double x0 = 0.;
    double y0 = 1200.;
    double h = 0.05;
    double x = 1.;

    cout << "dla h = 0,05" << endl;
    for (int i = 0; i < 300; i++) {
        cout << "w " << x << " s wartosc dla  " << endl;
        cout << "met heun   | met srodk   |  met runge kutta " << endl;
        heun(y0, x0, h, x, fun); cout << " ";
        cout << "    |" << setw(12); metMiddle(x0, x, y0, h, fun);
        cout << " |" << setw(12); rungeKutta4(x0, y0, x, h, fun);
        cout << endl << endl;
        x++;
    }

    double x01 = 0.;
    double y01 = 1200.;
    double h1 = 0.001;
    double x1 = 1.;

    cout << "dla h = 0,001" << endl;
    for (int i = 0; i < 300; i++) {
        cout << "w " << x1 << " s wartosc dla  " << endl;
        cout << "met heun   | met srodk   |  met runge kutta " << endl;
        heun(y01, x01, h1, x1, fun); cout << " ";
        cout << "    |" << setw(12); metMiddle(x01, x1, y01, h1, fun);
        cout << " |" << setw(12); rungeKutta4(x01, y01, x1, h1, fun);
        cout << endl << endl;
        x1++;
    }

    return 0;
}
