/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#include "XuLy.h"

//Hàm cấp phát ma trận. Thành công trả về ma trận đã cấp phát, thất bại trả về NULL.
void** Alloc(int Row, int Col, int Size)
{
	void **Matrix = (void **)malloc(Row * sizeof(void *));
	if (Matrix == NULL)
	{
		return NULL;
	}

	void *Buffer = calloc(Row * Col, Size);
	if (Buffer == NULL)
	{
		free(Matrix);
		return NULL;
	}

	for (int i = 0; i < Row; i++)
	{
		Matrix[i] = (char *)Buffer + i * Col * Size;
	}

	return Matrix;
}

//Hàm giải phóng ma trận.
void Destroy(void **Matrix)
{
	if (Matrix != NULL)
	{
		if (Matrix[0] != NULL)
		{
			free(Matrix[0]);
		}

		free(Matrix);
	}
}

//Hàm kiểm tra số có phù hợp để đưa vào ô hay không. Nếu phù hợp trả về true, ngược lại trả về false.
bool CheckCandidate(int **Sudoku, int Row, int Col, int Value)
{
	//Vị trí ô góc trái bên trên của vùng đang xét.
	int Index = (Row / BOX) * BOX * MATRIX_SIZE + (Col / BOX) * BOX;

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (Sudoku[Row][i] % 10 == Value || Sudoku[i][Col] % 10 == Value || Sudoku[Index / MATRIX_SIZE + i / BOX][Index % MATRIX_SIZE + i % BOX] % 10 == Value)
		{
			return false;
		}
	}

	return true;
}

//Hàm kiểm tra một số có hợp lệ hay không.
bool CheckValid(int **Sudoku, int Row, int Col, int Value)
{
	//Vị trí ô góc trái bên trên của vùng đang xét.
	int Index = (Row / BOX) * BOX * MATRIX_SIZE + (Col / BOX) * BOX;

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if ((i != Col && Sudoku[Row][i] % 10 == Value) || (i != Row && Sudoku[i][Col] % 10 == Value) || (Index / MATRIX_SIZE + i / BOX != Row && Index % MATRIX_SIZE + i % BOX != Col && Sudoku[Index / MATRIX_SIZE + i / BOX][Index % MATRIX_SIZE + i % BOX] % 10 == Value))
		{
			return false;
		}
	}

	return true;
}

//Hàm giải Sudoku (Chỉ giải nhiều nhất 2 trường hợp).
void SolveSudoku(int **Sudoku, int **Solution, int *Count, int Row, int Col)
{
	if (Col == 9) //Nếu như đã điền xong cột cuối.
	{
		if (Row == 8) //Nếu như đã điền xong dòng cuối
		{
			memcpy(Solution[0], Sudoku[0], SQ_SIZE * sizeof(int));
			++(*Count); //Tăng số cách giải lên 1 đơn vị.
			return;
		}
		else //Nếu chưa thì giải tiếp dòng kế.
		{
			SolveSudoku(Sudoku, Solution, Count, Row + 1);
		}
	}
	else
	{
		if (Sudoku[Row][Col] == 0) //Nếu ô đang xét chưa điền.
		{
			for (int i = 1; i < MATRIX_SIZE + 1; i++) //Thử các giá trị và điền vào nếu phù hợp.
			{
				if (CheckCandidate(Sudoku, Row, Col, i) == true)
				{
					Sudoku[Row][Col] = i;
					SolveSudoku(Sudoku, Solution, Count, Row, Col + 1);

					//Nếu như số cách giải >= 2 tức là lưới Sudoku không hợp lệ nên dừng quá trình bỏ chọn để chương trình
					//nhanh hơn.
					if (*Count < 2)
					{
						Sudoku[Row][Col] = 0;
					}
				}
			}
		}
		else //Nếu như ô đã được điền thì chuyển sang ô kế tiếp.
		{
			SolveSudoku(Sudoku, Solution, Count, Row, Col + 1);
		}
	}
}

//Hàm giải Sudoku (Giải tất cả trường hợp).
void SolveSudoku_ManySolution(int **Sudoku, int *Count, int Row, int Col)
{
	if (Col == 9) //Nếu như đã điền xong cột cuối.
	{
		if (Row == 8) //Nếu như đã điền xong dòng cuối
		{
			gotoXY(30, 22 + 30 * (*Count));
			printf("----------------------------------------------------------------------");
			PrintGrid(45, 1 + 30 * (*Count));
			PrintMatrix(Sudoku, MATRIX_SIZE, MATRIX_SIZE, 49, 3 + 30 * (*Count));
			++(*Count);
			return;
		}
		else //Nếu chưa thì giải tiếp dòng kế.
		{
			SolveSudoku_ManySolution(Sudoku, Count, Row + 1);
		}
	}
	else
	{
		if (Sudoku[Row][Col] == 0) //Nếu ô đang xét chưa điền.
		{
			for (int i = 1; i < MATRIX_SIZE + 1; i++) //Thử các giá trị và điền vào nếu phù hợp.
			{
				if (CheckCandidate(Sudoku, Row, Col, i) == true)
				{
					Sudoku[Row][Col] = i;
					SolveSudoku_ManySolution(Sudoku, Count, Row, Col + 1);
					Sudoku[Row][Col] = 0;
				}
			}
		}
		else //Nếu như ô đã được điền thì chuyển sang ô kế tiếp.
		{
			SolveSudoku_ManySolution(Sudoku, Count, Row, Col + 1);
		}
	}
}

//Hàm tìm các ô đường xuyên. Trả về mảng chứa vị trí của các ô đường xuyên
int* FindCross(int **Sudoku, int Row, int Col)
{
	int *a = (int *)malloc(MATRIX_SIZE * sizeof(int));
	int n = 0;

	if (a != NULL)
	{
		for (int i = 0; i < Row * Col; i++)
		{
			if (Sudoku[i / Col][i % Col] == -1)
			{
				a[n] = i;
				++n;
			}
		}
	}

	return a;
}

/*Hàm kiểm tra số đã tồn tại trong đường xuyên hay chưa.
Nếu như tồn tại thì trả về true, chưa tồn tại thì trả về false.
*/
bool CheckExist(int **Sudoku, int Col, int *Index, int n, int Value)
{
	for (int i = 0; i < n; i++)
	{
		if (Sudoku[Index[i] / Col][Index[i] % Col] == Value)
		{
			return true;
		}
	}

	return false;
}

//Hàm giải Sudoku đường xuyên.
void SolveSudoku_(int **Sudoku, int *Index, int Row, int Col, int n)
{
	if (n == MATRIX_SIZE)
	{
		int Count = 0;
		SolveSudoku_ManySolution(Sudoku, &Count);
		return;
	}
	else
	{
		for (int i = 1; i < 10; i++)
		{
			if (CheckExist(Sudoku, Col, Index, n, i * 11) == false)
			{
				Sudoku[Index[n] / Col][Index[n] % Col] = i * 11;
				SolveSudoku_(Sudoku, Index, Row, Col, n + 1);
				Sudoku[Index[n] / Col][Index[n] % Col] = -1;
			}
		}
	}
}

/*Hàm phát sinh giá trị ngẫu nhiên tạo lưới Sudoku KÍN sau đó ghi vào file
Nếu thành công trả về SUCCESS, ngược lại trả về FAIL*/
STATUS BuildSudoku(const char *Filename)
{
	//Khỡi tạo lưới Sudoku rỗng.
	int **Sudoku = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));

	if (Sudoku != NULL)
	{
		//Khởi tạo 9 ô có giá trị từ 1-9 tại những vị trí ngẫu nhiên => Luôn luôn thỏa điều kiện của Sudoku.
		//Trường hợp xấu nhất cả 9 ô random đều trùng nhau. Tuy nhiên điều này vẫn không làm ảnh hướng đến chương trình.
		int Count;
		bool Status;
		srand(time(NULL));
		for (int i = 1; i < MATRIX_SIZE + 1; i++)
		{
			Sudoku[rand() % MATRIX_SIZE][rand() % MATRIX_SIZE] = i;
		}

		Count = 1; //Để Count có giá trị 1 vì ta chỉ cần lấy ra 1 kết quả
		SolveSudoku(Sudoku, Sudoku, &Count);
		Status = WriteSudoku(Filename, Sudoku);
		Destroy((void **)Sudoku);
		if (Status == true)
		{
			return SUCCESS;
		}
	}

	return FAIL;
}

/*Hàm tạo ma trận Sudoku nhằm mục đích sử dụng (có một số lượng ô trống nhất định được định nghĩa trước).
Trả về SUCCESS nếu thao tác thành công.
Nếu không đủ bộ nhớ hoặc không truy cập được file thì trả về FAIL.
Nếu quá trình tạo trên 10s thì trả về TIME_OUT. Tất cả đã được định nghĩa trong kiểu dữ liệu STATUS.
*/
STATUS GenerateSudoku(const char *Filename, DIFFICULT_LV Difficult)
{
	//Khỡi tạo lưới Sudoku rỗng.
	int **Sudoku = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
	int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
	int **Source = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));

	if (Sudoku != NULL && Solution != NULL && Source != NULL)
	{
		int Count, r, c, Blank, t;
		time_t Time;
		STATUS Status;

		//Khởi tạo 9 ô có giá trị từ 1-9 tại những vị trí ngẫu nhiên => Luôn luôn thỏa điều kiện của Sudoku.
		//Trường hợp xấu nhất thì cả 9 ô random trùng nhau. Tuy nhiên điều này không làm ảnh hưởng đến chương trình.
		srand(time(NULL));
		for (int i = 1; i < MATRIX_SIZE + 1; i++)
		{
			Sudoku[rand() % MATRIX_SIZE][rand() % MATRIX_SIZE] = i;
		}

		Count = 1; //Để Count có giá trị 1 vì ta chỉ cần lấy ra 1 kết quả
		SolveSudoku(Sudoku, Solution, &Count);
		//Sao chép Sudoku kết quả ra cho ma trận Source để quay ngược quá trình khi cần thiết.
		memcpy(Source[0], Solution[0], SQ_SIZE * sizeof(int));

		//Số ô trống cần có trong ma trận. Số ô trống này giao động trong khoảng lân cận so với giá trị gốc.
		Blank = SQ_SIZE - Difficult;
		t = 0; //Số lần quay ngược quá trình.
		Time = clock();
		while (Blank > -1) //Trong khi số ô trống chưa đủ.
		{
			//Phát trinh ngẫu nhiên dòng, cột.
			r = rand() % MATRIX_SIZE;
			c = rand() % MATRIX_SIZE;

			//Nếu ô được phát sinh ngẫu nhiên chưa xóa.
			if (Solution[r][c] != 0)
			{
				//Xóa một ô ngẫu nhiên cùng với ô đối xứng với nó qua đường chéo.
				Sudoku[r][c] = 0;
				Solution[r][c] = 0;
				Sudoku[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = 0;
				Solution[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = 0;

				//Giải thử ma trận Sudoku sau khi xóa 2 phần tử.
				Count = 0;
				SolveSudoku(Sudoku, Sudoku, &Count);
				//Vì chỉ quay lui khi Count < 2 nên ma trận truyền vào có thể sẽ không trở về trạng thái ban đầu nên ta tiến
				//hành sao chép.
				memcpy(Sudoku[0], Solution[0], SQ_SIZE * sizeof(int));
				if (Count > 1) //Nếu có 2 cách giải trở lên.
				{
					//Trả một ô về giá trị cũ.
					Solution[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = Source[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1];
					Sudoku[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = Source[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1];

					//Tiếp tục kiểm tra.
					Count = 0;
					SolveSudoku(Sudoku, Sudoku, &Count);
					memcpy(Sudoku[0], Solution[0], SQ_SIZE * sizeof(int));
					if (Count > 1)
					{
						//Nếu như thời gian thực hiện xóa > 2s.
						if (double(clock() - Time) / CLOCKS_PER_SEC > 1.5)
						{
							Time = clock(); //Đặt lại mốc thời gian tính toán.
							++t; //Tăng số lần vượt thời gian lên 1 đơn vị.
							if (t > 2) //Nếu số lần vượt thời gian > 2, giải phóng tất cả ma trận, trả về TIME_OUT.
							{
								Destroy((void **)Sudoku);
								Destroy((void **)Solution);
								Destroy((void **)Source);
								return TIME_OUT;
							}
							else //Nếu chưa quá 2 lần vượt thời gian, tiến hành đảo ngược quá trình.
							{
								//Đưa ma trận Sudoku và Solution về như cũ (Được giải đầy đủ).
								memcpy(Sudoku[0], Source[0], SQ_SIZE * sizeof(int));
								memcpy(Solution[0], Source[0], SQ_SIZE * sizeof(int));
								Blank = SQ_SIZE - Difficult;
							}
						}
						else //Nếu chưa quá thời gian thì đưa ô còn lại vế giá trị cũ.
						{
							Solution[r][c] = Source[r][c];
							Sudoku[r][c] = Source[r][c];
						}
					}
					else //Nếu chỉ có 1 cách giải.
					{
						--Blank;
					}
				}
				else //Nếu chỉ có 1 cách giải.
				{
					Blank = Blank - 2;
				}
			}
		}

		//Nếu quá trình xóa ô bên trên thực hiện thành công thì tiến hành ghi ra file.
		Status = WriteGenerateSudoku(Filename, Solution);
		Destroy((void **)Sudoku);
		Destroy((void **)Solution);
		Destroy((void **)Source);
		return Status;
	}
	
	Destroy((void **)Sudoku);
	Destroy((void **)Solution);
	Destroy((void **)Source);
	return FAIL;
}

/*Hàm tạo ma trận Sudoku nhằm mục đích tạo Sudoku cho người dùng (có một số lượng ô trống nhất định được định nghĩa trước).
Trả về SUCCESS nếu thao tác thành công.
Nếu không đủ bộ nhớ hoặc không truy cập được file thì trả về FAIL.
Nếu quá trình tạo trên 10s thì trả về TIME_OUT. Tất cả đã được định nghĩa trong kiểu dữ liệu STATUS.
*/
STATUS GenerateSudoku_(const char *Filename, DIFFICULT_LV Difficult)
{
	//Khỡi tạo lưới Sudoku rỗng.
	int **Sudoku = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
	int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
	int **Source = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));

	if (Sudoku != NULL && Solution != NULL && Source != NULL)
	{
		int Count, r, c, Blank, t;
		time_t Time;
		STATUS Status;

		//Khởi tạo 9 ô có giá trị từ 1-9 tại những vị trí ngẫu nhiên => Luôn luôn thỏa điều kiện của Sudoku.
		//Trường hợp xấu nhất thì cả 9 ô random trùng nhau. Tuy nhiên điều này không làm ảnh hưởng đến chương trình.
		srand(time(NULL));
		for (int i = 1; i < MATRIX_SIZE + 1; i++)
		{
			Sudoku[rand() % MATRIX_SIZE][rand() % MATRIX_SIZE] = i;
		}

		Count = 1; //Để Count có giá trị 1 vì ta chỉ cần lấy ra 1 kết quả
		SolveSudoku(Sudoku, Solution, &Count);
		//Sao chép Sudoku kết quả ra cho ma trận Source để quay ngược quá trình khi cần thiết.
		memcpy(Source[0], Solution[0], SQ_SIZE * sizeof(int));

		//Số ô trống cần có trong ma trận. Số ô trống này giao động trong khoảng lân cận so với giá trị gốc.
		Blank = SQ_SIZE - Difficult;
		t = 0; //Số lần quay ngược quá trình.
		Time = clock();
		while (Blank > -1) //Trong khi số ô trống chưa đủ.
		{
			//Phát trinh ngẫu nhiên dòng, cột.
			r = rand() % MATRIX_SIZE;
			c = rand() % MATRIX_SIZE;

			//Nếu ô được phát sinh ngẫu nhiên chưa xóa.
			if (Solution[r][c] != 0)
			{
				//Xóa một ô ngẫu nhiên cùng với ô đối xứng với nó qua đường chéo.
				Sudoku[r][c] = 0;
				Solution[r][c] = 0;
				Sudoku[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = 0;
				Solution[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = 0;

				//Giải thử ma trận Sudoku sau khi xóa 2 phần tử.
				Count = 0;
				SolveSudoku(Sudoku, Sudoku, &Count);
				//Vì chỉ quay lui khi Count < 2 nên ma trận truyền vào có thể sẽ không trở về trạng thái ban đầu nên ta tiến
				//hành sao chép.
				memcpy(Sudoku[0], Solution[0], SQ_SIZE * sizeof(int));
				if (Count > 1) //Nếu có 2 cách giải trở lên.
				{
					//Trả một ô về giá trị cũ.
					Solution[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = Source[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1];
					Sudoku[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1] = Source[MATRIX_SIZE - r - 1][MATRIX_SIZE - c - 1];

					//Tiếp tục kiểm tra.
					Count = 0;
					SolveSudoku(Sudoku, Sudoku, &Count);
					memcpy(Sudoku[0], Solution[0], SQ_SIZE * sizeof(int));
					if (Count > 1)
					{
						//Nếu như thời gian thực hiện xóa > 2s.
						if (double(clock() - Time) / CLOCKS_PER_SEC > 1.5)
						{
							Time = clock(); //Đặt lại mốc thời gian tính toán.
							++t; //Tăng số lần vượt thời gian lên 1 đơn vị.
							if (t > 2) //Nếu số lần vượt thời gian > 2, giải phóng tất cả ma trận, trả về TIME_OUT.
							{
								Destroy((void **)Sudoku);
								Destroy((void **)Solution);
								Destroy((void **)Source);
								return TIME_OUT;
							}
							else //Nếu chưa quá 2 lần vượt thời gian, tiến hành đảo ngược quá trình.
							{
								//Đưa ma trận Sudoku và Solution về như cũ (Được giải đầy đủ).
								memcpy(Sudoku[0], Source[0], SQ_SIZE * sizeof(int));
								memcpy(Solution[0], Source[0], SQ_SIZE * sizeof(int));
								Blank = SQ_SIZE - Difficult;
							}
						}
						else //Nếu chưa quá thời gian thì đưa ô còn lại vế giá trị cũ.
						{
							Solution[r][c] = Source[r][c];
							Sudoku[r][c] = Source[r][c];
						}
					}
					else //Nếu chỉ có 1 cách giải.
					{
						--Blank;
					}
				}
				else //Nếu chỉ có 1 cách giải.
				{
					Blank = Blank - 2;
				}
			}
		}

		//Nếu quá trình xóa ô bên trên thực hiện thành công thì tiến hành ghi ra file.
		Status = WriteSudoku(Filename, Solution);
		Destroy((void **)Sudoku);
		Destroy((void **)Solution);
		Destroy((void **)Source);
		return Status;
	}

	Destroy((void **)Sudoku);
	Destroy((void **)Solution);
	Destroy((void **)Source);
	return FAIL;
}

//Hàm kiểm tra chuỗi nhập vào có đúng là tọa độ ô hay không.
bool CheckCoordinate(char *s)
{
	strupr(s);
	if (s[0] >= 'A' && s[0] <= 'I' && s[1] >= '0' && s[2] <= '9')
	{
		return true;
	}

	return false;
}

/*Hàm kiểm tra xem lệnh điều khiển là chọn ô hay chọn chức năng.
Nếu là chọn ô trả về COORDINATE.
Nếu là chọn chức năng thì trả về FEATURE.
Nếu không là gì cả thì trả về FAIL.
*/
STATUS CheckCommand(char *Command)
{
	if (Command != NULL)
	{
		strupr(Command);
		if (strlen(Command) == 2 && CheckCoordinate(Command) == true)
		{
			return COORDINATE;
		}
		else
		{
			if (strlen(Command) == 1 && (Command[0] == 'N' || Command[0] == 'H' || Command[0] == 'C' || Command[0] == 'F' || Command[0] == 'S' || Command[0] == 'E'))
			{
				return FEATURE;
			}
		}
	}

	return FAIL;
}

//Hàm thực hiện các lệnh điều khiển.
int CommandControl(int **Sudoku, int Row, int Col, int *Blank)
{
	char *Command = NULL;

	gotoXY(1, 30);
	fflush(stdin);
	CommandInput("Ex:\nCoordinate: A1\nFeature: N\nPlease enter the coordinates or feature you wanna choose", &Command);
	STATUS stt = CheckCommand(Command);

	if (stt != FAIL)
	{
		if (stt == COORDINATE)
		{
			if (Sudoku[Command[1] - '1'][Command[0] - 'A'] < 10)
			{
				if (Sudoku[Command[1] - '1'][Command[0] - 'A'] == 0)
				{
					--(*Blank);
				}

				ValueInput(&Sudoku[Command[1] - '1'][Command[0] - 'A']);
			}
		}
		else
		{
			switch (Command[0])
			{
				case 'N':
				{
					stt = GenerateSudoku("Sudoku.in", ChooseDiffLV());

					if (stt == TIME_OUT)
					{
						printf("REQUEST TIME OUT!\nPLEASE TRY AGAIN!\n");
					}
					else
					{
						if (stt == FAIL)
						{
							printf("Low of memory or file can not access.\n");
						}
						else
						{
							ReadSudoku_C2("Sudoku.in", Sudoku, Blank);
							printf("Process complete!\n");
						}
					}

					break;
				}
				case 'H':
				{
					char *Coordinate;
					fflush(stdin);
					CommandInput("Please enter the coordinate you wanna fill", &Coordinate);

					if (Coordinate != NULL)
					{
						if (CheckCommand(Coordinate) == COORDINATE)
						{
							int Count;
							int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
							//Tránh trường hợp người chơi chơi sai trên Sudoku.
							int **Temp = ReadSudoku("Sudoku.in", &Count);
							
							Count = 0;
							if (Solution != NULL && Temp != NULL)
							{
								if (Sudoku[Coordinate[1] - '1'][Coordinate[0] - 'A'] == 0)
								{
									--(*Blank);
								}

								SolveSudoku(Temp, Solution, &Count);
								Sudoku[Coordinate[1] - '1'][Coordinate[0] - 'A'] = Solution[Coordinate[1] - '1'][Coordinate[0] - 'A'];
							}

							Destroy((void **)Solution);
							Destroy((void **)Temp);
						}

						free(Coordinate);
					}
					break;
				}
				case 'C':
				{
					fflush(stdin);
					int Count;
					int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
					//Tránh trường hợp người dùng chơi sai trên Sudoku.
					int **Temp = ReadSudoku("Sudoku.in", &Count);

					if (Temp != NULL && Solution != NULL)
					{
						Count = 0;
						SolveSudoku(Temp, Solution, &Count);

						//Kiểm tra ô sai và đánh dấu bằng cách chuyển giá trị của ô sai thành giá trị âm.
						for (int i = 0; i < Row; i++)
						{
							for (int j = 0; j < Col; j++)
							{
								if (Sudoku[i][j] > 0 && Sudoku[i][j] != Solution[i][j])
								{
									Sudoku[i][j] = 0 - Sudoku[i][j];
									Destroy((void **)Solution);
									Destroy((void **)Temp);
									free(Command);
									return 1;
								}
							}
						}
					}

					Destroy((void **)Solution);
					Destroy((void **)Temp);
					break;
				}
				case 'F':
				{
					int Count = 0;
					int **Temp = ReadSudoku("Sudoku.in", &Count);
					
					if (Temp != NULL)
					{
						Count = 0;
						SolveSudoku(Temp, Sudoku, &Count);
						Destroy((void **)Temp);
					}

					break;
				}
				case 'S':
				{
					if (WriteSudoku("Sudoku.out", Sudoku) == SUCCESS)
					{
						printf("Process complete!!!");
					}

					break;
				}
				case 'E':
				{
					free(Command);
					return 0;
				}
			}
		}
	}

	if (Command != NULL)
	{
		free(Command);
	}
	return 1;
}

//Hàm kiểm tra ô sai và đánh dấu.
void CheckFalse(int **Sudoku, int **Solution, int Row, int Col)
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (Sudoku[i][j] > 0 && Sudoku[i][j] != Solution[i][j])
			{
				Sudoku[i][j] = 0 - Sudoku[i][j];
				return;
			}
		}
	}
}

//Hàm điều khiển game dùng các thao tác với bàn phím.
int Control(int **Sudoku, int Row, int Col, int *Blank)
{
	char ch;
	int r = 0;
	int c = 0;
	STATUS stt;

	PrintSUDOKU();
	PrintGrid(20, 8);
	PrintMatrix(Sudoku, Row, Col, 24, 10);
	PrintFeature(65, 8);
	gotoXY(35, 29);
	textColor(12);
	PrintCharacter('=', 58, true);
	Contact(50, 30);

	while (1)
	{
		if (*Blank == 0 && CheckSudoku(Sudoku, Row, Col) == true)
		{
			ClearScreen(0, 0);
			printf("CONGRATULATION!!!\n");
			Sleep(3000);
			return 1;
		}

		if (r < 0)
		{
			r = 0;
		}
		if (c < 0)
		{
			c = 0;
		}

		gotoXY(24 + c * 4, 10 + r * 2);

		if (_kbhit())
		{
			if (GetAsyncKeyState(VK_UP))
			{
				ch = getch();
				ch = getch();

				r = (r - 1) % 9;
				Beep(3000, 10);
			}
			else
			{
				if (GetAsyncKeyState(VK_DOWN))
				{
					ch = getch();
					ch = getch();

					r = (r + 1) % 9;
					Beep(3000, 10);
				}
				else
				{
					if (GetAsyncKeyState(VK_LEFT))
					{
						ch = getch();
						ch = getch();

						c = (c - 1) % 9;
						Beep(3000, 10);
					}
					else
					{
						if (GetAsyncKeyState(VK_RIGHT))
						{
							ch = getch();
							ch = getch();

							c = (c + 1) % 9;
							Beep(3000, 10);
						}
						else
						{
							if (GetAsyncKeyState(VK_N))
							{
								ch = getch();
								stt = GenerateSudoku("Sudoku.in", ChooseDiffLV());

								ClearScreen(0, 0);
								if (stt == TIME_OUT)
								{
									printf("REQUEST TIME OUT!\nPLEASE TRY AGAIN!\n");
									return 0;
								}
								else
								{
									if (stt == FAIL)
									{
										printf("Low of memory or file can not access.\n");
										return 0;
									}
									else
									{
										ReadSudoku_C2("Sudoku.in", Sudoku, Blank);
										printf("Process complete!\n");
										ClearScreen(0, 0);
										PrintSUDOKU();
										PrintGrid(20, 8);
										PrintMatrix(Sudoku, Row, Col, 24, 10);
										PrintFeature(65, 8);
									}
								}

								Sleep(2000);
							}
							else
							{
								if (GetAsyncKeyState(VK_H))
								{
									ch = getch();

									if (Sudoku[r][c] == 0)
									{
										int Count;
										int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
										//Tránh trường hợp người chơi chơi sai trên Sudoku.
										int **Temp = ReadSudoku("Sudoku.in", &Count);

										Count = 0;
										if (Solution != NULL && Temp != NULL)
										{
											if (Sudoku[r][c] == 0)
											{
												--(*Blank);
											}

											SolveSudoku(Temp, Solution, &Count);
											Sudoku[r][c] = Solution[r][c];
											PrintMatrix(Sudoku, Row, Col, 24, 10);
										}

										Destroy((void **)Solution);
										Destroy((void **)Temp);
									}
								}
								else
								{
									if (GetAsyncKeyState(VK_C))
									{
										ch = getch();
										fflush(stdin);
										int Count;
										int **Solution = (int **)Alloc(MATRIX_SIZE, MATRIX_SIZE, sizeof(int));
										//Tránh trường hợp người dùng chơi sai trên Sudoku.
										int **Temp = ReadSudoku("Sudoku.in", &Count);

										if (Temp != NULL && Solution != NULL)
										{
											Count = 0;
											SolveSudoku(Temp, Solution, &Count);

											//Kiểm tra ô sai và đánh dấu bằng cách chuyển giá trị của ô sai thành giá trị âm.
											CheckFalse(Sudoku, Solution, Row, Col);
											PrintMatrix(Sudoku, Row, Col, 24, 10);
										}

										Destroy((void **)Solution);
										Destroy((void **)Temp);
									}
									else
									{
										if (GetAsyncKeyState(VK_F))
										{
											ch = getch();
											int Count = 0;
											int **Temp = ReadSudoku("Sudoku.in", &Count);

											if (Temp != NULL)
											{
												Count = 0;
												SolveSudoku(Temp, Sudoku, &Count);
												Destroy((void **)Temp);
												PrintMatrix(Sudoku, Row, Col, 24, 10);
											}
										}
										else
										{
											if (GetAsyncKeyState(VK_S))
											{
												ch = getch();
												if (WriteSudoku("Sudoku.out", Sudoku) == SUCCESS)
												{
													ClearScreen(0, 0);
													printf("PROCESS COMPLETE!!!\n");
													Sleep(2000);
													ClearScreen(0, 0);
													return 1;
												}
											}
											else
											{
												if (GetAsyncKeyState(VK_E))
												{
													ch = getch();
													ClearScreen(0, 0);
													return 0;
												}
												else
												{
													ch = getch();
													if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
													{
														if (Sudoku[r][c] < 10)
														{
															if (Sudoku[r][c] == 0)
															{
																--(*Blank);
															}

															Sudoku[r][c] = ch - '0';
															PrintMatrix(Sudoku, Row, Col, 24, 10);
														}
													}
													else
													{
														ClearScreen(0, 0);
														printf("DON'T PRESS ANY KEY ELSE WHICH IS NOT VALID IN THIS PROGRAM!\n");
														Sleep(5000);
														ClearScreen(0, 0);
														return 0;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		Sleep(300);
	}

	return 1;
}

//Hàm kiểm tra ma trận sudoku đã điền kín.
bool CheckSudoku(int **Sudoku, int Row, int Col)
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (CheckValid(Sudoku, i, j, Sudoku[i][j]) == false)
			{
				return false;
			}
		}
	}

	return true;
}