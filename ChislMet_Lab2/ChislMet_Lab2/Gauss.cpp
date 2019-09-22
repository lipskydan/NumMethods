#include "pch.h"
#include "Gauss.h"

#include <iostream>
#include <stdlib.h> 

using namespace std;

Gauss::Gauss()
{
	cout << "You choose Gauss method \n\n";
}


Gauss::~Gauss()
{
}

bool Gauss::Continue() {
	char tmp;
	cout << "Would you like to continue(y/n): ";
	cin >> tmp;

	if (tmp == 'y') return true;
	return false;
}

void Gauss::run()
{
	int number;
	bool cont = true;

	while (cont) {
		cout << "1. Random\n2. From keyboard\n\n";

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

		default:
			break;
		}

		sysOut(a, y, n);
		x = gauss(a, y, n);
		showX(x, n);

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
			cout << "a[" << i << "][" << j << "]= " << a[i][j] <<endl;
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

void Gauss::showX(double *x, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]=" << x[i] << endl;
	cout << endl;
}

// Вывод системы уравнений
void Gauss::sysOut(double **a, double *y, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "*x" << j;
			if (j < n - 1)
				cout << " + ";
		}
		cout << " = " << y[i] << endl;
	}
	cout << endl;
	return;
}

double * Gauss::gauss(double **a, double *y, int n)
{
	double *x, max;
	int k, index;
	const double eps = 0.00001;  // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "Solution impossible due to null column ";
			cout << index << " matrix A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;

		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k)  continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}

	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}