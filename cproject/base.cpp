// base.cpp
// [14][55]
#pragma execution_character_set("utf-8")

#include <windows.h>
#include <stdio.h>
#define MAP_HEIGHT 20

void gotoxy(int x, int y); 

void SetConsole() {
	system("chcp 65001 > nul");
	system("mode con cols=120 lines=30 | title 게임제목");
	system("title 게임제목");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize = 1; // 커서 크기

	if (consoleHandle != NULL && consoleHandle != INVALID_HANDLE_VALUE) {
		SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	}
	else {
		printf(" 콘솔 핸들 획득 실패!\n");
	}
}
void titleDraw() {
	printf("hello world!\n\n");
}

void menuDraw() {
	int y = MAP_HEIGHT+3;

		gotoxy(1, y);
		printf("[1] Plant");

		gotoxy(10, y);
		printf("| [2] Water");

		gotoxy(22, y);
		printf("| [3] Harvest");

		gotoxy(36, y);
		printf("| [I] Inventory");

		gotoxy(52, y);
		printf("| [Q] Sleep");
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos); //좌표 위치 변경
}


