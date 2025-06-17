// Какая-то штука для Visual Studio, можно убрать
#include "stdafx.h"

#include <iostream>
#include <functional>
#include <cmath>

void someFunc(int arg1, double arg2) {
	std::cout << arg1 << " " << arg2;
}

// c style
void getFunc(void(*f)(int arg1, double arg2)) {
	f(1, 543.32);
}

void getFunc2(std::function<void(int, double)> f) {
	f(1, 543.32);
}

struct SomeStruct {
	int a;
	float b;
};

struct Point {
	double _x;
	double _y;

	Point(double x, double y)
		: _x(x)
		, _y(y) {}
	
	double abs() const {
		return sqrt(_x * _x + _y * _y);
	}
};

void CallFuncton(std::function<double()> f) {
	std::cout << "Calling f: ";
	f();
	std::cout << std::endl;
}

int main2() {
	// std::cout << "test" << std::endl;

	getFunc(someFunc);
	getFunc2(someFunc);

	SomeStruct variable;
	int u = 123;

	// [] - захват переменных
	// () - как у обычной функции аргументы
	// {} - тело функции
	auto lambdaF = [variable, u](int arg1, double arg2) {
		std::cout << "arg1: " << arg1;
		std::cout << " ";
		std::cout << "arg2: " << arg2;
		std::cout << std::endl;

		std::cout << "Struct: " << variable.a << " " << variable.b;
		std::cout << std::endl;

		std::cout << u;
		std::cout << std::endl;
	};

	lambdaF(6, 754);
	lambdaF(-6, 41754);

	return 0;
}

void long_f(int a1, int a2, int a3, int a4, int a5) {
	std::cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << std::endl;
}

int main() {
	Point p(3, 4);

	// Связывание метода класса с объектом класса
	auto f = std::bind(&Point::abs, &p);

	double value = f();
	std::cout << value << std::endl;

	p._x = 8;

	value = f();
	std::cout << value << std::endl;

	CallFuncton(f);

	// Связывание функции и её аргументов
	// placeholders - места, в аргументами которых должны являтся аргументы полученной функции
	auto f2 = std::bind(long_f, 3, 5, std::placeholders::_1, 1, std::placeholders::_2);

	f2(0, 0);
	f2(10, 40);

	return 0;
}