#include "pch.h"
#include "Jacobi.h"

#include <iostream>
#include <stdlib.h> 
#include <cmath>
#include <time.h>
#include <iomanip>

using namespace std;

Jacobi::Jacobi()
{
}


Jacobi::~Jacobi()
{
}

bool Jacobi::Continue() {
	char tmp;
	cout << "Would you like to continue Jacobi method (y/n): ";
	cin >> tmp;

	if (tmp == 'y') return true;
	return false;
}

void Jacobi::run()
{
	srand(time(0));
	bool cont = true;
	int number;

	while (cont) {
		cout << "1. From keyboard\n2. Matr Diag\n\n";

		cout << "Enter the number : ";
		cin >> number;

		cout << "Enter the number of equations : ";
		cin >> n;
		a = new double*[n];
		y = new double[n];

		switch (number)
		{
		case 1:
			a = generMatr(n);
			y = generY(n);
			break;
		case 2:
			a = generMatrDiag(n);
			y = generYRand(n);
			break;

		default:
			break;
		}

		sysOut(a, y, n);
		showMatr();

		x = jacobi(a, y, n);
		showX(x, n);
		checkRes();

		cont = Continue();
	}
}

double ** Jacobi::generMatr(int n)
{
	double **a;
	a = new double*[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			cout << "a[" << i << "][" << j << "]= ";
			cin >> a[i][j];
		}
	}

	return a;
}

double * Jacobi::generY(int n)
{
	double *y;
	y = new double[n];

	for (int i = 0; i < n; i++)
	{
		cout << "y[" << i << "]= ";
		cin >> y[i];
	}

	return y;
}

double * Jacobi::generYRand(int n)
{
	cout << endl;
	double *y;
	y = new double[n];

	for (int i = 0; i < n; i++)
	{
		int tmp = rand() % 50 + 1;
		y[i] = tmp;
		cout << "y[" << i << "]= " << y[i] << endl;
	}
	cout << endl;

	return y;
}

double ** Jacobi::generMatrDiag(int n)
{
	double **a;
	a = new double*[n];

	int f = 0;
	int tmp = 0;
	int s = 0;

	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			tmp = rand() % 50 + 1;
			a[i][j] = tmp;
			if (i == j) f = abs(tmp);
			else s += abs(tmp);

			if (n <= 10) cout << "a[" << i << "][" << j << "]= " << a[i][j] << endl;
		}

		if (f > s) {
			continue;
		}
		else {
			a[i][i] += f + s;
			f = 0;
			s = 0;
		}
	}
	if (n <= 10){
		cout << "--------------------------------------" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << "a[" << i << "][" << j << "]= " << a[i][j] << endl;
			}
		}
	}
	return a;
}

void Jacobi::showX(double *x, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]= " << x[i] << endl;
	cout << endl;
}

void Jacobi::showMatr()
{
	if (n <= 10) {
		cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(3) << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Jacobi::checkRes()
{
	cout << endl;
	cout << "checkRes: Our = Real\n";
	double res = 0;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//if (n <= 5) { cout << a[i][j] << " * " << x[j]; if (j < n - 1) cout << " + "; }
			res += a[i][j] * x[j];
		}
		cout << res << " = " << y[i] << endl;
		res = 0;
	}
	cout << endl;
}


void Jacobi::sysOut(double **a, double *y, int n)
{
	if (n <= 5) {
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << a[i][j] << "*x" << j;
				if (j < n - 1)
					cout << setw(2) << " + " << setw(2);
			}
			cout << setw(2) << " = " << y[i] << setw(2) << endl;
		}
		cout << endl;
	}
	return;
}

double * Jacobi::jacobi(double ** a, double * y, int n)
{
	double *x;
	x = new double[n];

	int i, j, count = 0;
	double *tmp_x, norma, e;

	tmp_x = new double[n];
	e = 0.0000001;
	
	for (i = 0; i < n; i++) {
		x[i] = 0;
	}


	do {
		count++;

		for (i = 0; i < n; i++) {
			tmp_x[i] = 0.0;
			for (j = 0; j < n; j++) {
				if (i != j) {
					//cout << "      tmp_x[" << i << "] = " << tmp_x[i] << " + ( " << a[i][j] << " * " << x[j] << " ) = " << tmp_x[i] << "\n";
					tmp_x[i] = tmp_x[i] + (a[i][j] * x[j]);
					
				}
			}

			//cout << "tmp_x[" << i << "] = (" << y[i] << " - " << tmp_x[i] << " ) / " << a[i][i] << " = " << tmp_x[i] << " \n";
			tmp_x[i] = (y[i] - tmp_x[i]) / a[i][i];
		}

		norma = 0;

		//for (i = 0; i < n; i++) cout << "tmp_x[" << i << "] = " << tmp_x[i] << "\n";

		for (i = 0; i < n; i++) {
			if (fabs(x[i] - tmp_x[i]) > norma) {
				//cout << "exp before = " << exp;
				norma = fabs(x[i] - tmp_x[i]);
				//cout << "exp after = " << exp << endl;
			}
			x[i] = tmp_x[i];
		}
	} while (norma > e);

	return x;
}
