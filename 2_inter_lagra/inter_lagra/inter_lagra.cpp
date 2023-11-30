#include <iostream>
#include <fstream>
#include <string>
constexpr auto N = 80;
constexpr auto Z = 119;
using namespace std;
//uwazaj na wszytski N i Z i nazwy plikow thx


double lagrange(double *wyniki, double *ytab, double *xtab, double wart) {

	for (int i = 0; i < Z; i++)
	{
		wyniki[i] = ytab[i]; //przypisanie wart y
		for (int j = 0; j < Z; j++) {
			if (xtab[i] != xtab[j])
			{
				wyniki[i] *= (wart - xtab[j]);
			}
		}
		for (int k = 0; k < Z; k++) {
			if (xtab[i] != xtab[k])
			{
				wyniki[i] /= (xtab[i] - xtab[k]);
			}
		}
	}

	double suma = 0;

	for (int i = 0; i < Z; i++)
	{
		suma += wyniki[i];

	}
	return suma;
}

int main()
{
	//double xtab[N]{}, ytab[N]{}, wyniki[N]{};
	double xtab[Z]{}, ytab[Z]{}, wyniki[Z]{};

	fstream xplik("x_wart.txt", ios::in);
	fstream yplik("y_wart.txt", ios::in);
	fstream xp("x_w.txt", ios::in);
	fstream yp("y_w.txt", ios::in);
	if ((xp.good() || yp.good()) == false) {
		cout << "brak pliku" << endl;
		exit(0);
	}


	for (int i = 0; i < Z; i++) {
		if (!xp.eof()) {
			xp >> xtab[i];
			yp >> ytab[i];
		}
		//cout <<"f(" << xtab[i]<<") = " << ytab[i]<<endl;
	}
	
	cout << "podaj watosc do interpolacji: " << endl;
	double wart;
	cin >> wart;

	for (int i = 0; i < Z; i++)
	{
		wyniki[i] = ytab[i]; //przypisanie wart y
		for (int j = 0; j < Z; j++) {
			if (xtab[i] != xtab[j])
			{
				wyniki[i] *= (wart - xtab[j]);
			}
		}
		for (int k = 0; k < Z; k++) {
			if (xtab[i] != xtab[k])
			{
				wyniki[i] /= (xtab[i] - xtab[k]);
			}
		}
	}

	double suma = 0;
	
	for (int i = 0; i < Z; i++)
	{	
		suma += wyniki[i];	
		
	}
	
	cout <<endl << "wartosc obliczona: "<<endl<< suma << endl;
	

	for (int i = 0; i < Z; i++) {
		cout << "f(" << xtab[i] << ")= " << ytab[i] << endl;
	}
		xp.close();
		yp.close();
	
	return 0;
}
