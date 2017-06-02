/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#pragma once
#ifndef XuLy_h
#define XuLy_h

#include "Library.h"

//Hàm cấp phát ma trận. Thành công trả về ma trận đã cấp phát, thất bại trả về NULL.
void** Alloc(int Row, int Col, int Size);
//Hàm giải phóng ma trận.
void Destroy(void **Matrix);
//Hàm kiểm tra số có phù hợp để đưa vào ô hay không. Nếu phù hợp trả về true, ngược lại trả về false.
bool CheckCandidate(int **Sudoku, int Row, int Col, int Value);
//Hàm kiểm tra một số có hợp lệ hay không.
bool CheckValid(int **Sudoku, int Row, int Col, int Value);
//Hàm giải Sudoku.
void SolveSudoku(int **Sudoku, int **Solution, int *Count, int Row = 0, int Col = 0);
//Hàm giải Sudoku (Giải tất cả trường hợp).
void SolveSudoku_ManySolution(int **Sudoku, int *Count, int Row = 0, int Col = 0);
//Hàm tìm các ô đường xuyên. Trả về mảng chứa vị trí của các ô đường xuyên
int* FindCross(int **Sudoku, int Row, int Col);
/*Hàm kiểm tra số đã tồn tại trong đường xuyên hay chưa.
Nếu như tồn tại thì trả về true, chưa tồn tại thì trả về false.
*/
bool CheckExist(int **Sudoku, int Col, int *Index, int n, int Value);
//Hàm giải Sudoku đường xuyên.
void SolveSudoku_(int **Sudoku, int *Index, int Row, int Col, int n = 0);

//---------------------------------YÊU CẦU 01---------------------------------
/* Tạo lưới Sudoku 9x9 rỗng (Tất cả các ô đều là số 0).
Phát sinh giá trị ngẫu nhiên trong đoạn [1, 9] cho một ô số bất kỳ (không do người dùng nhập) của lưới vừa khởi tạo theo
đúng luật chơi Sudoku. Nếu các ô phát sinh giá trị thuộc cùng dòng, cột hoặc vùng 3x3 thì không được trùng nhau.
Lưu lưới đã khởi tạo vào tập tin Sudoku.in
*/
/*Hàm phát sinh giá trị ngẫu nhiên tạo lưới Sudoku KÍN sau đó ghi vào file
Nếu thành công trả về SUCCESS, ngược lại trả về FAIL*/
STATUS BuildSudoku(const char *Filename);
/*Hàm tạo ma trận Sudoku nhằm mục đích sử dụng (có một số lượng ô trống nhất định được định nghĩa trước).
Trả về SUCCESS nếu thao tác thành công.
Nếu không đủ bộ nhớ hoặc không truy cập được file thì trả về FAIL.
Nếu quá trình tạo trên 10s thì trả về TIME_OUT. Tất cả đã được định nghĩa trong kiểu dữ liệu STATUS.
*/
STATUS GenerateSudoku(const char *Filename, DIFFICULT_LV Difficult);
/*Hàm tạo ma trận Sudoku nhằm mục đích tạo Sudoku cho người dùng (có một số lượng ô trống nhất định được định nghĩa trước).
Trả về SUCCESS nếu thao tác thành công.
Nếu không đủ bộ nhớ hoặc không truy cập được file thì trả về FAIL.
Nếu quá trình tạo trên 10s thì trả về TIME_OUT. Tất cả đã được định nghĩa trong kiểu dữ liệu STATUS.
*/
STATUS GenerateSudoku_(const char *Filename, DIFFICULT_LV Difficult);
//Hàm kiểm tra chuỗi nhập vào có đúng là tọa độ ô hay không.
bool CheckCoordinate(char *s);
/*Hàm kiểm tra xem lệnh điều khiển là chọn ô hay chọn chức năng.
Nếu là chọn ô trả về COORDINATE.
Nếu là chọn chức năng thì trả về FEATURE.
Nếu không là gì cả thì trả về FAIL.
*/
STATUS CheckCommand(char *Command);
//Hàm thực hiện các lệnh điều khiển.
int CommandControl(int **Sudoku, int Row, int Col, int *Blank);
//Hàm kiểm tra ô sai và đánh dấu.
void CheckFalse(int **Sudoku, int **Solution, int Row, int Col);
//Hàm điều khiển game dùng các thao tác với bàn phím.
int Control(int **Sudoku, int Row, int Col, int *Blank);
//Hàm kiểm tra ma trận sudoku đã điền kín.
bool CheckSudoku(int **Sudoku, int Row, int Col);
#endif