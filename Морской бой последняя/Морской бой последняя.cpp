
#include "Func.h"
#include "Header.h"

int main() 
{
	
	Set_Size();
	RemoveCursor(100 , true);
	setlocale(LC_ALL, "Russian"); 
	srand(time(NULL)); 
	char variant[2][52] = { "АВТОМАТИЧЕСКАЯ РАССТАНОВКА","РУЧНАЯ РАССТАНОВКА" };
	int ship_pos[12][24] = { 0 }; 
	int enemy_ship_pos[12][24] = { 0 }; 
	
	Ships* characteristic = new Ships[20]; 
	LoadCharactShips(characteristic); 
	int key = 1, y = 2, x = 2, num = 0, change = 1, A = 0, xx = 37, yy = 2, up = 0, down = 0, over = 0;
	bool manual_placement = true, your_turn = 0 + rand() % 2, start = false; 
	
	Avake(); 
	Draw();
	Sleep(2000); 
	system("cls");
	Start_Menu();	
	setColor(White, Black); 

	CreatField(1, 0, 9); 
	
	do 
	{
		HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE); // дескриптор окна для работы с мышкой
		SetConsoleMode(h_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // установка режима использования мышки
		INPUT_RECORD all_events[256]; // здесь хранятся все события, произошедшие в консоли
		DWORD read_event; // переменная, в которую запишется количество произошедших событий
		
		setColor(White, DarkGray);
		int count = 0;
		
		for (int i = 0; i < 2; i++)
		{
			SetCursor(40, 5 + count);
			setColor(White, DarkGray);
			for (int j = 0; j < 40; j++)
			{
				cout << variant[i][j];
			}
			count = 2;
			cout << "\n";
		}
		
		bool m = true;
		while (m == 1)
		{
			ReadConsoleInput(h_in, all_events, 256, &read_event);
			for (int i = 0; i < read_event; i++)
			{
				if (m == false)
				{

					break;
				}
				if (all_events[i].EventType == MOUSE_EVENT)
				{
					auto event = all_events[i].Event.MouseEvent;
					for (int k = 0; k < 16; k++)
					{

						if ((event.dwMousePosition.X == 40 + k ||
							event.dwMousePosition.X == 41 + k) &&
							event.dwMousePosition.Y == 5)
						{
							SetCursor(40, 5);
							setColor(White, Red);
							for (int i = 0; i < 1; i++)
							{
								
								
								for (int j = 0; j < 40; j++)
								{
									cout << variant[i][j];
								}
								cout << "\n";
							}
							Sleep(300);
						}
						else
						{
							SetCursor(40, 5);
							setColor(White, DarkGray);
							for (int i = 0; i < 1; i++)
							{
								
								for (int j = 0; j < 40; j++)
								{
									cout << variant[i][j];
								}
								cout << "\n";
							}
						}
						if ((event.dwMousePosition.X == 40 + k ||
							event.dwMousePosition.X == 41 + k) &&
							event.dwMousePosition.Y == 5 &&
							event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							manual_placement = false; //автоматическая расстанвкоа
							A++; 
							SetCursor(40, 5);
							setColor(White, Red);
							for (int j = 0; i < 1; j++)
							{
								for (int j = 0; j < 40; j++)
								{
									cout << variant[i][j];
								}
							}
							cout << "\n";
							m = false;
							break;

						}

						if ((event.dwMousePosition.X == 40 + k ||
							event.dwMousePosition.X == 41 + k) &&
							event.dwMousePosition.Y == 7)
						{
							
							for (int i = 0; i < 1; i++)
							{
								SetCursor(40, 7 + i);
								setColor(White, Red);
								
								for (int j = 0; j < 40; j++)
								{
									cout << variant[i + 1][j];
								}
								cout << "\n";
							}
							Sleep(300);
						}
						else
						{
							
							for (int i = 0; i < 1; i++)
							{
								SetCursor(40, 7 + i);
								setColor(White, DarkGray);
								for (int j = 0; j < 40; j++)
								{
									cout << variant[i + 1][j];
								}
								cout << "\n";
							}
						}
						if ((event.dwMousePosition.X == 40 + k ||
							event.dwMousePosition.X == 41 + k) &&
							event.dwMousePosition.Y == 7 &&
							event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						{
							manual_placement = true; //ручная расстановка
							A++;
							
							
							for (int j = 0; j < 40; j++)
							{
								SetCursor(40, 7 + i);
								setColor(White, Red);
								cout << variant[i + 1][j];
							}
							cout << "\n";
							m = false;
							break;
						}


					}
				}
			}
		}
	
	} while (A < 1);
	
	setColor(White, Black);
	system("cls");
	

	CreatField(0, 0, 8); 
	Menu();
	x = 2, y = 2;
	
	
	if (manual_placement == false) //если выбрана автоматическая расстановка
		{
			auto_arrangement(characteristic, ship_pos, 0); 
			PaintPos(ship_pos, 2, 0); 
			start = true;
		}
		
	
	
	else if (manual_placement == true && num < 10) //ручная расстановка
	{
		do 
		{
			PaintPos(ship_pos, 2, 0); 
			SetCursor(x, y); 
			setColor(Black, Black); 
			if (characteristic[num].horizontal == true) 
			{
				for (size_t i = 0; i < characteristic[num].deck; i++) 
				{
					cout << "++"; 
				}
			}
			else if (characteristic[num].horizontal == false)
			{
				y += characteristic[num].deck; 
				for (size_t i = 0; i < characteristic[num].deck; i++)  
				{
					cout << "++";
					y--; 
					SetCursor(x, y);

				}
			}
			key = _getch();
			switch (key) 
			{
			case Esc:
			{
				int answer;
				setColor(White, Black);
				answer = MessageBoxA(0, "Вы уверенны?", "Выход", MB_YESNO);
				if (answer == IDYES)
				{
					system("cls");
					setColor(White, Black);
					AnimationShipX1(rand() % 60, rand() % 40, 200);
					AnimationShipX2(rand() % 60, rand() % 40, 200);
					system("cls");
					exit(0);
				}
				else
				{
					setColor(Black, Black);
					system("cls");
					main();
					exit(0);
				}

			}
			case Left:
			{

				if (x > 3) 
				{
					x -= 2; 
				}
				break;
			}
			case Right: 
			{

				if (characteristic[num].horizontal == true) 
				{
					if (x < 22 - characteristic[num].deck * 2) 
					{
						x += 2; 
					}
				}
				else  
				{
					if (x < 20) 
					{
						x += 2; 
					}
				}
				break; 
			}
			case Up: 
			{

				if (y > 2) 
				{
					y--;  
				}
				break; 
			}
			case Down: 
			{

				if (characteristic[num].horizontal == false) 
				{
					if (y < 12 - characteristic[num].deck) 
					{
						y++;  
					}
				}
				else
				{
					if (y < 11) 
					{
						y++;  
					}
				}
				break; 
			}
			case Q: 
			{

				characteristic[num].horizontal = !characteristic[num].horizontal; 
				if (characteristic[num].horizontal == false && y + characteristic[num].deck >= 13)
					
				{
					y -= y + characteristic[num].deck - 12; 
				}
				else if (characteristic[num].horizontal == true && x + characteristic[num].deck * 2 >= 24)
					
				{
					x -= (x + characteristic[num].deck * 2) - 22; 
				}
				for (size_t i = 0; i < 10 - num; i++) 
				{
					characteristic[num + i].horizontal = characteristic[num].horizontal; 
				}
				break; 
			}

			case Enter: 
			{

				if (characteristic[num].horizontal == true && ship_pos[y - 1][x] == 0 && ship_pos[y - 1][x + characteristic[num].deck * 2 - 2] == 0)
				{
					characteristic[num].x = x + 2, characteristic[num].y = y;
					for (size_t q = 0; q < 3; q++) 
					{
						for (size_t w = 1; w < characteristic[num].deck * 3 + 1; w++)  
						{
							ship_pos[y - 2 + q][x - 3 + w] = 1; 
						}
					}
					for (int g = 0; g < 2 * characteristic[num].deck; g++) 
					{
						ship_pos[y - 1][x + g] = 13 - num;  
					}
					num++; 
				}
				if (characteristic[num].horizontal == false && ship_pos[y - 1][x] == 0 && ship_pos[y + characteristic[num].deck - 2][x] == 0)
				{
					characteristic[num].x = x + 2, characteristic[num].y = y;
					for (size_t q = 0; q < characteristic[num].deck + 2; q++) 
					{
						for (size_t w = 0; w < 6; w++) 
						{
							ship_pos[y - 2 + q][x - 2 + w] = 1; 
						}
					}
					for (int g = 0; g < characteristic[num].deck; g++) 
					{
						for (int n = 0; n < 2; n++) 
						{
							ship_pos[y - 1 + g][x + n] = 13 - num; 
						}
					}
					num++; 
				}
			}
			
			}
			start = true;
			}while (num <= 9);
			
			
		}
	
	Sleep(20);
	CreatField(1, 35, 4); 
	auto_arrangement(characteristic, enemy_ship_pos, 10); 
	PaintPos(enemy_ship_pos, 37, 15); 
	do
	{
		if (your_turn == true) 
		{
			do 
			{
				x = xx, y = yy;
				PaintPos(enemy_ship_pos, 37, 15); 
				setColor(DarkGray, DarkGray); 
				SetCursor(x, y); 
				cout << "++"; 
				key = _getch();
				switch (key) 
				{
				case Esc:
				{
					int answer;
					setColor(White, Black);
					answer = MessageBoxA(0, "Вы уверенны?", "Выход", MB_YESNO);
					if (answer == IDYES)
					{
						system("cls");

						AnimationShipX1(rand() % 60, rand() % 40, 200);
						AnimationShipX2(rand() % 60, rand() % 40, 200);
						system("cls");
						exit(0);
					}
					else
					{
						system("cls");
						setColor(Black, Black);
						main();
					}

				}
				case Left: 
				{

					if (x > 38) 
					{
						x -= 2; 
						xx = x;
					}
					break;
				}
				case Right:
				{

					if (x < 55)
					{
						x += 2;
						xx = x;
					}
					break; 
				}
				case Up:
				{

					if (y > 2) 
					{
						y--;  
						yy = y; 
					}
					break; 
				}
				case Down: 
				{

					if (y < 11) 
					{
						y++;  
						yy = y; 
					}
					break;
				}

				case Enter:
				{

					if (enemy_ship_pos[y - 1][x - 35] >= 4) 
					{
						for (size_t i = 0; i < 2; i++) 
						{
							enemy_ship_pos[y - 1][x - 35 + i] = 3; 
							explosion(characteristic, enemy_ship_pos, 10, over); 
						}
						Meny(9); 
						Sleep(500); 
					}
					else if (enemy_ship_pos[y - 1][x - 35] < 2) 
					{
						for (size_t i = 0; i < 2; i++)
						{
							enemy_ship_pos[y - 1][x - 35 + i] = 2; 
						}
						Sleep(500);
						Meny(5); 
						your_turn = false; 
					}
					break;
				}
				}
			} while (key != Enter); 
		}
		if (your_turn == false)
		{
			Sleep(0 + rand() % 400);
			Meny(0); 
			PaintPos(ship_pos, 2, 0);
			Sleep(0 + rand() % 400); 
			x = (2 + rand() % 10) * 2, y = 2 + rand() % 10; 
			if (ship_pos[y - 1][x - 1] >= 4) 
			{
				for (size_t i = 0; i < 2; i++) 
				{
					ship_pos[y - 1][x - 2 + i] = 3;  
					explosion(characteristic, ship_pos, 0, over);
				}
				Meny(2); 
				Sleep(0 + rand() % 750); 
			}
			else if (ship_pos[y - 1][x - 1] <= 2)  
			{
				for (size_t i = 0; i < 2; i++) 
				{
					ship_pos[y - 1][x - 2 + i] = 2; 
				}
				Meny(1); 
				Sleep(0 + rand() % 750); 
				your_turn = true; 
			}
		}
	} while (over == 0);
	PaintPos(ship_pos, 2, 0);
	PaintPos(enemy_ship_pos, 37, 15); 
	if (over == 2) 
	{
		Meny(7);
	}
	else
	{
		Meny(3);
	}
	Sleep(500000);

}