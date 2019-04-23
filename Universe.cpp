#include "Universe.h"

Map::Map() {}
Map::Map(int s1, int s2)
{
	size1 = s1;
	size2 = s2;
	arr = new char*[size1];
	for (int i = 0; i < size1; i++)
		arr[i] = new char[size2];
	zeroer();
}
void Map::zeroer()
{
	for (int i = 0; i < size1; i++)
		for (int j = 0; j < size2; j++)
			arr[i][j] = ' ';
}
void Map::assign(Map object)
{
	for (int i = 0; i < size1; i++)
		for (int j = 0; j < size2; j++)
			arr[i][j] = object.arr[i][j];
}
void Map::newshow()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "\n   .";
	for (int k = 0; k < size2 - 1; k++)
	{
		if (k == size2 - 2)
			cout << "  .";
		cout << " .";
	}
	cout << "\n";
	for (int i = 0; i < size1; i++)
	{
		cout << "   .";
		for (int j = 0; j < size2; j++)
		{
			if (arr[i][j] == 'O')
			{
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 12));  //4 - red, 12 - lightred, 
				cout << arr[i][j] << " ";
			}
			else
			{
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
				cout << arr[i][j] << " ";
			}
		}
		cout << ".\n";
	}
	cout << "   .";
	for (int k = 0; k < size2; k++)
		cout << " .";
	cout << ".\n";
}
void Map::getsize(int& s1, int& s2)
{
	s1 = size1;
	s2 = size2;
}
void Map::find(char sym, int& number1, int& number2, int& status)
{
	status = 0;
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr[i][j] == sym)
			{
				number1 = i;
				number2 = j;
				status++;
			}
		}
	}
}


Universe::Universe() { symbol = 'O'; }
void Universe::add(Map object, int status)
{
	int x = 0, y = 0;
	if (status == 1 || status == 2)
	{
		cout << "  ѕожалуйста, введите координаты: \n  x: ";
		cin >> y;
		y = y - 1;
		cout << "  y: ";
		cin >> x;
		x = x - 1;
	}
	if(status == 1)
		object.arr[x][y] = symbol;
	if (status == 2)
	{
		object.arr[x][y] = 'X';
		if (check(object, x - 1, y, 1) == true)
			if (object.arr[x - 1][y] == ' ')
				object.arr[x - 1][y] = 'O';
		if (check(object, x + 1, y, 1) == true)
			if (object.arr[x + 1][y] == ' ')
				object.arr[x + 1][y] = 'O';
		if (check(object, x, y - 1, 1) == true)
			if (object.arr[x][y - 1] == ' ')
				object.arr[x][y - 1] = 'O';
		if (check(object, x, y + 1, 1) == true)
			if (object.arr[x][y + 1] == ' ')
				object.arr[x][y + 1] = 'O';
	}
	if (status == 3)
	{
		int n = 0;
		cout << "¬ведите количество рандомных клеток: ";
		cin >> n;
		int a = 20, b = 40;
		srand(time(NULL));
		int x = 0, y = 0;
		for (int i = 0; i < 25; i++)
		{
			x = rand() % a;
			y = rand() % b;
			if (object.arr[x][y] == ' ')
			{
				object.arr[x][y] = 'X';
				if (check(object, x - 1, y, 1) == true)
					if (object.arr[x - 1][y] == ' ')
						object.arr[x - 1][y] = 'O';
				if (check(object, x + 1, y, 1) == true)
					if (object.arr[x + 1][y] == ' ')
						object.arr[x + 1][y] = 'O';
				if (check(object, x, y - 1, 1) == true)
					if (object.arr[x][y - 1] == ' ')
						object.arr[x][y - 1] = 'O';
				if (check(object, x, y + 1, 1) == true)
					if (object.arr[x][y + 1] == ' ')
						object.arr[x][y + 1] = 'O';
			}
		}
		for (int i = 0; i < n; i++)
		{
			x = rand() % a;
			y = rand() % b;
			if (object.arr[x][y] == ' ')
				object.arr[x][y] = 'O';
		}
	}
}
void Universe::buttons(Map object, char sym)
{
	if (sym == 'z')
		add(object, 1);
	if (sym == 'h')
		add(object, 2);
	if (sym == 'r')
		add(object, 3);
}

void Universe::NewBirthAndDeath(Map object)
{
	int s1 = 0, s2 = 0;
	object.getsize(s1, s2);
	Map ChangeObject(s1, s2);
	ChangeObject.zeroer();
	ChangeObject.assign(object);
	int counter = 0;

	for (int i = 0; i < s1; i++)
		for (int j = 0; j < s2; j++)
			if (ChangeObject.arr[i][j] == ' ' || ChangeObject.arr[i][j] == 'O')
			{
				if (check(ChangeObject, i, j + 1, 1) == true)
					if (ChangeObject.arr[i][j + 1] == symbol)
						++counter;
				if (check(ChangeObject, i, j - 1, 1) == true)
					if (ChangeObject.arr[i][j - 1] == symbol)
						++counter;
				if (check(ChangeObject, i - 1, j, 1) == true)
					if (ChangeObject.arr[i - 1][j] == symbol)
						++counter;
				if (check(ChangeObject, i + 1, j, 1) == true)
					if (ChangeObject.arr[i + 1][j] == symbol)
						++counter;
				if (check(ChangeObject, i - 1, j - 1, 1) == true)
					if (ChangeObject.arr[i - 1][j - 1] == symbol)
						++counter;
				if (check(ChangeObject, i + 1, j + 1, 1) == true)
					if (ChangeObject.arr[i + 1][j + 1] == symbol)
						++counter;
				if (check(ChangeObject, i - 1, j + 1, 1) == true)
					if (ChangeObject.arr[i - 1][j + 1] == symbol)
						++counter;
				if (check(ChangeObject, i + 1, j - 1, 1) == true)
					if (ChangeObject.arr[i + 1][j - 1] == symbol)
						++counter;

				if (counter == 3 && object.arr[i][j] == ' ')
					object.arr[i][j] = symbol;
				if ((counter < 2 || counter > 3) && object.arr[i][j] == symbol)
					object.arr[i][j] = ' ';
				counter = 0;
			}
}


bool Universe::check(Map object, int x, int y, int status)
{
	int s1 = 0, s2 = 0;
	object.getsize(s1, s2);
	if ((x < 0 || y < 0 || x >= s1 || y >= s2) && status == 1)
		return false;
	else return true;
}

void Universe::test()
{
	setlocale(LC_ALL, "Rus");
	int a = 20, b = 40;
	Map A(a, b);
	char button = ' ';
	int letter = 0;
	
	while (1)
	{
		if (letter == 0)
			cout << "Ќажмите z, дл€ ввода данных(координаты клеток),\nh - координаты дыр;\n»ли r дл€ рандомного расставлени€ координат и количества\ny - чтобы убрать данную надпись, k - чтобы вернуть";
		A.newshow();
		NewBirthAndDeath(A);
		button = (char)_getch();
		buttons(A, button);
		if (button == 'y')
			letter = 1;
		if (button == 'k')
			letter = 0;
		system("cls");
	}
}

















//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <random>
//#include <ctime>
//#include <conio.h>
//#include "Universe.h"
//
//
//using namespace std;
//
//const int UniverseSize = 25; //размер сетки
//
//void printUniverse(bool Universe1[UniverseSize + 1][UniverseSize + 1]);
//void determineState(bool Universe1[UniverseSize + 1][UniverseSize + 1]); //определение положени€ клетоk
//
//int main()
//{
//	srand(time(NULL));
//	bool Universe1[UniverseSize + 1][UniverseSize + 1] = {};
//	int x, y, n;
//	//string nc, start;
//
//	/*cout << "Enter the number of cells, or 'r' for the entry of random cells: ";
//	cin >> nc;
//	cout << endl;*/
//
//	/*if (nc == "r")
//	{*/
//	int kol = 100;
//	//cout << "input number of random cells: ";
//	//cin >> kol;
//	for (int i = 0; i < kol; i++)
//	{
//		x = rand() % 24;
//		y = rand() % 24;
//		Universe1[x][y] = true;
//	}
//	printUniverse(Universe1);
//	//}
//
//	//else
//	//{
//	//	for (int i = 0; i < stoi(nc); i++) //распознавание координат, введенных пользователем
//	//	{
//	//		cout << stoi(nc) << "Enter the coordinates of cell " << i + 1 << " : ";
//	//		cin >> x >> y;
//	//		Universe1[x][y] = true;
//	//		printUniverse(Universe1);
//	//	}
//	//}
//	/*cout << "Start the game ? (y/n)" << endl;
//	cin >> start;
//	if (start == "y" || start == "Y")
//	{*/
//	while (true)
//	{
//		printUniverse(Universe1);
//		determineState(Universe1);
//		system("cls");
//	}
//	//}
//
//
//
//
//	_getch();
//}
//
//void printUniverse(bool Universe1[UniverseSize + 1][UniverseSize + 1]) { //процесс создани€ вселенной с живыми/мертвыми клетками
//	for (int a = 1; a < UniverseSize; a++)
//	{
//		for (int b = 1; b < UniverseSize; b++)
//		{
//			if (Universe1[a][b] == true)
//			{
//				cout << " O "; //оживша€ клетка
//			}
//			else
//			{
//				cout << " . ";//мертва€ клетка
//			}
//			if (b == UniverseSize - 1)
//			{
//				cout << endl;
//			}
//		}
//	}
//}
//
//
//
//void determineState(bool Universe1[UniverseSize + 1][UniverseSize + 1]) { // происходит определение мертвых и живых точек; процедура рождени€ и смерти клеток
//	bool Universe2[UniverseSize + 1][UniverseSize + 1] = {};
//
//	for (int a = 0; a < UniverseSize; a++)
//	{
//		for (int b = 0; b < UniverseSize; b++)
//		{
//			Universe2[a][b] = Universe1[a][b];
//		}
//	}
//
//	for (int a = 1; a < UniverseSize; a++)//оживление клеток 
//	{
//		for (int b = 1; b < UniverseSize; b++)
//		{
//			int alive = 0;
//			for (int c = -1; c < 2; c++)
//			{
//				for (int d = -1; d < 2; d++)
//				{
//					if (!(c == 0 && d == 0))
//					{
//						if (Universe2[a + c][b + d])
//						{
//							++alive;
//						}
//					}
//				}
//			}
//			if (alive < 2) //если вокруг живых клеток меньше 2, то она умирает
//			{
//				Universe1[a][b] = false;
//			}
//			else if (alive == 3) //если вокруг три живые клетки, то живет 
//			{
//				Universe1[a][b] = true;
//			}
//			else if (alive > 3)// если вокруг живых - больше трех, то клетка умирает
//			{
//				Universe1[a][b] = false;
//			}
//		}
//	}
//}
