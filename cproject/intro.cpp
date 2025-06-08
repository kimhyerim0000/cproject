#pragma execution_character_set("utf-8")
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "base.h"

void draw_title_screen() {
    system("chcp 65001 > nul");
    system("cls");

    const char* title = R"(
            ██╗  ██╗ █████╗ ██████╗ ██╗   ██╗███████╗███████╗████████╗     ███████╗ █████╗  ██████╗  █████╗ 
            ██║  ██║██╔══██╗██╔══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝     ██╔════╝██╔══██╗██╔════╝ ██╔══██╗
            ███████║███████║██████╔╝██║   ██║█████╗  █████╗     ██║        █████╗  ███████║██║  ███╗███████║
            ██╔══██║██╔══██║██╔═══╝ ██║   ██║██╔══╝  ██╔══╝     ██║        ██╔══╝  ██╔══██║██║   ██║██╔══██║
            ██║  ██║██║  ██║██║     ╚██████╔╝███████╗███████╗   ██║        ███████╗██║  ██║╚██████╔╝██║  ██║
            ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ ╚══════╝╚══════╝   ╚═╝        ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝
    )";

    int console_width = 120;
    int console_height = 30;
    int title_lines = 6;
    int start_y = (console_height / 2) - (title_lines / 2) - 2; // 위에서 살짝 내림
    int start_x = 15;  // 여유 공간

    gotoxy(start_x, start_y);
    printf("\033[1;36m%s\033[0m\n", title);

    gotoxy(console_width / 2 - 25, start_y + title_lines + 2);
    printf("🌾 Press any key to begin your farming journey... 🌾");
}


void wait_for_keypress() {
    while (!_kbhit()) {
        Sleep(100);
    }
    _getch();
}

void show_intro() {
    SetConsole();
    draw_title_screen();
    wait_for_keypress();
    system("cls");
}
