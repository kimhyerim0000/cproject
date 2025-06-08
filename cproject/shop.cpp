#include <stdio.h>
#include "base.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

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
