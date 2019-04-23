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
		cout << "  Ïîæàëóéñòà, ââåäèòå êîîðäèíàòû: \n  x: ";
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
		cout << "Ââåäèòå êîëè÷åñòâî ðàíäîìíûõ êëåòîê: ";
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
			cout << "Íàæìèòå z, äëÿ ââîäà äàííûõ(êîîðäèíàòû êëåòîê),\nh - êîîðäèíàòû äûð;\nÈëè r äëÿ ðàíäîìíîãî ðàññòàâëåíèÿ êîîðäèíàò è êîëè÷åñòâà\ny - ÷òîáû óáðàòü äàííóþ íàäïèñü, k - ÷òîáû âåðíóòü";
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

