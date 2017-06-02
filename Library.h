/*
Product by Võ Sỹ Liên Thành
Contact:
Email: vosylienthanh@gmail.com
Facebook: https://www.facebook.com/VoSyLienThanh
*/

#pragma once
#ifndef Library_h
#define Library_h

#define MATRIX_SIZE		9
#define SQ_SIZE			(MATRIX_SIZE * MATRIX_SIZE)
#define BOX				3
#define BUFFER			100

//Các phím chữ cần thiết.
#define VK_N	0x004E
#define VK_H	0x0048
#define VK_C	0x0043
#define VK_F	0x0046
#define VK_S	0x0053
#define VK_E	0x0045

//Độ khó của Sudoku.
typedef enum DIFFICULT_LV
{
	EXTREMELY_EASY = 50,
	EASY = 37,
	MEDIUM = 32,
	HARD = 23,
};

//Trang thái xứ lý.
typedef enum STATUS
{
	SUCCESS,
	TIME_OUT,
	COORDINATE,
	FEATURE,
	FAIL,
};

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "NhapXuat.h"
#include "UserInterface.h"
#include "XuLy.h"

#pragma comment(lib, "winmm.lib")
#endif