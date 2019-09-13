// ChislMet_Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <cmath>

using namespace std;

///////////////////////////////////////////- F1 -///////////////////////////////////////////////////////////

class F1 {
public:
	void Main() {
		cout << "We work with F1: \n";

		double a, b, eps, x;
		cout << "  interval: ";
		cin >> a;
		cin >> b;

		if (F(a)*F(b) > 0) {
			cout << "  Wrong interval!\n";
			return;
		}
		cout << "  eps: ";
		cin >> eps;
		x = Alg( a, b, eps);

		cout << "------------------------------\n";
		cout << "  Result:\n   x = " << x << endl;
		cout << "------------------------------\n";
	}

private:
	double F(double x) {
		return (x*x)-4;  
														  // x^2 - 4 interval 1 4 eps 0.00001 
														  // (x*x*x)-x-2  interval 1 2 eps 0.00001 res 1.5213928	 
														  // x - 4 interval 1 8 eps 0.00001
														  // sin(​x/​5)*​exp(​x/​10)+​5*​exp(​(‑x)/​2) interval 1 30 eps 0.00001 res 15.7
	}

	double Alg(double a, double b, double eps) {
		double c;
		int index = 1;
		while ((b - a) > eps) {
			c = (a + b) / 2;
			if ((F(a)*F(c)) < 0) b = c;
			else a = c;

			cout << "\n index = " << index << endl;
			cout << "    a = " << a << endl;
			cout << "    b = " << b << endl;
			index++;
		}
		return c;
	}
};

//////////////////////////////////////////////- F2 -////////////////////////////////////////////////////////

class F2 {
public:
	void Main() {
		cout << "We work with F2: \n";
		double x0, alpha, eps;
		eps = 0.00001;
		alpha = -0.1;
		cout << "  x0 = "; cin >> x0;
		cout << "  alpha = " << alpha <<"\n"; //cin >> alpha;
		cout << "  eps = " << eps <<endl;

		double x = Alg(x0, alpha, eps);
		cout << "------------------------------\n";
		cout << "  Result:\n   x = " << x <<endl;
		cout << "------------------------------\n";
	}


private:
	double F(double x) {
		return x*x;
							// x^2 - 4 eps = 0.00001 alpha = -0.05
							// (x*x*x) - x - 2 -||- res 1.5213928	
							// (x*x*x) - 8 
							// sin(x)  --> (res*180)/pi = res in gradus
							// x^2 alpha = -0.5
	}

	double Alg(double x0, double alpha, double eps) {
		int index = 1;
		

		double x1 = alpha * F(x0) + x0;

		cout << "\n index = " << index << endl; index++;
		cout <<"    abs( "<<x1 << " - " << x0 << ") = " << abs(x1 - x0) <<endl;
		cout <<"    x0 = " << x0 << endl;
		cout <<"    x1 = " << x1 << endl;

		while (fabs(x1 - x0) >= eps)
		{
			x0 = x1;
			x1 = alpha*F(x0) + x0;

			cout << "\n index = " << index << endl; index++;
			cout << "    abs( " << x1 << " - " << x0 << ") = " << abs(x1 - x0) << endl;
			cout << "    x0 = " << x0 << endl;
			cout << "    x1 = " << x1 << endl;
		}
		
		return x1;
	}
		
};

//////////////////////////////////////////////////- F3 -/////////////////////////////////////////////////////

class F3 {
public:
	void Main() {
		cout << "We work with F3: \n";
		double x0, alpha, eps;
		eps = 0.000000001;
		//alpha = -0.5;
		cout << "  x0 = "; cin >> x0;
		//cout << "  alpha = " << alpha << "\n"; //cin >> alpha;
		cout << "  eps = " << eps << endl;

		double x = Alg(x0, eps);

		cout << "------------------------------\n";
		cout << "  Result:\n   x = " << x << endl;
		cout << "------------------------------\n";
	}

private:
	double F(double x) {
		return (x*x) - 4;
						// x^2 - 4 eps = 0.00001 
						// (x*x*x) - x - 2 -||- res 1.5213928	
						// (x*x*x) - 8 
						// sin(x)  --> (res*180)/pi = res in gradus
	}

	double F_Poh(double x)
	{
		return 2*x;
	}

	double Alg(double x0, double eps) {
		double x1;
		int index = 1;
	
		x1 = x0 - (F(x0) / F_Poh(x0));

		cout << "\n index = " << index << endl; index++;
		cout << "    abs( " << x1 << " - " << x0 << ") = " << abs(x1 - x0) << endl;
		cout << "    x0 = " << x0 << endl;
		cout << "    x1 = " << x1 << endl;
		cout << "    F(x)= " << F(x0) << endl;

		while (fabs(x1 - x0) >= eps)
		{
			x0 = x1;
			//x1 = alpha * F(x0) + x0;
			x1 = x0 - (F(x0) / F_Poh(x0));

			cout << "\n index = " << index << endl; index++;
			cout << "    abs( " << x1 << " - " << x0 << ") = " << abs(x1 - x0) << endl;
			cout << "    x0 = " << x0 << endl;
			cout << "    x1 = " << x1 << endl;
			cout << "    F(x)= " << F(x0) << endl;
		}

		return x1;
	}

};

//////////////////////////////////////////////////- Menu -//////////////////////////////////////////////////

class Menu {
private:
	bool Continue() {
		cout << "Would you like continue (Y/N) ";
		string str;
		cin >> str;
		if (str == "Y" || str == "y") return true;
		else return false;

	}

public:
	void menu() {
		int tmp;
		bool cont = true;
		cout << "1. Bisection method\n";
		cout << "2. Simple iteration method\n";
		cout << "3. Newton's method\n";


		while (cont) {
			cout << "Input number: ";
			cin >> tmp;

			switch (tmp)
			{
			case 1:
				F1 f1;
				f1.Main();
				cont = Continue();
				break;
			case 2:
				F2 f2;
				f2.Main();
				cont = Continue();
				break;
			case 3:
				F3 f3;
				f3.Main();
				cont = Continue();
				break;
			default:
				break;
			}
		}
	}
};



int main() {
	Menu a;
	a.menu();
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
