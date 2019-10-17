// ChislMet_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

/////////////////////////////////////////-CONST-////////////////////////////////////////

const double alpha = 0.85;
const double e = 1e-9;

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

	delete tmp;

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

double* InitX0(int n) {
	double *x0;
	x0 = new double[n];

	for (int i = 0; i < n; i++) x0[i] = 1.0 / n;

	return x0;
}

double* B_multi_x(double* x0, double** B, int n) {
	double *c;
	c = new double[n];

	for (int i = 0; i < n; i++) c[i] = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double tmp = B[i][j] * x0[j];
			c[i] += tmp;
		}
	}

	return c;
}

bool CheckE(double* x0, double* x1, int n) {

	double res = 0;

	for (int i = 0; i < n; i++)
	{
		res += pow((x1[i] - x0[i]), 2);
	}

	res = pow((res), 0.5);

	if (res < e) return false;

	return true;
	/*for (int i = 0; i < n; i++)
	{
		if (abs(x1[i] - x0[i]) < e) return false;
	}

	return true;*/
}

void Func(double* x0, double** B, int n) {
	
	double *x1;
	x1 = new double[n];

	bool q = false;

	do {

		if (q) {
			for (int i = 0; i < n; i++) x0[i] = x1[i];
		}
		q = true;

		x1 = B_multi_x(x0, B, n);

		/*for (int i = 0; i < n; i++) cout << "\n" << x1[i] << " ";
		cout << endl;*/

	} while (CheckE(x0,x1,n) == true); 

	cout << "\nVector X is :\n";
	for (int i = 0; i < n; i++) cout << setw(21) << x1[i] << "\n";

}

////////////////////////////////////////-CHECK-/////////////////////////////////////////

void CheckRes(double** matrB, double* x0, int n) {
	cout << "\nMatrB * X =\n";
	double* Bx;
	Bx = new double[n];

	for (int i = 0; i < n; i++) {
		Bx[i] = 0;
		for (int j = 0; j < n; j++) {
			double tmp = matrB[i][j] * x0[j];
			Bx[i] += tmp;
		}
	}

	for (int i = 0; i < n; i++) cout << setw(21) << Bx[i] << endl;

	delete Bx;
}

///////////////////////////////////////-CONTINUE-///////////////////////////////////////

bool Cont() {
	string str;
	cout << "Would you like to continue(y/n)?: "; cin >> str;
	if (str == "y" || str == "yes") {
		cout << "\n\n";
		return true;
	}
	else return false;
}

/////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	double **graf;
	double **matrA;
	double **matrB;
	double **matrM;
	int n;

	bool cont = true;

	do{
		cout << "Input quantity: "; cin >> n;

		graf = InitGraf(n);
		ShowGraf(graf, n);

		matrA = InitMatrA(graf, n);
		ShowMatrA(matrA, n);

		matrM = InitMatrM(n);

		matrB = InitMatrB(matrA, matrM, n);
		ShowMatrB(matrB, n);

		double *x0;
		x0 = InitX0(n);

		Func(x0, matrB, n);

		CheckRes(matrB, x0, n);
	
		cont = Cont();

	} while (cont);

	delete graf;
	delete matrA;
	delete matrB;
	delete matrM;
	
	delete tmp;

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
