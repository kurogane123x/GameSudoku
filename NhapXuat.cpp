/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#include "NhapXuat.h"

//Hàm đọc Sudoku và số lượng ô trống từ file. Thành công trả về ma trận Sudoku đọc được, ngược lại trả về NULL.
int** ReadSudoku(const char *Filename, int *Blank)
{
	FILE *fp = fopen(Filename, "r");

	if (fp != NULL)
	{
		int **Sudoku = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));

		if (Sudoku != NULL)
		{
			*Blank = 0;

			for (int i = 0; i < SQ_SIZE; i++)
			{
				fscanf(fp, "%d", (*(Sudoku + i / MATRIX_SIZE) + i % MATRIX_SIZE));

				if (Sudoku[i / MATRIX_SIZE][i % MATRIX_SIZE] == 0)
				{
					++(*Blank);
				}
			}
		}

		fclose(fp);
		return Sudoku;
	}
	
	return NULL;
}

//Hàm đọc Sudoku với ô Sudoku có sẵn không cần tại mới và số lượng ô trống từ file.
void ReadSudoku_C2(const char *Filename, int **Sudoku,  int *Blank)
{
	FILE *fp = fopen(Filename, "r");

	if (fp != NULL)
	{
		if (Sudoku != NULL)
		{
			*Blank = 0;

			for (int i = 0; i < SQ_SIZE; i++)
			{
				fscanf(fp, "%d", (*(Sudoku + i / MATRIX_SIZE) + i % MATRIX_SIZE));

				if (Sudoku[i / MATRIX_SIZE][i % MATRIX_SIZE] == 0)
				{
					++(*Blank);
				}
			}
		}

		fclose(fp);
	}
}

//Hàm ghi Sudoku (Đã giải hoặc trong tùy chọn tính năng lưu lưới) ra file. Thành côn trả về SUCCESS, ngược lại trả về FAIL.
STATUS WriteSudoku(const char *Filename, int **Sudoku)
{
	if (Sudoku != NULL)
	{
		FILE *fp = fopen(Filename, "w");

		if (fp != NULL)
		{
			for (int i = 0; i < MATRIX_SIZE; i++)
			{
				for (int j = 0; j < MATRIX_SIZE; j++)
				{
					fprintf(fp, "%d ", Sudoku[i][j]);
				}

				fprintf(fp, "\n");
			}

			fclose(fp);
			return SUCCESS;
		}
	}

	return FAIL;
}

//Hàm ghi Sudoku (Sudoku được tạo ra để chơi) ra file. Thành công trả về SUCCESS, ngược lại trả về FAIL.
STATUS WriteGenerateSudoku(const char *Filename, int **Sudoku)
{
	if (Sudoku != NULL)
	{
		FILE *fp = fopen(Filename, "w");

		if (fp != NULL)
		{
			for (int i = 0; i < MATRIX_SIZE; i++)
			{
				for (int j = 0; j < MATRIX_SIZE; j++)
				{
					if (Sudoku[i][j] != 0)
					{
						Sudoku[i][j] = Sudoku[i][j] * 11;
					}

					fprintf(fp, "%d ", Sudoku[i][j]);
				}

				fprintf(fp, "\n");
			}

			fclose(fp);
			return SUCCESS;
		}
	}

	return FAIL;
}

//Hàm đọc file text và hiển thị  ra màn hình.
void ReadTXT(const char *Filename)
{
	char s[100];
	FILE *fp = fopen(Filename, "rb");

	if (fp != NULL)
	{
		int Num;
		while (!feof(fp))
		{
			Num = fread(s, 1, 99, fp);
			s[Num] = '\0';
			printf("%s", s);
		}

		printf("\n");

		fclose(fp);
	}
}

//Hàm lựa chọn các chức năng.
int ChooseMenu()
{
	char c;
	int Choice = 0; //Lựa chọn.
	srand(time(NULL));

	while (1)
	{
		PrintMENU();
		PrintInstruction_01(38, 12);

		textColor(14);
		gotoXY(43, 8);
		printf("NEW GAME");
		gotoXY(75, 8);
		printf("CONTINUE");
		gotoXY(43, 9);
		printf("CREATE SUDOKU");
		gotoXY(75, 9);
		printf("SOLVE SUDOKU");
		gotoXY(43, 10);
		printf("INTRODUCE");
		gotoXY(75, 10);
		printf("EXIT");

		if (Choice < 0)
		{
			Choice = 0;
		}

		switch (Choice)
		{
			case 0:
			{
				gotoXY(43, 8);
				PrintStrColor(1 + rand() % 15, "NEW GAME");
				break;
			}
			case 1:
			{
				gotoXY(75, 8);
				PrintStrColor(1 + rand() % 15, "CONTINUE");
				break;
			}
			case 2:
			{
				gotoXY(43, 9);
				PrintStrColor(1 + rand() % 15, "CREATE SUDOKU");
				break;
			}
			case 3:
			{
				gotoXY(75, 9);
				PrintStrColor(1 + rand() % 15, "SOLVE SUDOKU");
				break;
			}
			case 4:
			{
				gotoXY(43, 10);
				PrintStrColor(1 + rand() % 15, "INTRODUCE");
				break;
			}
			case 5:
			{
				gotoXY(75, 10);
				PrintStrColor(1 + rand() % 15, "EXIT");
				break;
			}
		}

		if (GetAsyncKeyState(VK_UP))
		{
			c = getch();
			c = getch();

			Choice = (Choice - 2) % 6;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			c = getch();
			c = getch();

			Choice = (Choice + 2) % 6;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			c = getch();
			c = getch();

			Choice = (Choice - 1) % 6;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			c = getch();
			c = getch();

			Choice = (Choice + 1) % 6;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			c = getch();

			Beep(3000, 10);
			ClearScreen(0, 0);
			return Choice + 1;
		}

		Sleep(300);
		ClearScreen(0, 0);
	}

	textColor(15);
}

//Hàm in ma trận ra màn hình.
void PrintMatrix(int **Matrix, int Row, int Col, int x, int y)
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			gotoXY(x + j * 4, y + i * 2);
			if (Matrix[i][j] > 9)
			{
				textColor(12);
				printf("%d", Matrix[i][j] % 10);
				textColor(15);
			}
			else
			{
				if (Matrix[i][j] > 0)
				{
					printf("%d", Matrix[i][j]);
				}
				else
				{
					if (Matrix[i][j] < 0)
					{
						textColor(11);
						printf("%d", abs(Matrix[i][j]));
						textColor(15);
					}
				}
			}
		}
	}

	gotoXY(1, 24);
}

//Hàm in các chức năng trong khi chơi.
void PrintFeature(int x, int y)
{
	textColor(15);
	gotoXY(x, y);
	printf("Press key below to choose feature you want:");
	gotoXY(x, y + 1);
	printf("N: Create new Sudoku");
	gotoXY(x, y + 2);
	printf("H: Hint a value");
	gotoXY(x, y + 3);
	printf("C: Check a fail value");
	gotoXY(x, y + 4);
	printf("F: Fill all value");
	gotoXY(x, y + 5);
	printf("S: Save game");
	gotoXY(x, y + 6);
	printf("E: Exit");

	gotoXY(x, y + 8);
	printf("Tips: Use arrow keys move to the position you want.");
	gotoXY(x, y + 9);
	printf("Use number key and 6 character key above to play game.");
}

//Hàm in độ khó để lựa chọn.
DIFFICULT_LV ChooseDiffLV()
{
	char c;
	int Choice = 0;
	srand(time(NULL));

	while (1)
	{
		textColor(15);
		gotoXY(52, 1);
		printf("CHOOSE THE DIFFICULT LEVEL");
		gotoXY(58, 3);
		printf("EXTREMELY EASY");
		gotoXY(63, 4);
		printf("EASY");
		gotoXY(62, 5);
		printf("MEDIUM");
		gotoXY(63, 6);
		printf("HARD");

		if (Choice < 0)
		{
			Choice = 0;
		}

		switch (Choice)
		{
			case 0:
			{
				gotoXY(58, 3);
				PrintStrColor(1 + rand() % 15, "EXTREMELY EASY");
				break;
			}
			case 1:
			{
				gotoXY(63, 4);
				PrintStrColor(1 + rand() % 15, "EASY");
				break;
			}
			case 2:
			{
				gotoXY(62, 5);
				PrintStrColor(1 + rand() % 15, "MEDIUM");
				break;
			}
			case 3:
			{
				gotoXY(63, 6);
				PrintStrColor(1 + rand() % 15, "HARD");
				break;
			}
		}

		if (GetAsyncKeyState(VK_UP))
		{
			c = getch();
			c = getch();
			Choice = (Choice - 1) % 4;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			c = getch();
			c = getch();
			Choice = (Choice + 1) % 4;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			c = getch();

			Beep(3000, 10);
			ClearScreen(0, 0);
			switch (Choice)
			{
				case 0:
				{
					return EXTREMELY_EASY;
				}
				case 1:
				{
					return EASY;
				}
				case 2:
				{
					return MEDIUM;
				}
				case 3:
				{
					return HARD;
				}
			}
		}

		Sleep(250);
		ClearScreen(0, 0);
	}
}

//Hàm lựa chọn hướng dẫn hay giới thiệu game.
int ChooseIntro(int x, int y)
{
	char c;
	int Choice = 0;
	srand(time(NULL));

	while (1)
	{
		gotoXY(x, y);
		printf("Choose your choice:");
		gotoXY(x + 6, y + 1);
		printf("GUIDE");
		gotoXY(x + 3, y + 2);
		printf("INTRODUCTION");

		if (Choice < 0)
		{
			Choice = 0;
		}

		switch (Choice)
		{
			case 0:
			{
				gotoXY(x + 6, y + 1);
				PrintStrColor(1 + rand() % 15, "GUIDE");
				break;
			}
			case 1:
			{
				gotoXY(x + 3, y + 2);
				PrintStrColor(1 + rand() % 15, "INTRODUCTION");
				break;
			}
		}

		if (GetAsyncKeyState(VK_UP))
		{
			c = getch();
			c = getch();
			Choice = (Choice - 1) % 2;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			c = getch();
			c = getch();
			Choice = (Choice + 1) % 2;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			c = getch();

			Beep(3000, 10);
			ClearScreen(0, 0);
			return Choice;
		}

		Sleep(250);
		ClearScreen(0, 0);
	}
}

//Hàm lựa chọn giải Sudoku thông thường hay Sudoku đường xuyên.
int ChooseSolve(int x, int y)
{
	int Choice = 0;
	srand(time(NULL));
	char c;

	while (1)
	{
		gotoXY(x, y);
		printf("Choose your type of Sudoku:");
		gotoXY(x + 6, y + 2);
		printf("NORMAL SUDOKU");
		gotoXY(x + 6, y + 3);
		printf("CROSS SUDOKU");

		if (Choice < 0)
		{
			Choice = 0;
		}

		switch (Choice)
		{
			case 0:
			{
				gotoXY(x + 6, y + 2);
				PrintStrColor(1 + rand() % 15, "NORMAL SUDOKU");
				break;
			}
			case 1:
			{
				gotoXY(x + 6, y + 3);
				PrintStrColor(1 + rand() % 15, "CROSS SUDOKU");
				break;
			}
		}

		if (GetAsyncKeyState(VK_UP))
		{
			c = getch();
			c = getch();
			Choice = (Choice - 1) % 2;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			c = getch();
			c = getch();
			Choice = (Choice + 1) % 2;
			Beep(3000, 10);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			c = getch();

			Beep(3000, 10);
			ClearScreen(0, 0);
			return Choice;
		}

		Sleep(250);
		ClearScreen(0, 0);
	}
}

//Hàm cho người chơi nhập vào chuỗi tọa độ ô hoặc phím chức năng để xử lý.
void CommandInput(char *Notification, char **Command, char KyTuDung)
{
	int n = 0;
	*Command = (char *)malloc((n + 1) * sizeof(char));

	if (*Command != NULL)
	{
		char ch;
		printf("%s: ", Notification);
		fflush(stdin);
		while ((ch = getchar()) != KyTuDung && ch != EOF)
		{
			*Command = (char *)realloc(*Command, (n + 1) * sizeof(char));
			*(*Command + n) = ch;
			++n;
		}

		*Command = (char *)realloc(*Command, (n + 1) * sizeof(char));
		*(*Command + n) = '\0';
	}
}

/*Hàm nhập vào giá trị của ô muốn chọn.
Nếu người dùng nhập sai thì chương trình sẽ yêu cầu nhập lại.
*/
void ValueInput(int *Value)
{
	while (1)
	{
		printf("Please enter the value you wanna fill: ");
		scanf("%d", Value);

		if (*Value < 1 || *Value > MATRIX_SIZE)
		{
			ClearScreen(0, 30);
			printf("ERROR. Please enter the value between [1, %d].\n", MATRIX_SIZE);
		}
		else
		{
			break;
		}
	}
}