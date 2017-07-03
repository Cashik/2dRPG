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
		cout << "Выберите героя:" << endl;
		cout << "1 - MEGAMAN (Уничтожает грибы из автоматической пушки. Маленький ростом. Хорошая регенерация.)" << endl;
		cout << "2 - МАРИО (Старый добрый марио одетый в циклопа из X-MANов. Жизненный опыт научил его, что можно не только топтать. Большой запас здоровья.)" << endl;
		cin >> hero;

		cout << RunGame(hero)<< endl;
	}


	return 0;
}
