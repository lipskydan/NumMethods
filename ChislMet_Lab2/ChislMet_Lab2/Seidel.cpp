#include "pch.h"
#include "Seidel.h"

#include <iostream>
#include <stdlib.h> 
#include <cmath>
#include <time.h>
#include <iomanip>

using namespace std;

Seidel::Seidel()
{
}


Seidel::~Seidel()
{
}

bool Seidel::Continue() {
	char tmp;
	cout << "Would you like to continue Seidel method (y/n): ";
	cin >> tmp;

	if (tmp == 'y') return true;
	return false;
}

void Seidel::run()
{
	srand(time(0));
	bool cont = true;

	while (cont) {
		cout << "Enter the number of equations : ";
		cin >> n;
		a = new double*[n];
		y = new double[n];

		a = generMatrDiag(n);
		y = generYRand(n);

		sysOut(a, y, n);
		showMatr();

		x = seidel(a, y, n);
		showX(x, n);
		checkRes();

		cont = Continue();
	}
}

double * Seidel::generYRand(int n)
{
	double *y;
	y = new double[n];

	for (int i = 0; i < n; i++)
	{
		int tmp = rand() % 50 + 1;
		y[i] = tmp;
		cout << "y[" << i << "]= " << y[i] << endl;
	}

	return y;
}

double ** Seidel::generMatrDiag(int n)
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

void Seidel::showX(double *x, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]= " << x[i] << endl;
	cout << endl;
}

void Seidel::showMatr()
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

void Seidel::checkRes()
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

void Seidel::sysOut(double **a, double *y, int n)
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

double * Seidel::seidel(double ** a, double * y, int n)
{
	double *x;
	x = new double[n];
	const double eps = 0.0001;
	
	int i, j;
	double norma;

	double *xn;
	xn = new double[n];

	for (int i = 0; i < n; i++) xn[i] = 0;

	do {
		norma = 0.0;
		for (i = 0; i < n; i++)
		{
			xn[i] = -y[i];

			for (j = 0; j < n; j++)      
			{
				if (i != j)
					xn[i] += a[i][j] * x[j];
			}

			xn[i] /= -a[i][i];
		}

		for (i = 0; i < n; i++)
		{
			if (fabs(x[i] - xn[i]) > norma)
				norma = fabs(x[i] - xn[i]); 
			x[i] = xn[i];
		}

	} while (norma > eps);


	return x;
}
