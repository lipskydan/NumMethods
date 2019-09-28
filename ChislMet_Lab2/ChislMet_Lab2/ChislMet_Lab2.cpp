// ChislMet_Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

#include "Gauss.h"
#include "Jacobi.h"
#include "Seidel.h"

using namespace std;

int main()
{
	bool cont = true;

	while (cont) {

		cout << "1. Gauss \n2. Jacobi \n3. Seidel\n\n";

		int num;
		cout << "Input number: ";
		cin >> num;

		Gauss gauss = Gauss();
		Jacobi jacobi = Jacobi();
		Seidel seidel = Seidel();

		switch (num)
		{
		case 1:
			cout << "You choose Gauss method \n\n";
			gauss.run();
			break;
		case 2:
			cout << "You choose Jacobi method \n\n";
			jacobi.run();
			break;
		case 3:
			cout << "You choose Seidel method \n\n";
			seidel.run();
			break;
		default:
			break;
		}

		cout << "Would you like to continue Main program (y/n)?: ";
		char tmp;
		cin >> tmp;
		if (tmp == 'y') cont = true;
		else cont = false;
	}
	
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
