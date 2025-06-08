#pragma execution_character_set("utf-8")
// thankYou.cpp
#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "base.h"

void thank_you() {
    system("chcp 65001 > nul");
    system("cls");

    const char* lines[] = {
            "████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗     ██╗   ██╗ ██████╗ ██╗   ██╗",
            "╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝     ╚██╗ ██╔╝██╔═══██╗██║   ██║",
            "   ██║   ███████║███████║██╔██╗ ██║██║██╔╝       ╚████╔╝ ██║   ██║██║   ██║",
            "   ██║   ██╔══██║██╔══██║██║╚██╗██║█████╔╝        ╚██╔╝  ██║   ██║██║   ██║",
            "   ██║   ██║  ██║██║  ██║██║ ╚████║██╔═██╗         ██║   ╚██████╔╝╚██████╔╝",
            "   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝        ╚═╝   ╚══════╝  ╚═════╝ "
    };
    int console_width = 120;
    int console_height = 30;
    int title_lines = 6;
    int start_y = (console_height / 2) - (title_lines / 2) - 2; // 위에서 살짝 내림
    int start_x = 15;  // 여유 공간

    for (int i = 0; i < 6; i++) {
        gotoxy(start_x, start_y + i);
        printf("%s\n", lines[i]);
    }

    gotoxy(console_width / 2 - 25, start_y + title_lines + 2);
    printf("모든 퀘스트를 통과하였습니다! ");
    gotoxy(console_width / 2 - 25, start_y + title_lines + 2);
    printf("\n\n                            당신은 HAPVEET EAGA 마을의 이장이 될 자격이 생겼습니다!");
    _getch();
}
