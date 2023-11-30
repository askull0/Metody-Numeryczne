#include <iostream>
#include <iomanip>

const double E = 1.0E-13;

using namespace std;

double fn1(double x)
{
    return pow(x, 2) - 2;
}
double pochfn1(double x)
{
    return  2 * x;
}

double fn2(double x)
{
    return pow(x, 3) + pow(x, 2) - 3 * x - 3;
}
double pochfn2(double x)
{
    return  3 * pow(x, 2) + 2 * x - 3;
}

double fn3(double x)
{
    double sinus = sin(pow(x, 2));
    return  sinus - pow(x, 2);
}
double pochfn3(double x)
{
    double cosinus = cos(pow(x, 2));
    return  2 * x * cosinus - 2 * x;
}

double fn4(double x)
{
    double sinus = sin(pow(x, 2));
    return  sinus - pow(x, 2) + 1. / 2.;
}
double pochfn4(double x)
{
    double cosinus = cos(pow(x, 2));
    return  2 * x * cosinus - 2 * x;
}

//------------------------------------
void newton(double x1, double x2,double e, double(*f) (double), double(*pf)(double)) //analitycznie
{
    double h = f(x1) / pf(x1);
    double n = 0, n1=0;
    while (abs(h) >=e)
    {
        h = f(x1) / pf(x1); // x(i+1) = x(i) - f(x) / f'(x) 
        x1 = x1 - h;
    }
    cout << "x0 = "<< x1;
    double w = 0;
    for (int i = x1; i < x2; i++) {
        w = f(i);
        if (w == 0) {
            cout << setw(10) << "x0 = " << i;
        }
    }
    double h2 = f(x2) / pf(x2);
    while (abs(h2) >= e)
    {
        h2 = f(x2) / pf(x2);  // x(i+1) = x(i) - f(x) / f'(x) 
        x2 = x2 - h2;
    }
    cout << setw(10) << "x0 = " << x2;

}

double sieczna(double a, double b, double e, double(*f) (double))
{
    double x0 = a, x1 = b;
    double xn = 0, n = 0;
    for (int i = 0; i < 100; i++) {
       xn = x0 - f(x0) * ((x1 - x0) / (f(x1) - f(x0)));
        if (fabs(xn - x1) <= E) {
         //   n++;
         //   cout << n << " krok " << xn << endl;
            return xn;
        }
        x0 = x1;
        x1 = xn;
    }

}
double siecznad(double a, double b, double e, double(*f) (double))
{
    double x0 = a, x1 = b;
    double xn = 0,n=0;
   for (int i = -5; i < 5; i++) {
        double w = f(i);
        if (w == 0) {
            cout << setw(10) << "x0 = " << i << setw(10);
        }
    }
    for (int i = 0; i < 10; i++) {
        xn = x0 - f(x0) * ((x1 - x0) / (f(x1) - f(x0)));
        if (fabs(xn - x1) <= E) {
            return xn;
        }
    }

}

//podochna z definicji
double poch_def(double x0, double(*f) (double)) {
    double h = 0.0001; 
    double n_wyn, wyn = (f(x0 + h) - f(x0)) / h;
    do {
        h /= 100.; //h->0
        n_wyn = wyn;
        wyn= (f(x0 + h) - f(x0)) / h;
    } while (fabs(wyn - n_wyn) <= E);
       // (n_wyn<=E && n_wyn>-E);
        return n_wyn;
}
void newton_def(double x1, double x2, double e, double(*f) (double))
{
    double h = f(x1) / poch_def(x1,f);
    while (abs(h) >= e)
    {
        h = f(x1) / poch_def(x1, f); //f(x) / f'(x) 
        x1 = x1 - h; // x(i+1) = x(i) - f(x) / f'(x) 
    }
    cout << "x0 = " << x1;
    double w = 0;
    for (int i = x1; i < x2; i++) {
        w = f(i);
        if (w == 0) { cout << setw(10) << "x0 = " << i; }
    }
    double h2 = f(x2) / poch_def(x2, f);
    while (abs(h2) >= e)
    {
        h2 = f(x2) / poch_def(x2, f);  //f(x) / f'(x) 
        x2 = x2 - h2; // x(i+1) = x(i) - f(x) / f'(x) 
    }
    cout << setw(10) << "x0 = " << x2;
}

//-------------------------
void tabnewton(double x1, double x2, double e, double(*f) (double), double(*pf)(double)) //analitycznie
{
    double h = f(x1) / pf(x1);
    double n = 0, n1 = 0;
    while (abs(h) >= e)
    {
        h = f(x1) / pf(x1); // x(i+1) = x(i) - f(x) / f'(x) 
        x1 = x1 - h;
        n++;
        cout <<n<<" | " << x1 << endl;
    }
    double h2 = f(x2) / pf(x2);
    cout << endl;
    while (abs(h2) >= e)
    {
        h2 = f(x2) / pf(x2);  // x(i+1) = x(i) - f(x) / f'(x) 
        x2 = x2 - h2;
        n1++;
        cout << n1 << " | " << x2 << endl;
    }
}
int main()
{   
    cout << endl << "//met newton analitycznie//" << endl;
    double x01 = -3, x02 = 3;
    double x31 = 0., x32 = 2.;
    cout << "rownanie 1:"<<endl;
    newton(x01,x02, E, fn1, pochfn1); cout << endl; 
    cout << "rownanie 2: " << endl;
    newton(x01,x02, E, fn2, pochfn2); cout << endl;
    cout << "rownanie 3: " << endl;
    newton(x31, x32, E, fn3, pochfn3); cout << endl;
    cout << "rownanie 4: " << endl;
    newton(x01, x02, E, fn4, pochfn4); cout << endl;

    cout << endl << "//met newton numerycznie//" << endl;
    cout << "rownanie 1:" << endl;
    newton_def(x01, x02, E, fn1); cout << endl;
    cout << "rownanie 2: " << endl;
    newton_def(x01, x02, E, fn2); cout << endl;
    cout << "rownanie 3: " << endl;
    newton_def(x31, x32, E, fn3); cout << endl;
    cout << "rownanie 4: " << endl;
    newton_def(x01, x02, E, fn4); cout << endl;

    cout << endl << "\n//met siecznych// " << endl;
    double xs1 = 3, xs2 = -2;

    cout << "rownanie 1: \n"; cout << "x0 = "<<sieczna(xs1, xs2, E, fn1);
     cout << setw(10) << "x0 = "<<siecznad(-3,2, E, fn1) << endl;
    cout << "rownanie 2: \n"; cout << "x0 = " << sieczna(xs1, xs2, E, fn2);  
     cout << setw(10) << "x0 = " << siecznad(-3, 2, E, fn2)<<endl;  
    cout << "rownanie 3: \n"; cout << "x0 = " << sieczna(1,-4, E, fn3);
    cout << setw(10) << "x0 = " << siecznad(0,10, E, fn3)<<endl;
    cout << "rownanie 4: \n"; cout << "x0 = " << sieczna(xs1, xs2, E, fn4); 
     cout <<setw(10) << "x0 = " << siecznad(-3, 2, E, fn4) << endl;

  
   cout <<endl<< "zestawienie przykladowych wynikow do tabel" << endl;
   cout << "dla rownnaia 1 \n"; tabnewton(x01, x02, E, fn1, pochfn1);    cout << endl;
   cout << "dla rownnaia 4 \n"; tabnewton(x01, x02, E, fn4, pochfn4);
    
    return 0;
}