#include "source/Game.hpp"
#include <iostream> 

using namespace std;

int main()
{
	setlocale(0, "rus");

	int hero = 0, lvl = 0;
	while (true)
	{
		cout << "����� ���������� � RGP ���� - Evil mushrooms!" << endl;
		cout << "�������� �����:" << endl;
		cout << "1 - MEGAMAN (���������� ����� �� �������������� �����)" << endl;
		cout << "2 - CYCLON (���������� ����� �� ������� �� ����)" << endl;
		cin >> hero;
		cout << "�������� �������:" << endl;
		cin >> lvl;


		cout << RunGame(hero, lvl)<< endl;
	}


	return 0;
}
