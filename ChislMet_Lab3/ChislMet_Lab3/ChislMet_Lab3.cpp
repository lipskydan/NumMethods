// ChislMet_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

double alpha = 0.85;
double *tmp;

//////////////////////////////////////-FIRST STEP-//////////////////////////////////////

double** InitGraf(int n) {
	double **graf;
	graf = new double*[n];

	for (int i = 0; i < n; i++)
	{
		graf[i] = new double[n];
		cout << "graf[" << i << "] : ";
		for (int j = 0; j < n; j++)
		{
			cin >> graf[i][j];
		}
	}


	tmp = new double[n];
	for (int i = 0; i < n; i++) {
		tmp[i] = 0;
		//cout << "size: " << tmp[i] << endl;
	}

	//cout << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (graf[i][j] == 1) tmp[i]++;
		}
		//cout << "size: " << tmp[i] << endl << endl;
	}

	return graf;
}

void ShowGraf(double **graf, int n) {

	cout << "\nShow Graf :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (graf[i][j] == 1) cout << i << " -> " << j << endl;
		}
		cout << "size: " << tmp[i] << endl << endl;
	}
}

//////////////////////////////////////-SECOND STEP-//////////////////////////////////////

double** InitMatrA(double **graf, int n) {
	double **a;
	a = new double*[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = new double[n];
		
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 0;
		}
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (graf[j][i] == 1) {
				a[i][j] = 1 / tmp[j];
			}
		}
		
	}


	return a;
}

void ShowMatrA(double **a, int n) {

	cout << "\nShow MatrA :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << a[i][j] << " ";
		}
		cout << endl;
	}
}

//////////////////////////////////////-THIRD STEP-//////////////////////////////////////

double** InitMatrM(int n) {
	double **M;
	M = new double*[n];

	for (int i = 0; i < n; i++)
	{
		M[i] = new double[n];

		for (int j = 0; j < n; j++)
		{
			M[i][j] = 1.0/n;
			//cout << "\nM[" << i << "][" << j << "] = " << 1 << "/" << n << " = " << M[i][j] << "\n";
		}
	}

	/*cout << "\nShow MatrM :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << M[i][j] << " ";
		}
		cout << endl;
	}*/

	return M;
}

double** InitMatrB(double **A, double **M, int n) {

	double **b;
	b = new double*[n];

	double **bl;
	bl = new double*[n];

	double **br;
	br = new double*[n];

	for (int i = 0; i < n; i++) {
		bl[i] = new double[n];
		br[i] = new double[n];
		b[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			bl[i][j] = alpha * A[i][j];
			br[i][j] = (1 - alpha) * M[i][j];
			b[i][j] = bl[i][j] + br[i][j];
		}
	}

	/*cout << "\nShow MatrBL :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << bl[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\nShow MatrBR :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << br[i][j] << " ";
		}
		cout << endl;
	}*/

	return b;
}

void ShowMatrB(double **b, int n) {

	cout << "\nShow MatrB :\n";

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(10) << b[i][j] << " ";
		}
		cout << endl;
	}
}

//////////////////////////////////////-FOURTH STEP-//////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	double **graf;
	double **matrA;
	double **matrB;
	double **matrM;
	int n;

	cout << "Input quantity: "; cin >> n;

	graf = InitGraf(n);
	ShowGraf(graf, n);

	matrA = InitMatrA(graf, n);
	ShowMatrA(matrA, n);

	matrM = InitMatrM(n);

	matrB = InitMatrB(matrA, matrM, n);
	ShowMatrB(matrB, n);

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
