// checker-practice4.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <fstream> //要開啟檔案時用的標頭檔
#include <Windows.h>
#include <cmath>
using namespace std;
void read();
void kind_my_another();//分辨敵我方
void search(); //找棋子的位置
//void drawboard();
int choose_chess(int x_destination, int y_destination);  //指定這一局要移動的座標並輸出，指定棋子與目的地座標的距離
const int N = 17;
int A[N][N];
double r = 0; //棋子與所要下的目標的距離
double r_min = 0; //距離最小
HWND hwnd;
int Color_Name;//棋子的顏色

struct Chess 
{
	int x; //棋子的x座標
	int y; //棋子的y座標
	int c; //顏色
};
struct Chess my_checker[15];//存放自己棋子所在位置的座標的陣列
struct Chess another_checker[15];//存放敵方棋子所在位置的座標的陣列

void read()  //讀取棋盤
{
	ifstream board; //建立可讀的檔案物件
	board.open("board.txt");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board >> A[i][j];
		}
	}
	board.close();
}

void kind_my_another()
{
	int my = 0;
	int another=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j]== Color_Name) {
				my_checker[my].x=i;//把i放入struct的x裡
				my_checker[my].y=j;//把j放入struct的y裡
				my_checker[my].c = Color_Name;
			}
			else if ((A[i][j] != 0) && (A[i][j] != 1)) {
				my_checker[another].x = i;//把i放入struct的x裡
				my_checker[another].y = j;//把j放入struct的y裡
			}
		}
	}
}

void search() 
{
	for (int i = 0; i < 15; i++) {
		int x;
		int y;
		x = my_checker[i].x; //把struct裡面的位置取出來，放入x裡
		y = my_checker[i].y;  //把struct裡面的位置取出來，放入y裡
	}
}


int choose_chess(int x_destination, int y_destination) //選定要下的棋子，把座標輸出"1072016.txt"裡，且換行
{
	int x = 0;
	int y = 0;
	int i, j;
	ofstream export;
	export.open("1072016.txt"); 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (A[i][j] == Color_Name) {
				//---選一個棋子的過程----//
				export << A[i][j] << "\n";//寫入檔案
				cout << endl;
				for (int a = -1; a <= 1; a++) {
					for (int b = -1; b <= 1; b++) {
						if (a != 1 && b != -1) {
							r = sqrt(pow((x_destination - (i + a)), 2) + pow((y_destination - (j + b)), 2));
							if (r < r_min) {
								r_min = r;
								A[x][y] = A[i + a][j + b]; 
								export << A[x][y]<<"\n"; //寫入檔案
								
							}
						}
					}
				}
			}
		}
	}
}

 

/*int Destination_distance(int x_destination, int y_destination)
{
	int x=0;
	int y=0;
	int i,j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (A[i][j] == Color_Name) {
				for (int a = -1; a <= 1; a++) {
					for (int b = -1; b <= 1; b++) {
						if (a != 1 && b != -1) {
							r = sqrt(pow((x_destination - (i + a)), 2) + pow((y_destination - (j + b)), 2));
							if (r < r_min) {
								r_min = r;
								A[x][y] = A[i + a][j + b];
							}
						}
					}
				}
			}
		}
	}
	A[i][j] = A[x][y];
	return r_min;
}*/




/*void drawboard()
{
	if (hwnd) DestroyWindow(hwnd);
	hwnd = CreateWindow(L"static", L"checker"
		, WS_VISIBLE | WS_BORDER | WS_OVERLAPPED
		, 10, 10, 1024, 768, 0, 0, 0, 0);
	ShowWindow(hwnd, SW_SHOW);
	HDC hdc = GetDC(hwnd);
	double l = 40;
	double dx = l * cos(60 * 3.14159 / 180.);
	double dy = l * sin(60 * 3.14159 / 180.);
	int x, y;
	int i, j;
	int x0 = 4 * l;
	int y0 = l;
	int r = 10;
	int c[5] = { 0xffffff,0x0000ff,0x00ff00,0x00ffff };
	//c[0] 0xffffff white
	//c[1] 0x0000ff red
	//c[2] 0x00ff00 green
	//c[3] 0x00ffff yellow
	TCHAR s[64] = { 0 };
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			x = (2 * i - j)*dx + x0;
			y = j * dy + y0;
			if (A[j][i])
			{
				HBRUSH oldbrush, brush;
				brush = CreateSolidBrush(c[A[j][i] - 1]);
				oldbrush = (HBRUSH)SelectObject(hdc, brush);
				Ellipse(hdc, x - r, y - r, x + r, y + r);
				wsprintf(s, L"%d,%d", j, i);
				TextOut(hdc, x, y, s, 64);
				SelectObject(hdc, oldbrush);
			}
		}
	}
	ReleaseDC(hwnd, hdc);
}*/

int main()
{
	cin >> Color_Name;
	read();
	kind_my_another();
	search();
	if (Color_Name == 2) {  //red
		choose_chess(16, 4);
	}
	else if (Color_Name == 3) {  //green
		choose_chess(4, 16);
	}
	else { //yellow
		choose_chess(4, 4);
	}
	//drawboard();
}
   

