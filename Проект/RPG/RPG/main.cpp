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
		cout << "1 - MEGAMAN (���������� ����� �� �������������� �����. ��������� ������. ������� �����������.)" << endl;
		cout << "2 - ����� (������ ������ ����� ������ � ������� �� X-MAN��. ��������� ���� ������ ���, ��� ����� �� ������ �������. ������� ����� ��������.)" << endl;
		cin >> hero;

		cout << RunGame(hero)<< endl;
	}


	return 0;
}
