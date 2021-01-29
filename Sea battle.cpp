#include <iostream>
#include <vector>
#include <time.h>
#include "Header.h"
using namespace std;

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Rus");
	char realUserMap[SIZE][SIZE], realCompMap[SIZE][SIZE], targUserMap[SIZE][SIZE], targCompMap[SIZE][SIZE];

	int count = 0;
	int row, col, var; // последнее отвечает за то, в какую сторону расставлять корабли
	int variant;
	int User_KillPoints = 0;
	int Comp_KillPoints = 0;

	vector<vector<int>> _UserShipsData;
	vector<vector<int>> _CompShipsData;
	vector<int> shipData;

	CreateMap(realUserMap);
	CreateMap(targUserMap);

	CreateMap(realCompMap);
	CreateMap(targCompMap);

	cout << "1. Самостоятельное заполнение;\n2. Автозаполнение.";
	cout << "\n\nВыберите пункт: ";
	cin >> variant;

	switch (variant)
	{
	case 1:
	{
		cout << "Дана карта:\n\n";

		PrintMap(realUserMap);

		//заполнение пользователем

		for (int shipLen = 1; shipLen < 5; shipLen++)
		{
			do {
				cout << "\n\nВведите координаты " << shipLen << "-палубного корабля: (1:10, строка/столбец)\n\n";
				cin >> row >> col;
				var = rand() % 2 + 1;

				shipData.push_back(shipLen);
				shipData.push_back(row);
				shipData.push_back(col);
				shipData.push_back(var);

				if (shipLen > 1) {

					cout << "\n\nКак расположить корабль?\n\n\n1.Вертикально(вниз);\n\n2.Горизонтально(вправо)\n\n";
					cin >> var;
				}

				if (var == 1 && FreeSpaceCheck(realUserMap, shipLen, row, col, var))
				{
					SetShip(realUserMap, shipLen, row, col, 'V');
					PrintMap(realUserMap);
					_UserShipsData.push_back(shipData);
					count++;
				}

				else if (var == 2 && FreeSpaceCheck(realUserMap, shipLen, row, col, var))
				{
					SetShip(realUserMap, shipLen, row, col, '>');
					PrintMap(realUserMap);
					_UserShipsData.push_back(shipData);
					count++;
				}
				shipData.clear();

			} while (count != 5 - shipLen);

			count = 0;
		}
		break;
	}

	case 2:
	{
		for (int shipLen = 1; shipLen < 5; shipLen++)
		{
			do {
				col = rand() % 10 + 1;
				row = rand() % 10 + 1;
				var = rand() % 2 + 1;

				shipData.push_back(shipLen);
				shipData.push_back(row);
				shipData.push_back(col);
				shipData.push_back(var);

				if (var == 1 && FreeSpaceCheck(realUserMap, shipLen, row, col, var))
				{
					SetShip(realUserMap, shipLen, row, col, 'V');
					_UserShipsData.push_back(shipData);
					count++;
				}

				else if (var == 2 && FreeSpaceCheck(realUserMap, shipLen, row, col, var))
				{
					SetShip(realUserMap, shipLen, row, col, '>');
					_UserShipsData.push_back(shipData);
					count++;
				}
				shipData.clear();

			} while (count != 5 - shipLen);

			count = 0;
		}
		cout << "Ваша заполненная карта:\n\n";
		PrintMap(realUserMap);
		break;
	}
	}

	cout << "\n\n\nПроцесс заполнения карты компьютера...\n\n\n";
	for (int shipLen = 1; shipLen < 5; shipLen++)
	{
		do {
			col = rand() % 10 + 1;
			row = rand() % 10 + 1;
			var = rand() % 2 + 1;

			shipData.push_back(shipLen);
			shipData.push_back(row);
			shipData.push_back(col);
			shipData.push_back(var);

			if (var == 1 && FreeSpaceCheck(realCompMap, shipLen, row, col, var))
			{
				SetShip(realCompMap, shipLen, row, col, 'V');
				_CompShipsData.push_back(shipData);
				count++;
			}

			else if (var == 2 && FreeSpaceCheck(realCompMap, shipLen, row, col, var))
			{
				SetShip(realCompMap, shipLen, row, col, '>');
				_CompShipsData.push_back(shipData);
				count++;
			}
			shipData.clear();

		} while (count != 5 - shipLen);

		count = 0;
	}

	cout << "Процесс завершился удачно. Для того, чтобы начать игру, введите любой символ: ";
	char randSym;
	cin >> randSym;


	cout << "\n\n\n\t+++НАЧАЛО ИГРЫ +++\n\n\n";
	int turn = 0;
	do {
		turn = turn % 2;
		switch (turn + 1)
		{
		case 1:
		{
			cout << "\n\n\n\t+++Ход игрока " << turn + 1 << ".+++\n\n";

			cout << "Ваши карты:\n";
			cout << "\n\t+++КАРТА-МИШЕНЬ+++\n";
			PrintMap(targUserMap);
			cout << "\n\n\t+++ВАША КАРТА+++\n";
			PrintMap(realUserMap);
			cout << endl;

			cout << "Введите строку и столбец, куда вы собираетесь стрелять: ";

			cin >> row >> col;

			if (CheckShipExist(realCompMap, row, col))
			{
				SetPoint(realCompMap, row, col, 'W');
				SetPoint(targUserMap, row, col, 'W');
				cout << "\n\t\tПопадание!\n";
			}
			else {
				SetPoint(realCompMap, row, col, 'M');
				SetPoint(targUserMap, row, col, 'M');
				cout << "\n\t\tПромах!\n";
			}

			for (int i = 0, j = 0; i < 10; i++)
			{
				int shipLen = _CompShipsData[i][j];
				int row = _CompShipsData[i][j + 1];
				int col = _CompShipsData[i][j + 2];
				int var = _CompShipsData[i][j + 3];

				if (CheckKill(realCompMap, shipLen, row, col, var))
				{
					SetShip(targUserMap, shipLen, row, col, 'K');
					SetShip(realCompMap, shipLen, row, col, 'K');
					User_KillPoints++;
					cout << "\n\t\tУничтожение!\n";
				}
			}

			cout << "Ваши карты:\n";
			cout << "\n\t+++КАРТА-МИШЕНЬ+++\n";
			PrintMap(targUserMap);
			cout << "\n\n\t+++ВАША КАРТА+++\n";
			PrintMap(realUserMap);
			cout << endl;
			cout << "Для того, чтобы передать ход следующему игроку, введите любой символ: "; cin >> randSym;
			turn++;
			break;
		}

		case 2:
		{
			cout << "\n\n\n\t+++Ход игрока " << turn + 1 << ".+++\n\n";
			cout << "Ваши карты:\n";
			cout << "\n\t+++КАРТА-МИШЕНЬ+++\n";
			PrintMap(targCompMap);
			cout << "\n\n\t+++ВАША КАРТА+++\n";
			PrintMap(realCompMap);
			cout << endl;

			cout << "Введите строку и столбец, куда вы собираетесь стрелять: ";
			cin >> row >> col;
			if (CheckShipExist(realUserMap, row, col))
			{
				SetPoint(realUserMap, row, col, 'W');
				SetPoint(targCompMap, row, col, 'W');
				cout << "\n\t\tПопадание!\n";;
			}
			else {
				SetPoint(realUserMap, row, col, 'M');
				SetPoint(targCompMap, row, col, 'M');
				cout << "\n\t\tПромах!\n";
			}

			for (int i = 0, j = 0; i < 10; i++)
			{
				int shipLen = _CompShipsData[i][j];
				int row = _UserShipsData[i][j+1];
				int col = _UserShipsData[i][j+2];
				int var = _UserShipsData[i][j+3];

				if (CheckKill(realUserMap, shipLen, row, col, var))
				{
					SetShip(targCompMap, shipLen, row, col, 'K');
					SetShip(realUserMap, shipLen, row, col, 'K');
					Comp_KillPoints++;

					cout << "\n\t\tУничтожение!\n";
				}
			}

			cout << "Ваши карты:\n";
			cout << "\n\t+++КАРТА-МИШЕНЬ+++\n";
			PrintMap(targCompMap);
			cout << "\n\n\t+++ВАША КАРТА+++\n";
			PrintMap(realCompMap);
			cout << endl;
			cout << "Для того, чтобы передать ход следующему игроку, введите любой символ: "; cin >> randSym;
			turn++;
			break;
		}
		}
	} while (Comp_KillPoints != 10 && User_KillPoints != 10);

	if (Comp_KillPoints == 10)
	{
		cout << "\n\nПобедил компьютер!\n\n";
	}
	else if (User_KillPoints == 10)
	{
		cout << "\n\nПобедил игрок!\n\n";
	} else { cout << "НИЧЬЯ"; }

	return 0;
}