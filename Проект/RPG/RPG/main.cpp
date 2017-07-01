#include "source/Game.hpp"
#include <iostream> 

using namespace std;

int main()
{
	setlocale(0, "rus");

	int hero = 0, lvl = 0;
	while (true)
	{
		cout << "Добро пожаловать в RGP игру - Evil mushrooms!" << endl;
		cout << "Выбирите героя:" << endl;
		cout << "1 - MEGAMAN (Уничтожает грибы из автоматической пушки)" << endl;
		cout << "2 - CYCLON (Уничтожает грибы из лазером из глаз)" << endl;
		cin >> hero;
		cout << "Выбирите уровень:" << endl;
		cin >> lvl;


		cout << RunGame(hero, lvl)<< endl;
	}


	return 0;
}
