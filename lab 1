#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	float a;
	float b;
	double c;

	/*
	веществнный тип данных, т.к. числа берутся на действительной оси
	double, чтобы переменная c не переполснилась от суммы 2-ух чисел типа данный float
	long double не использовалось для экономии памяти
	*/

	cout << "Минимальное значение float: " << numeric_limits<float>::lowest() << endl;
	cout << "Максимальное значение float: " << numeric_limits<float>::max() << endl;
	cout << "\n";
	cout << "Минимальное значение double: " << numeric_limits<double>::lowest() << endl;
	cout << "Минимальное значение double: " << numeric_limits<double>::max() << endl;

	cin >> a >> b; //Ввод краев интервала


	c = (a + b) / 2.0; //Нахождение середины интервала

	cout << c << "double" << endl;
}
