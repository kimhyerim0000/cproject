#pragma execution_character_set("utf-8")
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "player.h"
#include "base.h"
#include "quest.h"
#include "game.h"
#include "inventory.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int selected_index = 0; // 현재 커서 위치
bool showing_detail = false; // 상세 정보 모드 여부

void draw_quest_list(int selected_index);
void draw_quest_detail(const Quest* quest);

void draw_inventory_box(const Inventory* inv);
void draw_inventory(Player* player);
void draw_quest_info(const Quest* quest);

void draw_inventory(Player* player) {
    int startX = MAP_WIDTH * 2 + 5;
    int startY = 2;
    int width = 28;
    int height = 8;

    // 박스 테두리
    gotoxy(startX, startY);
    printf("┌");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┐");

    for (int i = 1; i < height - 1; i++) {
        gotoxy(startX, startY + i);
        printf("│");
        gotoxy(startX + width - 1, startY + i);
        printf("│");
    }

    gotoxy(startX, startY + height - 1);
    printf("└");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┘");

    // 내부 내용 (ASCII 전용)
    int cx = startX + 2;
    int cy = startY + 1;
    gotoxy(cx, cy++); printf("======Inventory======");
    gotoxy(cx, cy++); printf("Money         : %d", player->money);
    gotoxy(cx, cy++); printf("Current Item  : %d", player->current_item);
    gotoxy(cx, cy++); printf("Slot          : %d", player->inventory.max_slots);
    gotoxy(cx, cy++); printf("Quest Progress: %d", player->quest_progress);

    gotoxy(startX, startY + height + 1);
    
    draw_inventory_box(&player->inventory);
}

void draw_quest_info(const Quest* quest) {
    int x = MAP_WIDTH * 2 + 5;
    int y = 12;
    int width = 45;
    int height = 16;

    gotoxy(x, y - 1);
    printf("📜 퀘스트 정보입니다.");

    gotoxy(x, y);
    printf("┌");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┐");

    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("│");
        gotoxy(x + width - 1, y + i);
        printf("│");
    }

    gotoxy(x, y + height - 1);
    printf("└");
    for (int i = 0; i < width - 2; i++) printf("─");
    

    /*int cx = x + 2;
    int cy = y + 1;
    gotoxy(cx, cy++); printf("===== Quest Info =====");
    gotoxy(cx, cy++); printf("Name     : %s", quest->name);
    gotoxy(cx, cy++); printf("Target   : %d", quest->target_harvest);
    gotoxy(cx, cy++); printf("Progress : %d", quest->current_progress);
    gotoxy(cx, cy++); printf("Reward   : %d", quest->reward_money);
    gotoxy(cx, cy++); printf("Status   : %s", quest->completed ? "완료" : "진행중");

    gotoxy(x, y + height);*/
    
}

void draw_inventory_box(const Inventory* inv) {
    int x = MAP_WIDTH * 2 + 5;
    int y = 12;

    const int width = 45;
    const int visible_rows = 10;  // 고정된 높이
    const int height = visible_rows + 6; // 상하 테두리 포함

    // 박스 상단
    gotoxy(x, y);
    printf("┌");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┐");

    // 박스 측면
    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("│");
        gotoxy(x + width - 1, y + i);
        printf("│");
    }

    // 박스 하단
    gotoxy(x, y + height - 1);
    printf("└");
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("┘");

    // 내부 정보
    int cx = x + 2;
    int cy = y + 1;
    gotoxy(cx, cy++); printf("📦 보유 아이템");

    for (int i = 0; i < inv->count && cy < y + height - 1; i++) {
        const char* name = inv->items[i].name;
        int qty = inv->items[i].quantity;

        // 작물 정보 찾기
        const Crop* found = NULL;
        for (int j = 0; j < crop_count; j++) {
            if (strcmp(crop_list[j].name, name) == 0) {
                found = &crop_list[j];
                break;
            }
        }

        gotoxy(cx, cy++);
        if (found) {
            const char* season_str = "";
            switch (found->season) {
            case SPRING: season_str = "봄"; break;
            case SUMMER: season_str = "여름"; break;
            case FALL:   season_str = "가을"; break;
            case WINTER: season_str = "겨울"; break;
            }
            printf(" - %s (%s, %d일, ₩%d): %d개",
                found->name, season_str, found->grow_days, found->sell_price, qty);
        }
        else {
            printf(" - %s: %d개", name, qty);
        }
    }
}void draw_quest_list(int selected_index) {
    int box_x = MAP_WIDTH * 2 + 5; // 테두리 시작 위치와 동일
    int box_y = 12;
    int width = 45;
    int height = 10;

    int text_x = box_x + 2;  // 여백 고려
    int text_y = box_y + (height - active_quest_count) / 2;

    for (int i = 0; i < active_quest_count; i++) {
        gotoxy(text_x, text_y + i);
        if (active_quests[i]) {
            printf("> %s", active_quests[i]->name);
        }
        else {
            printf(" (퀘스트 정보 없음)");
        }
    }


}

void draw_quest_detail(const Quest* quest) {

}



void draw_map(Player* player) {
    system("cls");
    const char* weather_str = (player->weather == 0) ? "☀️ 맑음" : "🌧️ 비";
    printf("📅 Day %d  🍂 Season %d  ⚡ Energy: %d  날씨: %s\n",
        player->day, player->season, player->energy, weather_str);
    printf(" 위치: (%d, %d)\n\n", player->x, player->y);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == player->x && y == player->y)
                printf("@ ");
            else
                printf(". ");
        }
        printf("\n");
    }

    menuDraw();
}

void update_day(Player* player) {
    player->day++;
    if (player->day > 14) {
        player->day = 1;
        player->season++;
        printf(" 새로운 계절이 시작되었습니다! (Season %d)\n", player->season);
    }
    player->energy = max_energy;
    player->weather = rand() % 2; // 랜덤 날씨
}

void run_game() {
    

    srand((unsigned int)time(NULL));

    Player player;
    init_player(&player);
    player.x = 5;
    player.y = 2;

    // 퀘스트 등록 (최대 3개)
    setup_quests();

    // 상태 변수
    bool inventory_visible = false;
    bool quest_visible = false;
    bool showing_detail = false;
    int selected_index = 0;

    draw_map(&player);

    while (1) {
        if (_kbhit()) {
            char input = _getch();

            // 방향키 조합 처리 (0 또는 224는 특수키 prefix)
            if (input == 0 || input == -32) {
                input = _getch();  // 방향키 실제 코드
                if (quest_visible && !showing_detail) {
                    if (input == 72 && selected_index > 0) selected_index--; // ↑
                    if (input == 80 && selected_index < active_quest_count - 1) selected_index++; // ↓
                }
                continue;
            }

            switch (input) {
            case 'w': case 'W':
                if (player.y > 0) player.y--;
                break;
            case 's': case 'S':
                if (player.y < MAP_HEIGHT - 1) player.y++;
                break;
            case 'a': case 'A':
                if (player.x > 0) player.x--;
                break;
            case 'd': case 'D':
                if (player.x < MAP_WIDTH - 1) player.x++;
                break;
            case 'q': case 'Q':
                printf(" 잠자기 선택! 하루가 지났습니다.\n");
                update_day(&player);
                Sleep(1000);
                break;
            case 'i': case 'I':
                inventory_visible = !inventory_visible;
                quest_visible = false;
                break;
            case 'e': case 'E':
                quest_visible = !quest_visible;
                inventory_visible = false;
                showing_detail = false;
                selected_index = 0;
                break;
            case 16: 
                if (quest_visible) {
                    showing_detail = !showing_detail;
                }
                break;
            }

            // 에너지 처리
            if (input != 'q' && input != 'Q' && input != 16) {
                player.energy--;
                if (player.energy <= 0) {
                    printf(" 에너지가 다 떨어졌습니다. 자동으로 하루가 지납니다.\n");
                    update_day(&player);
                    Sleep(1000);
                }
            }
            //맵 그리기
            draw_map(&player);

			//퀘스트 그리기
            //인벤토리 그리기
            if (inventory_visible) {
                draw_inventory(&player);
            }// 
            else if (quest_visible) {
                draw_quest_info(active_quests[selected_index]); // ← 테두리 항상 그림
                if (showing_detail) {
                    draw_quest_detail(active_quests[selected_index]);
                }
                else {
                    draw_quest_list(selected_index);
                }
            }

        }
    }
}

