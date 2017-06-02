/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#include "Library.h"

void main()
{
	ResizeConsole(800, 550);

	while (1)
	{
		int Choice = 0;
		Choice = ChooseMenu();
		PlaySoundA("Sound/Theme Song.wav", NULL, SND_LOOP | SND_ASYNC);

		switch (Choice)
		{
			case 1:
			case 2:
			{
				int Blank = 0;
				int ret;
				DIFFICULT_LV Lvl;
				STATUS stt;
				int **Sudoku = NULL;

				if (Choice == 1)
				{
					Lvl = ChooseDiffLV();
					stt = GenerateSudoku("Sudoku.in", Lvl);
					Sudoku = ReadSudoku("Sudoku.in", &Blank);
				}
				else
				{
					Sudoku = ReadSudoku("Sudoku.out", &Blank);
				}

				if (Sudoku != NULL)
				{
					/*
					//Phần này thực hiện nhập tọa độ và chức năng
					while (1)
					{
						if (Blank == 0 && CheckSudoku(Sudoku, MATRIX_SIZE, MATRIX_SIZE) == true)
						{
							ClearScreen(0, 0);
							printf("CONGRATULATION!!!\n");
							Sleep(3000);
							break;
						}

						PrintSUDOKU();
						PrintGrid(20, 8);
						PrintMatrix(Sudoku, MATRIX_SIZE, MATRIX_SIZE, 24, 10);
						PrintFeature(65, 8);

						ret = CommandControl(Sudoku, MATRIX_SIZE, MATRIX_SIZE, &Blank);

						if (ret == 0)
						{
							ClearScreen(0, 0);
							break;
						}

						Sleep(500);
						ClearScreen(0, 0);
					}*/


					Control(Sudoku, MATRIX_SIZE, MATRIX_SIZE, &Blank);

					Destroy((void **)Sudoku);
				}

				break;
			}
			case 3:
			{
				DIFFICULT_LV Lvl = ChooseDiffLV();
				char *Filename = NULL;
				CommandInput("Please enter the file's name output or link", &Filename);
				ClearScreen(0, 0);

				if (Filename != NULL)
				{
					if (GenerateSudoku_(Filename, Lvl) == SUCCESS)
					{
						ClearScreen(0, 0);
						printf("GENERATED SUCCESSFULLY!\n");
						Sleep(2000);
						ClearScreen(0, 0);
					}
					else
					{
						printf("REQUEST TIME OUT or LOW OF MEMORY!\nPLEASE TRY AGAIN!\n");
					}

					free(Filename);
				}

				return;
			}
			case 4:
			{
				int Choice = ChooseSolve(49, 5);
				char *Filename = NULL;
				CommandInput("Please enter the file's name input or link", &Filename);
				ClearScreen(0, 0);

				if (Filename != NULL)
				{
					int Blank = 0;
					int **Sudoku;
					Sudoku = ReadSudoku(Filename, &Blank);

					if (Sudoku != NULL)
					{
						if (Choice == 0)
						{

							Blank = 0;
							SolveSudoku_ManySolution(Sudoku, &Blank);
						}
						else
						{
							int *Index = FindCross(Sudoku, MATRIX_SIZE, MATRIX_SIZE);
							SolveSudoku_(Sudoku, Index, MATRIX_SIZE, MATRIX_SIZE);
							free(Index);
						}

						Destroy((void **)Sudoku);
					}
					else
					{
						ClearScreen(0, 0);
						printf("LOW OF MEMORY!\nPLEASE TRY AGAIN!\n");
					}

					free(Filename);
				}
				else
				{
					ClearScreen(0, 0);
					printf("LOW OF MEMORY!\nPLEASE TRY AGAIN!\n");
				}

				system("pause");
				return;
			}
			case 5:
			{
				int Choice = ChooseIntro(55, 1);

				if (Choice == 0)
				{
					ReadTXT("Introduce/Guide.txt");
				}
				else
				{
					ReadTXT("Introduce/Intro.txt");
				}

				printf("Press C to continue...");
				char c = getch();
				ClearScreen(0, 0);
				break;
			}
			case 6:
			{
				exit(0);
			}
			default:
			{
				break;
			}
		}
	}
}