#include"Header.h"
enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };





void setColor(Color text, Color background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //Дескриптор активного окна
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


enum Napravlenie { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, BackSpace = 8, Q = 81, Esc = 27, Auto = 65, Hand = 72 };


void SetCursor(int x, int y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //Дескриптор активного окна
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}
struct Ships
{
	int deck = { 0 };
	bool horizontal = true;
	bool alive = true;
	int x, y;
};
void explosion(Ships* characteristic, int ship_pos[12][24], int plus, int& end) //уничтожение и определение победителя
{
	int A = 0;
	int B = 13;
	int C = 0;
	bool alive = false;
	for (size_t n = 13; n > 3; n--)
	{
		for (size_t i = 1; i < 11; i++)
		{
			for (size_t r = 2; r < 22; r++)
			{
				if (ship_pos[i][r] == n)
				{
					alive = true;
					i = 11;
					break;
				}
			}
		}
		if (alive == false)
		{
			characteristic[B - n + plus].alive = false;
		}
		else
		{
			alive = false;
		}
	}
	for (size_t i = plus; i < 10 + plus; i++)
	{
		if (i == 0 || i == 10)
		{
			A = 0;
		}
		else if (i == 1 || i == 2 || i == 11 || i == 12)
		{
			A = 1;
		}
		else if (i > 2 && i < 6 || i > 12 && i < 16)
		{
			A = 2;
		}
		else
		{
			A = 3;
		}
		if (characteristic[i].alive == false)
		{
			if (characteristic[i].horizontal == true)
			{
				for (size_t q = 0; q < 3; q++)
				{
					for (size_t w = 0; w < characteristic[i].deck * 3 + A; w++)
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x - 4 + w] = 2;
					}
				}
				for (size_t g = 0; g < 2 * characteristic[i].deck; g++)
				{
					ship_pos[characteristic[i].y - 1][characteristic[i].x - 2 + g] = 3;
				}
			}
			else if (characteristic[i].horizontal == false)
			{
				for (size_t q = 0; q < characteristic[i].deck + 2; q++)
				{
					for (int w = -4; w < 2; w++)
					{
						ship_pos[characteristic[i].y - 2 + q][characteristic[i].x + w] = 2;
					}
				}
				for (int g = 0; g < characteristic[i].deck; g++)
				{
					for (int n = -2; n < 0; n++)
					{
						ship_pos[characteristic[i].y - 1 + g][characteristic[i].x + n] = 3;
					}
				}
			}
			C++; // увеличиваем значение счётчика уничтоженных корабликов на 1
		}
	}
	if (C == 10 && plus == 0) //если все наши кораблики уничтожены
	{
		end = 1; //завершаем игру (поражение)
	}
	else if (C == 10 && plus == 10) //если все кораблики врага уничтожены
	{
		end = 2; //завершаем игру (победа)
	}
	else
	{
		C = 0; //онулдируем счетчик уничтоженных корабликов
	}
}
void LoadCharactShips(Ships* characteristic) //присвоение палуб в соответствии с номером кораблика
{
	for (size_t i = 0; i < 20; i++)
	{
		if (i == 0 || i == 10)
		{
			characteristic[i].deck = 4;
		}
		else if (i > 0 && i <= 2 || i > 10 && i <= 12)
		{
			characteristic[i].deck = 3;
		}
		else if (i > 2 && i <= 5 || i > 12 && i <= 15)
		{
			characteristic[i].deck = 2;
		}
		else if (i > 5 && i <= 9 || i > 15 && i <= 19)
		{
			characteristic[i].deck = 1;
		}
	}
}
void auto_arrangement(Ships* characteristic, int ship_pos[12][24], int plus) //aвтоматическая расстановка корабликов
{
	int y, x, ship = plus; //переменная для координат и номера кораблика 
	while (ship < plus + 10)
	{
		characteristic[ship].horizontal = 0 + rand() % 2;
		y = 2 + rand() % 9, x = (1 + rand() % 9) * 2;
		if (characteristic[ship].horizontal == false && y + characteristic[ship].deck >= 13)

		{
			y -= y + characteristic[ship].deck - 12;
		}
		else if (characteristic[ship].horizontal == true && x + characteristic[ship].deck * 2 >= 24)
			//проверяем заденит ли кораблик границу по вертикале при перевороте, если его не отодвинуть
		{
			x -= (x + characteristic[ship].deck * 2) - 22;
		}
		if (characteristic[ship].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[ship].deck * 2 - 2] == 0)

		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y;
			for (size_t q = 0; q < 3; q++)
			{
				for (size_t w = 1; w < characteristic[ship].deck * 3 + 1; w++)
				{
					ship_pos[y - 2 + q][x - 3 + w] = 1;
				}
			}
			for (int g = 0; g < 2 * characteristic[ship].deck; g++)
			{
				ship_pos[y - 1][x + g] = 13 - ship + plus;
			}
			ship++;
		}
		if (characteristic[ship].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[ship].deck - 2][x] == 0)
			// проверемя имеет ли кораблик горизонтальное положение и нет ли ничего на позициях куда он будет устанавливаться
		{
			characteristic[ship].x = x + 2, characteristic[ship].y = y;
			for (size_t q = 0; q < characteristic[ship].deck + 2; q++)
			{
				for (size_t w = 0; w < 6; w++)
				{
					ship_pos[y - 2 + q][x - 2 + w] = 1;
				}
			}
			for (int g = 0; g < characteristic[ship].deck; g++)
			{
				for (int n = 0; n < 2; n++)
				{
					ship_pos[y - 1 + g][x + n] = 13 - ship + plus;
				}
			}
			ship++; //переходим к следующему кораблику
		}
	}
}
void PaintPos(int mas[12][24], int x, int num_color) //прорисовка игровой карты в соответсвии с положением поставленных корабликов
{
	for (size_t i = 1; i < 11; i++)
	{
		int y = 1 + i;
		SetCursor(x, y);

		for (size_t g = 2; g < 22; g++)
		{
			if (mas[i][g] == 2)
			{
				setColor(LightGray, LightGray);
			}
			else if (mas[i][g] == 3)
			{
				setColor(LightMagenta, LightMagenta);
			}
			else if (mas[i][g] >= 4)
			{
				setColor(Color(num_color), Color(num_color));
			}
			else
			{
				setColor(White, White);
			}
			cout << "+";
		}
		cout << "\n";
	}
}
void Avake()
{
	setColor(White, Cyan);
	SetCursor(24, 10);
	cout << "МОРСКОЙ БОЙ";
}
void SetCursor(int x, int y, Color color, string t)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, color);

	cout << t;
	cout << "\n";
}
void Menu()
{
	SetCursor(10, 18, White, ":Подсказки:\n");
	SetCursor(5, 19, White, "Q - перевернуть кораблик\n");
	SetCursor(5, 20, White, "ESC - Выход из игры\n");
}
void Menu_Color()
{
	SetCursor(10, 0, White, ":Цвета:\n");
	SetCursor(5, 1, White, "1 - Blue\n");
	SetCursor(5, 2, White, "2 - Green\n");
	SetCursor(5, 3, White, "3 - Cyan\n");
	SetCursor(5, 4, White, "4 - Red\n");
	SetCursor(5, 5, White, "5 - Magenta\n");
	SetCursor(5, 6, White, "6 - Brown\n");
	SetCursor(5, 7, White, "7 - Random\n");
	SetCursor(5, 8, White, "8 - Yellow\n");
	SetCursor(5, 9, White, "9 - LightBlue\n");

}
int SetColor()
{
	int num_color = LightCyan;
	int code = _getch();
	switch (code)
	{
	case 49:
	{
		num_color = Blue;
		break;
	}
	case 50:
	{
		num_color = Green;
		break;
	}
	case 51:
	{
		num_color = Cyan;
		break;
	}
	case 52:
	{
		num_color = Red;
		break;
	}
	case 53:
	{
		num_color = Magenta;
		break;
	}
	case 54:
	{
		num_color = Brown;
		break;
	}
	case 55:
	{
		num_color = 1 + rand() % (15 - 1);
		break;
	}
	case 56:
	{
		num_color = Yellow;
		break;
	}
	case 57:
	{
		num_color = LightBlue;
		break;
	}


	}
	return num_color;
}
void Snake();
void CreatField(int speed, int X, int num_color) //Функция благодоря которой будет отрисовываться игровое поле
{

	if (num_color != 9 && num_color != 4)
	{
		Menu_Color();
		num_color = SetColor();
		system("cls");
		Snake();
		setColor(Black, Black);
		system("cls");

	}


	SetCursor(X, 1);
	char mas[15] = { 'А','Б','В','Г','Д','Е','Ж','З','И','К', 'Л', 'М', 'Н', 'О', 'П' };
	setColor(White, Color(num_color));
	int A = 0, B = 0;
	cout << "  " << mas[0];
	for (size_t i = 0; i < 12; i++)
	{
		if (B == 0) //гениальная проврека, которая сработает один раз
		{
			SetCursor(X + 3, 1 + i);
			B++;
		}
		else
		{
			SetCursor(X, 1 + i);
		}
		for (size_t g = 0; g < 23; g++)
		{
			if (i == 0 && g == 22)
			{

				setColor(Color(num_color), Color(num_color));
				Sleep(speed);
				cout << '+';
			}
			if (i == 0 && g > 0 && g < 10)
			{

				setColor(White, Color(num_color));
				Sleep(speed);
				cout << " " << mas[g];
			}
			else if (i > 0 && i < 11 && g == 0)
			{
				setColor(White, Color(num_color));
				if (i < 10)
				{
					Sleep(speed);
					cout << i << ' ';
				}
				else
				{
					Sleep(speed);
					cout << i;
				}
			}
			else if (i == 11 || g > 20 && g < 23)
			{
				if (A == 0 && i == 11)
				{
					Sleep(speed);
					cout << "+";
					A++;
				}
				setColor(Color(num_color), Color(num_color));
				Sleep(speed);
				cout << '+';
			}
			else if (i > 0)
			{
				Sleep(speed);
				setColor(White, White);
				cout << '+';
			}
		}
	}
	setColor(Black, Black);
}

void Meny(int num)
{
	char variant[11][69] = { "ВРАГ ДУМАЕТ КУДА УДАРИТЬ...","ВРАГ ПРОМАЗАЛ!", "ВРАГ ПОПАЛ!", "ВРАГ ПОБЕДИЛ... НЕ ГРУСТИ...", "ТВОЙ ХОД." , "ТЫ ПРОМАЗАЛ...", "ТЫ ПОПАЛ!", "ТЫ ПОБЕДИЛ, ПОЗДРАВЛЯЮ!", "+++++++++++++++++++++++++++++++++++++++", "ТЫ ПОПАЛ, ХОДИ СНОВА!", "ЮХУ, ТЫ УНИЧТОЖИЛ ВРАЖЕСКИЙ КОРАБЛИК!" };

	SetCursor(22, 15);
	setColor(Black, Black);
	for (size_t i = 0; i < 25; i++)
	{
		cout << variant[10][i];
		cout << variant[10][i];
	}
	SetCursor(22, 15);
	if (num > 0 && num < 4)
	{
		setColor(White, Red);
	}
	else
	{
		setColor(White, Green);
	}
	for (size_t i = 0; i < 30; i++)
	{
		cout << variant[num][i];

	}
	Sleep(500);
}
void RemoveCursor(int dwSize, bool bVisible)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);

}
void Draw() {
	setColor(Cyan, Black);
	SetCursor(0, 2); cout << "	  ^v^                    ^v^        ^v^                    ^v^       ";
	SetCursor(0, 3); cout << "              ^ v ^               ^v^                    ^v^                   ^v^ ";
	SetCursor(0, 4); cout << "        ^v^     ";
	SetCursor(0, 5); cout << "^v^                                  ^v^   ^v^                    ^v^      ";
	SetCursor(0, 6); cout << "             ^ v ^         ^v^                    ^v^            ^v^ ";

	SetCursor(0, 5); cout << "     ^v^        ^v^                    ^v^             ^v^ ";

	SetCursor(0, 12); cout << " ..-+*°* -..  ~~~*°*~~~  ..- *°* -.. ..-+*°* -..  ~~~*°*~~~  ..- *°* -..";
	SetCursor(0, 15); cout << "~~~  ..- *°* -..~~~~  ..- *°* -.. ~~~  ..- *°* -..~~~~  ..- *°* -..";
	SetCursor(0, 16); cout << " ..- *~~°* -..  ..- *~~~~°* -.. * -...- *°..- *~~°* -..  ..- *~~~~°* -.. * -...- *°";
	SetCursor(0, 17); cout << " .~*°*~~~~  ..- *~~~~°* -.. *.- *°* -...~*°*~~~~  ..- *~~~~°* -.. *.- *°* -..";
}
void Numbers()
{

	SetCursor(27, 8);
	setColor(White, Black);
	cout << "..Загрузка..";


}
void Snake()
{
	Numbers();
	for (int i = 0; i < 50; i++)
	{
		SetCursor(i + 10, 10);
		setColor(White, White);
		cout << "+";
		Sleep(100);

	}
}
void Set_Size()
{
	HWND hwnd = GetConsoleWindow();
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(hwnd, 0, 0, screen_width - (screen_width / 3), screen_height, true);
}
void AnimationShipX1(int x, int y, int speed)
{


	{
		for (int i = 0; i < 500; i++)
		{
			if (x == 0)
			{
				SetCursor(x, y);
				cout << "                            ";
				SetCursor(x, y + 1);
				cout << "                                       ";
				SetCursor(x, y + 2);
				cout << "                                         ";
				SetCursor(x, y + 3);
				cout << "                                           ";
				continue;

				//break;
			}
			SetCursor(x, y);
			cout << "                 $$$$        ";
			SetCursor(x, y + 1);
			cout << " $$            $$$$$$       $$";
			SetCursor(x, y + 2);
			cout << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$";
			SetCursor(x, y + 3);
			cout << "   $$$$$$$$$$$$$$$$$$$$$$$$$$";
			x--;
			Sleep(speed);
			SetCursor(x - 1, y);
			cout << "                                      ";
			SetCursor(x - 1, y + 1);
			cout << "                                     ";
			SetCursor(x - 1, y + 2);
			cout << "                                  ";
			SetCursor(x - 1, y + 3);
			cout << "                               ";

		}
	}
}
void AnimationShipX2(int x, int y, int speed)
{
	//setColor(White, Black);
	/*int x = rand() % 100;
	int y = rand() % 40;*/
	int screen_width = GetSystemMetrics(SM_CXSCREEN);


	for (int i = 0; i < screen_width - (screen_width / 3); i++)
	{

		SetCursor(x, y);
		cout << "                            ";
		SetCursor(x, y + 1);
		cout << "                                       ";
		SetCursor(x, y + 2);
		cout << "                                         ";
		SetCursor(x, y + 3);
		cout << "                                           ";
		continue;
		//break;
	}
	SetCursor(x, y);
	cout << "           $$$$        ";
	SetCursor(x, y + 1);
	cout << "  $$       $$$$$$            $$";
	SetCursor(x, y + 2);
	cout << "  $$$$$$$$$$$$$$$$$$$$$$$$$$$$";
	SetCursor(x, y + 3);
	cout << "   $$$$$$$$$$$$$$$$$$$$$$$$$$";
	x++;
	Sleep(speed);
	SetCursor(x - 1, y);
	cout << "                                      ";
	SetCursor(x - 1, y + 1);
	cout << "                                     ";
	SetCursor(x - 1, y + 2);
	cout << "                                  ";
	SetCursor(x - 1, y + 3);
	cout << "                               ";



}
void Start_Menu()
{
	HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE); // дескриптор окна для работы с мышкой
	SetConsoleMode(h_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // установка режима использования мышки
	INPUT_RECORD all_events[256]; // здесь хранятся все события, произошедшие в консоли
	DWORD read_event; // переменная, в которую запишется количество произошедших событий
	const char mass[2][13] = { "Играть", "Выход" };
	setColor(White, Black);
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		SetCursor(24, 10 + count);
		setColor(White, DarkGray);
		for (int j = 0; j < 13; j++)
		{
			cout << mass[i][j];
		}
		count = 2;
		cout << "\n";
	}
	//int code = _getch();
	setColor(White, Black);
	AnimationShipX1(90, 25, 200);
	setColor(White, DarkGray);
	bool m = true;
	while (m == 1)
	{
		ReadConsoleInput(h_in, all_events, 256, &read_event);
		for (int i = 0; i < read_event; i++)
		{
			if (m == false)
			{

				return;
			}
			if (all_events[i].EventType == MOUSE_EVENT)
			{
				auto event = all_events[i].Event.MouseEvent;
				for (int k = 0; k < 16; k++)
				{

					if ((event.dwMousePosition.X == 24 + k ||
						event.dwMousePosition.X == 25 + k) &&
						event.dwMousePosition.Y == 10)
					{
						for (int i = 0; i < 1; i++)
						{
							SetCursor(24, 10 + i);
							setColor(White, Red);
							for (int j = 0; j < 13; j++)
							{
								cout << mass[i][j];
							}
							cout << "\n";
						}
						Sleep(300);
					}
					else
					{
						for (int i = 0; i < 1; i++)
						{
							SetCursor(24, 10 + i);
							setColor(White, DarkGray);
							for (int j = 0; j < 13; j++)
							{
								cout << mass[i][j];
							}
							cout << "\n";
						}
					}
					if ((event.dwMousePosition.X == 24 + k ||
						event.dwMousePosition.X == 25 + k) &&
						event.dwMousePosition.Y == 10 &&
						event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						setColor(White, Black); //Устанавливаем цвет текста (белый на голубом)
						system("cls"); //очищяем консоль
						m = false;
						break;

					}

					if ((event.dwMousePosition.X == 24 + k ||
						event.dwMousePosition.X == 25 + k) &&
						event.dwMousePosition.Y == 12)
					{
						for (int i = 0; i < 1; i++)
						{
							SetCursor(24, 12 + i);
							setColor(White, Red);
							for (int j = 0; j < 13; j++)
							{
								cout << mass[i + 1][j];
							}
							cout << "\n";
						}
						Sleep(300);
					}
					else
					{
						for (int i = 0; i < 1; i++)
						{
							SetCursor(24, 12 + i);
							setColor(White, DarkGray);
							for (int j = 0; j < 13; j++)
							{
								cout << mass[i + 1][j];
							}
							cout << "\n";
						}
					}
					if ((event.dwMousePosition.X == 24 + k ||
						event.dwMousePosition.X == 25 + k) &&
						event.dwMousePosition.Y == 12 &&
						event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						setColor(White, Black);
						system("cls");
						m = false;
						exit(0);

					}


				}
			}
		}
	}
}


