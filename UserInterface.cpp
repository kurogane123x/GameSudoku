/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#include "UserInterface.h"

//Hàm thay đổi kích thước khung cmd.
void ResizeConsole(int Width, int Height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, Width, Height, true);
}

//Hàm tô màu ký tự.
void textColor(int Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

//Hàm di chuyển đến tọa độ x, y.
void gotoXY(int x, int y)
{
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor_an_Pos);
}

//Hàm xóa màn hình từ điểm có tọa độ x, y trở xuống.
void ClearScreen(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	int X = x, Y = y;
	if (x > 0)
	{
		X = x - 1;
	}
	if (y > 0)
	{
		Y = y - 1;
	}

	COORD	Home = { X, Y };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

//Hàm in chuỗi với màu nhất định và không đổi màu của các chuỗi khác.
void PrintStrColor(int Color, char *s)
{
	textColor(Color);
	printf("%s\n", s);
	textColor(14);
}

//Hàm in thông tin liên hệ.
void Contact(int x, int y)
{
	textColor(13);
	gotoXY(x, y);
	printf("Product by Vo Sy Lien Thanh.");
	gotoXY(x, y + 1);
	printf("Contact:");
	gotoXY(x, y + 2);
	printf("Email: vosylienthanh@gmail.com");
	gotoXY(x, y + 3);
	printf("Phone: 01642819291\n");
	textColor(15);
}

//Hàm xuất ra MENU kiểu.
void PrintMENU()
{
	textColor(12);
	gotoXY(40, 1);
	printf("|_|       |_|  |_|_|_|_|  |_|      |_|  |_|    |_|\n");
	gotoXY(40, 2);
	printf("|_|_|   |_|_|  |_|        |_|_|    |_|  |_|    |_|\n");
	gotoXY(40, 3);
	printf("|_|  |_|  |_|  |_|_|_|    |_|  |_| |_|  |_|    |_|\n");
	gotoXY(40, 4);
	printf("|_|       |_|  |_|        |_|    |_|_|  |_|    |_|\n");
	gotoXY(40, 5);
	printf("|_|       |_|  |_|_|_|_|  |_|      |_|    |_||_|\n");
	gotoXY(40, 6);
	printf("==================================================\n\n");
	gotoXY(40, 13);
	printf("==================================================");
	Contact(50, 14);
}

//Hàm in chữ SUDOKU kiểu.
void PrintSUDOKU()
{
	textColor(12);
	gotoXY(35, 1);
	printf("  _|_|_|  _|    _|  _|_|_|      _|_|    _|    _|  _|    _|\n");
	gotoXY(35, 2);
	printf("_|        _|    _|  _|    _|  _|    _|  _|  _|    _|    _|\n");
	gotoXY(35, 3);
	printf("  _|_|    _|    _|  _|    _|  _|    _|  _|_|      _|    _|\n");
	gotoXY(35, 4);
	printf("      _|  _|    _|  _|    _|  _|    _|  _|  _|    _|    _|\n");
	gotoXY(35, 5);
	printf("_|_|_|      _|_|    _|_|_|      _|_|    _|    _|    _|_|\n");
	gotoXY(35, 6);
	PrintCharacter('=', 58, true);
	textColor(14);
}

//Hàm in ký tự n lần.
void PrintCharacter(char Ch, int Times, bool NewLine)
{
	for (int i = 0; i < Times; i++)
	{
		printf("%c", Ch);
	}

	if (NewLine)
	{
		printf("\n");
	}
}

//Hàm tạo lưới ô vuông.
void PrintGrid(int x, int y)
{
	textColor(15);
	for (int i = 0; i < 9; i++)
	{
		gotoXY(x + 4 + i * 4, y);
		printf("%c", 'A' + i);
	}
	++y; //Xuống dòng.
	gotoXY(x + 2, y);
	//In dòng đầu.
	printf("%c", 218);
	for (int i = 0; i < 17; i++)
	{
		if (i % 2 == 0)
		{
			PrintCharacter(196, 3);
		}
		else
		{
			printf("%c", 194);
		}
	}
	printf("%c\n", 191);
	++y;

	//In những dòng giữa.
	for (int i = 0; i < 17; i++)
	{
		if (i % 2 == 0)
		{
			gotoXY(x, y);
			printf("%d ", 1 + i / 2);

			for (int j = 0; j < 19; j++)
			{
				if (j % 2 == 0)
				{
					printf("%c", 179);
				}
				else
				{
					PrintCharacter(32, 3);
				}
			}

			printf("\n");
			++y;
		}
		else
		{
			gotoXY(x + 2, y);
			printf("%c", 195);

			for (int j = 0; j < 17; j++)
			{
				if (j % 2 == 0)
				{
					PrintCharacter(196, 3);
				}
				else
				{
					printf("%c", 197);
				}
			}

			printf("%c\n", 180);
			++y;
		}
	}

	//In dòng cuối.
	gotoXY(x + 2, y);
	printf("%c", 192);
	for (int i = 0; i < 17; i++)
	{
		if (i % 2 == 0)
		{
			PrintCharacter(196, 3);
		}
		else
		{
			printf("%c", 193);
		}
	}
	printf("%c\n", 217);
}

//Hàm in hướng dẫn lựa chọn trong menu chính.
void PrintInstruction_01(int x, int y)
{
	gotoXY(x, y);
	printf("Tips: Use arrow buttons to move. Press ENTER to select.");
}