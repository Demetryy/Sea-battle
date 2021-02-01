#pragma once
#pragma once
#include <iostream>
using namespace std;

const int SIZE = 11;

void CreateMap(char arr[][SIZE])
{
	char letters[SIZE - 1] = { 'A','B','C','D','E','F','G','H','I','J' };

	char digits[SIZE - 1] = { '1','2','3','4','5','6','7','8','9','0' };

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i == 0 && j > 0)
				arr[i][j] = letters[j - 1];

			else if (i > 0 && j == 0)
				arr[i][j] = digits[i - 1];

			else
				arr[i][j] = ' ';
		}
	}

	arr[0][0] = '+';
	arr[10][0] = '0';
}

void PrintMap(char arr[][SIZE])  //ôóíêöèÿ âûâîäà ìàññèâà íà ýêðàí
{
	cout << endl << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << arr[i][j] << " | ";
		}
		cout << endl << "-------------------------------------------" << endl;
	}
}

void SetShip(char arr[][SIZE], int shipLen, int row, int col, char sym) //ôóíêöèÿ çàïîëíåíèÿ îïðåäåëåííîé îáëàñòè ñèìâîëàìè
{
	if (sym == 'V')
	{
		for (int i = row - 1; i < row + shipLen + 1; i++)
		{
			for (int j = col - 1; j < col + 2; j++)
			{
				if (arr[i][j] == ' ')
				{
					arr[i][j] = '.';
				}
			}
		}
		for (int i = 0; i < shipLen; i++) {
			arr[row + i][col] = sym;
		}
	}

	else if (sym == '>')
	{
		for (int i = row - 1; i < row + 2; i++)
		{
			for (int j = col - 1; j < col + shipLen + 1; j++)
			{
				if (arr[i][j] == ' ')
				{
					arr[i][j] = '.';
				}
			}
		}

		for (int i = 0; i < shipLen; i++) {
			arr[row][col + i] = sym;
		}
	}

	else
	{
		arr[row][col] = sym;
	}
}

bool FreeSpaceCheck(char arr[][SIZE], int shipLen, int row, int col, int var)
{
	bool flag = true;

	if (var == 1)
	{


		if (row + shipLen - 1 > SIZE || row == 0) {
			flag = false;
		}

		if (flag)
		{
			for (int i = row - 1; i < row + shipLen + 1; i++)
			{
				for (int j = col - 1; j < col + 2; j++)
					if (arr[i][j] == 'V' || arr[i][j] == '>') {
						flag = false;
					}
			}
		}
	}

	else if (var == 2)
	{

		if (col + shipLen - 1 > SIZE || col == 0)
		{
			flag = false;
		}

		if (flag)
		{
			for (int i = row - 1; i < row + 2; i++)
			{
				for (int j = col - 1; j < col + shipLen + 1; j++)
				{
					if (arr[i][j] == 'V' || arr[i][j] == '>') {
						flag = false;
					}
				}
			}
		}
	}
	else {
		cout << "\n\nÂû íåâåðíî âûáðàëè âàðèàíò.\n\n";
		flag = false;
	}
	return flag;
}

void SetPoint(char arr[][SIZE], int row, int col, char sym)
{
	arr[row][col] = sym;
}

bool CheckShipExist(char arr[][SIZE], int row, int col)
{
	bool flag = false;

	if (arr[row][col] == 'V' || arr[row][col] == '>')
		flag = true;

	return flag;
}

bool CheckKill(char arr[][SIZE], int shipLen, int row, int col, int var)
{
	bool flag = false;
	int points = 0;

	if (var == 1)
	{
		for (int i = 0; i < shipLen; i++) {
			if (arr[row + i][col] == 'W')
			{
				points++;
			}
		}
	}
	else if (var == 2)
	{
		for (int i = 0; i < shipLen; i++) {
			if (arr[row][col + i] == 'W')
			{
				points++;
			}
		}
	}

	if (points == shipLen)
	{
		flag = true;
	}

	return flag;
}
