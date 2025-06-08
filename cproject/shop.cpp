#include <stdio.h>
#include <conio.h>

#include "base.h"
#include "console_move.h"


#define MAP_WIDTH 30
#define MAP_HEIGHT 20
#pragma execution_character_set("utf-8")

void draw_shop_ui_bottom_right() {
    int ui_width = 10;
    int ui_height = 5;

    int startX = MAP_WIDTH - ui_width;
    int startY = MAP_HEIGHT - ui_height;

    gotoxy(startX * 2, startY);     printf("[  SHOP  ]");
    gotoxy(startX * 2, startY + 1); printf("|--------|");
    gotoxy(startX * 2, startY + 2); printf("| []  [] |");
    gotoxy(startX * 2, startY + 3); printf("| ## ##  |");
    gotoxy(startX * 2, startY + 4); printf("|--------|");
}
void open_shop() {
    system("cls");
    printf("\n\n");
    printf("========== 상점에 입장했습니다 ==========\n");
    printf("1. 씨앗 구매\n");
    printf("2. 작물 판매\n");
    printf("3. 나가기\n");
    printf("=========================================\n");

    while (1) {
        char input = _getch();
        if (input == '3') break;
        // 구매/판매 로직은 네가 확장하면 됨
    }

    draw_map();  // 나가면 다시 맵으로
}
