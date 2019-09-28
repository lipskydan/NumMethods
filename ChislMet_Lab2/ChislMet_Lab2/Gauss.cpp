#include "pch.h"
#include "Gauss.h"

#include <iostream>
#include <stdlib.h> 
#include <cmath>
#include <time.h>
#include <iomanip>

using namespace std;

Gauss::Gauss()
{
}


Gauss::~Gauss()
{
}

bool Gauss::Continue() {
	char tmp;
	cout << "Would you like to continue Gauss method (y/n): ";
	cin >> tmp;

	if (tmp == 'y') return true;
	return false;
}

void Gauss::run()
{
	srand(time(0));
	int number;
	bool cont = true;

	while (cont) {
		cout << "1. Random\n2. From keyboard\n3. Matr Gilbert\n4. Matr Diag\n\n";

		cout << "Enter the number : ";
		cin >> number;

		cout << "Enter the number of equations : ";
		cin >> n;
		a = new double*[n];
		y = new double[n];

		switch (number)
		{
		case 1:
			a = generMatrRand(n);
			y = generYRand(n);
			break;

		case 2:
			a = generMatr(n);
			y = generY(n);
			break;

		case 3:
			a = generMatrGilbert(n);
			y = generYRand(n);
			break;

		case 4:
			a = generMatrDiag(n);
			y = generYRand(n);
			break;

		default:
			break;
		}

		sysOut();
		showMatr();
		x = gauss(a, y, n);
		showX(x, n);
		checkRes();
	
		cont = Continue();
	}

}

double ** Gauss::generMatr(int n)
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

double * Gauss::generY(int n)
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

double ** Gauss::generMatrRand(int n)
{
	double **a;
	a = new double*[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			int tmp = rand() % 50 + 1;
			a[i][j] = tmp;
			if (n <= 10) cout << "a[" << i << "][" << j << "]= " << a[i][j] <<endl;
		}
	}

	return a;
}

double * Gauss::generYRand(int n)
{
	double *y;
	y = new double[n];

	for (int i = 0; i < n; i++)
	{
		int tmp = rand() % 50 + 1;
		y[i] = tmp;
		cout << "y[" << i << "]= " << y[i] <<endl;
	}

	return y;
}

double ** Gauss::generMatrGilbert(int n)
{
	double **a;
	a = new double*[n];
	
	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			double tmp = 1./(i + j + 1);
			a[i][j] = tmp;
			if (n <= 10) cout << "a[" << i << "][" << j << "]= " << a[i][j] << endl;
		}
	}

	return a;
}

double ** Gauss::generMatrDiag(int n)
{
	double **a;
	a = new double*[n];

	int f = 0;
	int tmp = 0;
	int s = 0;

	int i, j;

	for (i = 0; i < n; i++)
	{
		a[i] = new double[n];
		for (j = 0; j < n; j++)
		{
			tmp = rand() % 50 + 1;
			a[i][j] = tmp;
			if (i == j) f = abs(tmp);
			else s += abs(tmp);
			
			if (n <= 10) cout << "a[" << i << "][" << j << "]= " << a[i][j] << endl;
		}

		if (f > s) {
			continue;
		}else{
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

void Gauss::showX(double *x, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]= " << x[i] << endl;
	cout << endl;
}

void Gauss::showMatr()
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

void Gauss::checkRes()
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

void Gauss::sysOut()
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

double * Gauss::gauss(double **a, double *y, int n)
{	
	
	double *x, max;
	int k, index;
	const double eps = 0.0000001; 
	x = new double[n];

	double **aa;

	aa  = new double*[n];
	for (int i = 0; i < n; i++)
	{
		aa[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			aa[i][j] = a[i][j];
		}
	}

	double *yy;
	yy = new double[n];
	for (int i = 0; i < n; i++)
	{
		yy[i] = y[i];
	}

	k = 0;
	while (k < n)
	{
		max = abs(aa[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(aa[i][k]) > max)
			{
				max = abs(aa[i][k]);
				index = i;
			}
		}
		
		if (max < eps)
		{
			
			cout << "Solution impossible due to null column ";
			cout << index << " matrix A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = aa[k][j];
			aa[k][j] = aa[index][j];
			aa[index][j] = temp;
		}
		double temp = yy[k];
		yy[k] = yy[index];
		yy[index] = temp;

		
		for (int i = k; i < n; i++)
		{
			double temp = aa[i][k];
			if (abs(temp) < eps) continue; 
			for (int j = 0; j < n; j++)
				aa[i][j] = aa[i][j] / temp;
			yy[i] = yy[i] / temp;
			if (i == k)  continue; 
			for (int j = 0; j < n; j++)
				aa[i][j] = aa[i][j] - aa[k][j];
			yy[i] = yy[i] - yy[k];
		}
		k++;
	}

	
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = yy[k];
		for (int i = 0; i < k; i++)
			yy[i] = yy[i] - aa[i][k] * x[k];
	}
	return x;
}