/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#pragma once
#ifndef NhapXuat_h
#define NhapXuat_h

#include "Library.h"

//Hàm đọc Sudoku và số lượng ô trống từ file. Thành công trả về ma trận Sudoku đọc được, ngược lại trả về NULL.
int** ReadSudoku(const char *Filename, int *Blank);
//Hàm đọc Sudoku với ô Sudoku có sẵn không cần tại mới và số lượng ô trống từ file.
void ReadSudoku_C2(const char *Filename, int **Sudoku, int *Blank);
//Hàm ghi Sudoku (Đã giải hoặc trong tùy chọn tính năng lưu lưới) ra file. Thành côn trả về SUCCESS, ngược lại trả về FAIL.
STATUS WriteSudoku(const char *Filename, int **Sudoku);
//Hàm ghi Sudoku (Sudoku được tạo ra để chơi) ra file. Thành công trả về true, ngược lại trả về false.
STATUS WriteGenerateSudoku(const char *Filename, int **Sudoku);
//Hàm ghi Sudoku (Sudoku được tạo ra để chơi) ra file. Thành công trả về SUCCESS, ngược lại trả về FAIL.
STATUS WriteGenerateSudoku(const char *Filename, int **Sudoku);
//Hàm đọc file text và hiển thị  ra màn hình.
void ReadTXT(const char *Filename);
//Hàm lựa chọn các chức năng.
int ChooseMenu();
//Hàm in ma trận ra màn hình.
void PrintMatrix(int **Matrix, int Row, int Col, int x, int y);
//Hàm in các chức năng trong khi chơi.
void PrintFeature(int x, int y);
//Hàm in độ khó để lựa chọn.
DIFFICULT_LV ChooseDiffLV();
//Hàm lựa chọn hướng dẫn hay giới thiệu game.
int ChooseIntro(int x, int y);
//Hàm lựa chọn giải Sudoku thông thường hay Sudoku đường xuyên.
int ChooseSolve(int x, int y);
//Hàm cho người chơi nhập vào chuỗi tọa độ ô hoặc phím chức năng để xử lý.
void CommandInput(char *Notification, char **Command, char KyTuDung = '\n');
/*Hàm nhập vào giá trị của ô muốn chọn.
Nếu người dùng nhập sai thì chương trình sẽ yêu cầu nhập lại.
*/
void ValueInput(int *Value);
#endif