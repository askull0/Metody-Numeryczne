#include <iostream>
#include <iomanip>
#include <cmath>

const double E = 1.0E-8;

using namespace std;

double fn1(double x)
{
	double sinus = sin(x);
	return  4 * x + sinus - exp(x);
}
double fn2(double x)
{
	return  3 * pow(x, 4) - 6 * pow(x, 2) + x + 2;
}
double fn3(double x)
{
	return  pow(x, 2) - 3 * x * sin(x) + (3 * sin(x)) * (3 * sin(x)) - 6;
}
//-----------

void bisection(double (*f)(double), double a, double b)
{
	if (f(a) * f(b) >= 0)
	{
		cout << "   zly dobor a i b   ";
		return;
	}
	
	double xm = a;
		while ((b - a) >= E)
		{
			xm = (a + b) / 2;

			if (f(xm) == 0.0)
				break;
			else if (f(xm) * f(a) < 0)
				b = xm;
			else
				a = xm;
		}
		cout << "x0 = " << xm;
}


void fals(double (*f)(double), double a, double b) {
	double fa = f(a), fb = f(b), x1 = a, x0 = b, f0;
	if (f(a) * f(b) > 0) cout << "   zly dobor a i b   ";
	else
	{
		while (fabs(x1 - x0) > E)
		{
			x1 = x0;
			x0 = a - fa * (b - a) / (fb - fa);
			f0 = f(x0);
			if (fabs(f0) < E) break;
			if (fa * f0 < 0)
			{
				b = x0; fb = f0;
			}
			else
			{
				a = x0; fa = f0;
			}
		}
		cout << "x0 = " << x0;
	}
}
//----------
void bis_iter(double (*f)(double), double a, double b)
{
	int i = 0;
	if (f(a) * f(b) >= 0)
	{
		cout << "   zly dobor a i b   ";
		return;
	}

	double xm = a;
	while ((b - a) >= E)
	{
		xm = (a + b) / 2;

		if (f(xm) == 0.0)
			break;
		else if (f(xm) * f(a) < 0)
			b = xm;
		else
			a = xm;
		cout << "iteracja " << i << " = " << xm<<endl;
		i++;
	}
}

void fals_iter(double (*f)(double), double a, double b) {
	double fa = f(a), fb = f(b), x1 = a, x0 = b, f0;
	int i = 0;
	if (f(a) * f(b) > 0) cout << "   zly dobor a i b   ";
	else
	{
		while (fabs(x1 - x0) > E)
		{
			x1 = x0;
			x0 = a - fa * (b - a) / (fb - fa);
			f0 = f(x0);
			if (fabs(f0) < E) break;
			if (fa * f0 < 0)
			{
				b = x0; fb = f0;
			}
			else
			{
				a = x0; fa = f0;
			}
			cout << "iteracja " << i << " = " << x0 << endl;
			i++;
		}
	}
}
 int main()
 {

	 cout << "rownanie 1\n";
	 cout << "bisekcja: \n"; 
	 bisection(fn1, -1, 2); cout << setw(10);
	 bisection(fn1, 1, 4);

	 cout << "\nregula falsi: \n";
	 fals(fn1, -1, 2); cout << setw(10); 
	 fals(fn1, 1, 4);

	 cout << "\n\nrownanie 2\n";
	 cout << "bisekcja: \n";
	 bisection(fn2, -2,-1); cout << setw(10);
	 bisection(fn2, -1, 0); cout << setw(10);
	 bisection(fn2, 0.5, 0.99); cout << setw(10);
	 bisection(fn2, 0.99, 2);

	 cout << "\nregula falsi: \n"; 
	 fals(fn2, -2, -1); cout << setw(10);
	 fals(fn2, -1, 0); cout << setw(10);
	 fals(fn2, 0.5, 0.99); cout << setw(10);
	 fals(fn2,1, 2);


	 cout << "\n\nrownanie 3\n";
	 cout << "bisekcja: \n"; 
	 bisection(fn3, -3, -2.5); cout << setw(10);
	 bisection(fn3, -2.5, -1.5); cout << setw(10);
	 bisection(fn3, -1.5, -1); cout << setw(10);
	 bisection(fn3, 1, 1.5); cout << setw(10);
	 bisection(fn3, 1.5, 2.5); cout << setw(10);
	 bisection(fn3, 2.5, 3);

	 cout << "\nregula falsi: \n";	
	 fals(fn3, -3, -2.5); cout << setw(10);
	 fals(fn3, -2.5, -1.5); cout << setw(10);
	 fals(fn3, -1.5, -1); cout << setw(10);
	 fals(fn3, 1, 1.5); cout << setw(10);
	 fals(fn3, 1.5, 2.5); cout << setw(10);
	 fals(fn3, 2.5, 3);
	 cout << endl<< endl;

	 cout << "Przykladowe iteracje: " << endl;
	 cout << "dla bisekcji: " << endl;
	 bis_iter(fn2, -2, -1); cout << endl;
	 cout << "dla regula falsi: " << endl;
	 fals_iter(fn2, -2, -1); cout << endl;
	 cout << "inne miejsce zerowe\ndla bisekcji: " << endl;
	 bis_iter(fn1, 1, 4); cout << endl;
	 cout << "dla regula falsi: " << endl;
	 fals_iter(fn1, 1, 4); cout << endl;
	 cout << endl;
	 return 0;
 }