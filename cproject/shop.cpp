﻿#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "player.h"
#include "base.h"
#include "console_move.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20
#define SEED_COUNT 10
#pragma execution_character_set("utf-8")

const char* seed_names[SEED_COUNT] = {
    "감자 씨앗", "당근 씨앗", "토마토 씨앗", "옥수수 씨앗", "블루베리 씨앗",
    "단호박 씨앗", "무 씨앗", "고구마 씨앗", "시금치 씨앗", "브로콜리 씨앗"
};
int seed_prices[SEED_COUNT] = { 100, 120, 150, 180, 200, 250, 130, 160, 110, 170 };

void draw_intro_trophy_dog() {
    const char* lines[] = {
        "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",
        "██████████████████████████████████████████████████████████░████████░███████████████████████████████████████████████████████████████████████████████",
        "█████████████████████████████████████████████████████████░░████████░░██████████████████████████████████████████████████████████████████████████████",
        "████████████████████████████████████████████████████████░░░░██████░░░░██████████████████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████░░░░░░████░░░░░░██████████████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████░░░░█░░░░░░█░░░░████████████████████████████████████████████████████████████████",
        "████████████████████████████████████████████████████████░░░░░░░░░░░░░░███████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████░░░$$$░░░░$$$░░░████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████████████████░░░░░░░░░░░░░░░░██████████████████████████████████████████████████████████████████",
        "███████████████████████████████████████████░░░░██████████░░░░░░░░░░░░██████████░░░░██████████████████████████████████████████████████████",
        "██████████████████████████████████████████░░░░░░███████████░░░░░░░░███████████░░░░░░████████████████████████████████████"
    };
    for (int i = 0; i < 14; i++) {
        gotoxy(0, i + 1);
        printf("%s\n", lines[i]);
    }
}

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

void draw_seed_shop_menu() {
    system("cls");
    draw_intro_trophy_dog();
    printf("================================================ 🌱 씨앗 상점 ==========================================================\n\n");
    for (int i = 0; i < SEED_COUNT / 2; i++) {
        printf("[%-2d] %-15s - ₩%-4d   [%-2d] %-15s - ₩%-4d\n",
            i + 1, seed_names[i], seed_prices[i],
            i + 6, seed_names[i + 5], seed_prices[i + 5]);
    }
    printf("[.] 밭 타일 구매");
    printf("\n\n[ 0] 나가기\n\n");
    printf("소지금: ₩%d\n", player.money);
}

void handle_seed_purchase() {
    while (1) {
        draw_seed_shop_menu();
        char input = _getch();

        if (input == '0') {
            gotoxy(0, 28);
            printf("상점을 나갑니다...\n");
            _getch();
            break;
        }

        if (input == '.') {
            if (player.money >= 100) { // 예: 밭 타일 가격 50원
                player.money -= 100;
                player.farm_tile++;
                gotoxy(0, 28);
                printf("🧱 밭 타일이 1칸 늘어났습니다! (현재: %d칸)", player.farm_tile);
            }
            else {
                gotoxy(0, 28);
                printf("✘ 돈이 부족합니다.");
            }
            printf("\n계속하려면 아무 키나 누르세요...");
            _getch();
            continue;
        }

        int choice = input - '0';
        if (choice < 1 || choice > SEED_COUNT) continue;

        int index = choice - 1;
        if (player.money >= seed_prices[index]) {
            player.money -= seed_prices[index];
            add_item(&player.inventory, seed_names[index], 1);
            gotoxy(0, 28);
            printf("✔ %s 1개를 구매했습니다!", seed_names[index]);
        }
        else {
            gotoxy(0, 28);
            printf("✘ 돈이 부족합니다.");
        }
        printf("\n계속하려면 아무 키나 누르세요...");
        _getch();
    }
}


void open_shop() {
    system("cls");
    draw_intro_trophy_dog();
    gotoxy(0, 16);
    printf("================================================ 상점에 입장했습니다 ===================================================");
    printf("\n1. 씨앗 구매\n2. 나가기\n");
    printf("================================================ 상점에 입장했습니다 ===================================================");

    while (1) {
        char input = _getch();
        if (input == '2') break;
		if (input == '1') handle_seed_purchase();
    }

    draw_map();
}
