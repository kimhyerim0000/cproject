#pragma execution_character_set("utf-8")
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

#include "quest_inventory.h"
#include "player.h"
#include "base.h"
#include "quest.h"
#include "game.h"
#include "inventory.h"
#include "farm.h"

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

int selected_index = 0; // 현재 커서 위치
bool showing_detail = false; // 상세 정보 모드 여부

void draw_quest_list();
void draw_inventory_box(const Inventory* inv, int selected_index);
void draw_inventory();
void draw_quest_info();

void draw_inventory() {
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
    gotoxy(cx, cy++); printf("Money         : %d", player.money);
    gotoxy(cx, cy++); printf("Farm tile     : %d", player.farm_tile);
    gotoxy(cx, cy++); printf("Quest Progress: %d", player.quest_progress);

    gotoxy(startX, startY + height + 1);
    
    draw_inventory_box(&player.inventory, player.selected_index);

    int msg_x = MAP_WIDTH * 2 + 5 + 2;
    int msg_y = 12 + 16;

    gotoxy(msg_x, msg_y);
    printf("%s", player.last_selected_message);

}

void draw_quest_info() {
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
}

void draw_inventory_box(const Inventory* inv, int selected_index) {
    int x = MAP_WIDTH * 2 + 5;
    int y = 12;

    const int width = 45;
    const int visible_rows = 10;
    const int height = visible_rows + 6;

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
    printf("┘");

    int cx = x + 2;
    int cy = y + 1;
    gotoxy(cx, cy++); printf("📦 Inventory");

    // 🔹 가상 항목: Farm Tile seletecd_index==0 일때임.
    gotoxy(cx, cy);
    if (selected_index == 0)
        printf(" > ");
    else
        printf("   ");
    printf("Farm Tile: %d개", player.farm_tile);
    cy++;

    // 🔹 실제 인벤토리 아이템들 (selected_index - 1 비교)
    for (int i = 0; i < inv->count && cy < y + height - 1; i++) {
        const char* name = inv->items[i].name;
        int qty = inv->items[i].quantity;

        const Seed* found = NULL;
        for (int j = 0; j < crop_count; j++) {
            if (strcmp(seed_list[j].seed_name, name) == 0) {
                found = &seed_list[j];
                break;
            }
        }
        gotoxy(cx, cy);
        // 커서 위치: +1 오프셋
        if (i + 1 == selected_index)
            printf(" > ");
        else
            printf("   ");
        if (found) {
            const char* season_str = "";
            switch (found->season) {
            case SPRING: season_str = "봄"; break;
            case SUMMER: season_str = "여름"; break;
            case FALL:   season_str = "가을"; break;
            case WINTER: season_str = "겨울"; break;
            }
            printf("%s (%s, %d일, ₩%d): %d개",
                found->seed_name, season_str, found->seed_grow, found->seed_sell_price, qty);
        }
        else {
            printf("%s: %d개", name, qty);
        }
        cy++;
    }

}void draw_quest_list() {
    int x = MAP_WIDTH * 2 + 5 + 2;
    int y = 13;

    gotoxy(x, y - 1);

    for (int i = 0; i < player_quest_list.quest_count; i++) {
        gotoxy(x, y + i);

        // 커서 위치 표시
        if (i == player.selected_quest_index)
            printf("> ");
        else
            printf("  ");

        // 퀘스트 이름과 상태 출력
        const Quest* q = &player_quest_list.active_quests[i];
        printf("%s (%s: %d/%d)  %s",
            q->name,
            q->target_crop,
            q->current_progress,
            q->target_harvest,
            q->completed ? "[완료]" : "");
    }
}

void draw_map() {
    system("cls");
    const char* weather_str = (player.weather == 0) ? "☀️ 맑음" : "🌧️ 비";
    printf("📅 Day %d  🍂 Season %d  ⚡ Energy: %d  날씨: %s\n",
        player.day, player.season, player.energy, weather_str);
    printf(" 위치: (%d, %d)\n\n", player.x, player.y);

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                // 첫 줄 5칸만 밭
                FarmTile tile = farm[y][x];

                if (player.x == x && player.y == y) {
                    printf("@ ");
                }
                else {
                    switch (tile.state) {
                    case TILE_PLOWED:  printf("[ ]"); break;
                    case TILE_PLANTED: printf("[s]"); break;
                    case TILE_GROWING: printf("[g]"); break;
                    case TILE_READY:   printf("[R]"); break;
                    case TILE_EMPTY:   printf(". "); break; // 빈 밭
                    default:           printf(". "); break;  // 그 외는 기본 땅
                    }
                }

            }
            printf("\n");
        }


    menuDraw();
}

void update_day() {
    player.day++;
    if (player.day > 14) {
        player.day = 1;
        player.season++;
        printf(" 새로운 계절이 시작되었습니다! (Season %d)\n", player.season);
    }
    player.energy = max_energy;
    player.weather = rand() % 2; // 랜덤 날씨
    update_farm();
    // 비 오는 날 자동 물주기
    if (player.weather == 1) {
        for (int y = 0; y < FARM_HEIGHT; y++) {
            for (int x = 0; x < FARM_WIDTH; x++) {
                FarmTile* tile = &farm[y][x];

                // 심겨 있는 상태면 물 주기
                if (tile->state == TILE_PLANTED || tile->state == TILE_GROWING) {
                    tile->watered_today = true;
                }
            }
        }
    }

}
void draw_quest_message() {
    int msg_x = MAP_WIDTH * 2 + 5 + 2;
    int msg_y = 12 + 16;

    gotoxy(msg_x, msg_y);
    printf("                                             "); // 기존 메시지 지움
    gotoxy(msg_x, msg_y);
    printf("%s", player.last_selected_message);
}
#include <windows.h>  // Sleep 함수 사용

#include <windows.h>
#include <stdio.h>

#include <windows.h>
#include <stdio.h>

#include <windows.h>
#include <stdio.h>

#define CONSOLE_WIDTH  100
#define CONSOLE_HEIGHT 30

void draw_firework_pattern(int baseX, int baseY, int frame) {
    // 패턴 회전: 0 ~ 3 (총 4단계 회전)
    int phase = frame % 4;

    switch (phase) {
    case 0:
        gotoxy(baseX, baseY);     printf("   |   ");
        gotoxy(baseX, baseY + 1); printf("  -o-  ");
        gotoxy(baseX, baseY + 2); printf("   |   ");
        break;
    case 1:
        gotoxy(baseX, baseY);     printf("  \\|/  ");
        gotoxy(baseX, baseY + 1); printf("  -o-  ");
        gotoxy(baseX, baseY + 2); printf("  /|\\  ");
        break;
    case 2:
        gotoxy(baseX, baseY);     printf("   *   ");
        gotoxy(baseX, baseY + 1); printf("  ***  ");
        gotoxy(baseX, baseY + 2); printf("   *   ");
        break;
    case 3:
        gotoxy(baseX, baseY);     printf("  /|\\  ");
        gotoxy(baseX, baseY + 1); printf("  -o-  ");
        gotoxy(baseX, baseY + 2); printf("  \\|/  ");
        break;
    }
}

void show_quest_completion_fireworks_fullscreen(const Quest* q) {
    for (int frame = 0; frame < 24; frame++) {
        system("cls");

        // 폭죽 여러 개 출력 (격자 패턴)
        for (int y = 2; y < CONSOLE_HEIGHT - 6; y += 6) {
            for (int x = 4; x < CONSOLE_WIDTH - 10; x += 16) {
                draw_firework_pattern(x, y, frame);
            }
        }

        // 중앙 퀘스트 완료 메시지
        int msgX = CONSOLE_WIDTH / 2 - 20;
        int msgY = CONSOLE_HEIGHT / 2;

        gotoxy(msgX, msgY - 2);
        printf("╔════════════════════════════════════════╗");
        gotoxy(msgX, msgY - 1);
        printf("║         🎉 퀘스트 완료 축하 🎉        ║");
        gotoxy(msgX, msgY);
        printf("║  퀘스트명: %-26s                       ║", q->name);
        gotoxy(msgX, msgY + 1);
        printf("║  보상 금액: %5d G                      ║", q->reward_money);
        gotoxy(msgX, msgY + 2);
        printf("╚════════════════════════════════════════╝");

        gotoxy(msgX + 5, msgY + 4);
        printf("3초간 축하 후 게임으로 돌아갑니다...");

        Sleep(120);  // 프레임 간격
    }
}




// 사용자 키보드 입력 처리
void run_game() {
    srand((unsigned int)time(NULL));

    init_player(&player);
	init_farm();
    initialize_player_quests();
    player.x = 5;
    player.y = 2;

    // 퀘스트 등록 (최대 3개)
    //setup_quests();

    // 상태 변수
    bool inventory_visible = false;
    bool quest_visible = false;
    bool showing_detail = false;

    draw_map();

    while (1) {
        if (_kbhit()) {
            char input = _getch();
            
            if (input == 0 || input == -32) {
                input = _getch();  // 두 번째 입력이 실제 방향키
                int max_index = player.inventory.count;  // 실제 아이템 개수
                max_index += 1;  // 가상 항목(Farm Tile)을 포함

                if (input == 72 && player.selected_index > 0) {
                    player.selected_index--;
                }
                if (input == 80 && player.selected_index < max_index - 1) {
                    player.selected_index++;
                }
                else if (quest_visible && !inventory_visible) {
                    if (input == 72 && player.selected_quest_index > 0) {
                        player.selected_quest_index--;
                    }
                    if (input == 80 && player.selected_quest_index < player_quest_list.quest_count - 1) {
                        player.selected_quest_index++;
                    }
                }
            }
            if (input == 13 && inventory_visible) {
                player.current_item = player.selected_index;

                if (player.selected_index == 0) {
                    // Farm Tile 선택됨
                    sprintf_s(player.last_selected_message, sizeof(player.last_selected_message),
                        "'Farm Tile'을 선택했습니다.");
                    place_farm_tile(&player);  // 설치 시도
                }
                else {
                    // 일반 인벤토리 아이템 선택
                    player.current_item = player.selected_index - 1;  // ✅ 핵심 수정
                    const char* name = player.inventory.items[player.current_item].name;
                    sprintf_s(player.last_selected_message, sizeof(player.last_selected_message),
                        "'%s'을 선택했습니다.", name);
                }

            }else if (input == 13 && quest_visible) {
                int idx = player.selected_quest_index;

                if (idx >= 0 && idx < player_quest_list.quest_count) {
                    Quest* q = &player_quest_list.active_quests[idx];
                    const char* target = q->target_crop;

                    // 인벤토리에서 해당 작물 찾아서 제거
                    int found = 0;
                    for (int i = 0; i < player.inventory.count; i++) {
                        if (strcmp(player.inventory.items[i].name, target) == 0 &&
                            player.inventory.items[i].quantity > 0) {

                            // 퀘스트 진행 + 아이템 제거
                            q->current_progress++;
                            remove_item(&player.inventory, target, 1);

                            // 퀘스트 완료 체크
                            if (q->current_progress >= q->target_harvest) {
                                q->completed = true;
								player.money += q->reward_money;
                                player.quest_progress--;
                                show_quest_completion_fireworks_fullscreen(q);
                            }

                            sprintf_s(player.last_selected_message, sizeof(player.last_selected_message),
                                "'%s' 납품 완료! 진행도: %d/%d", target, q->current_progress, q->target_harvest);
                            found = 1;
                            break;
                        }
                    }

                    if (!found) {
                        sprintf_s(player.last_selected_message, sizeof(player.last_selected_message),
                            "인벤토리에 '%s'이(가) 없습니다.", target);
                    }
                }
            }

            if (input == 49 && inventory_visible ) {
				handle_input(&player); 
            }
            if (input == 50) {
                //물주기 2번
				water_crop_at_player_position(&player);
            }
			if (input == 51) {
				//수확하기 3번
				harvest_crop_at_player_position(&player);
			}

            // 방향키 처리 -> player.cpp로 옮기기
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
                update_day();
                Sleep(1000);
                break;
            case 'i': case 'I':
                inventory_visible = !inventory_visible;
                quest_visible = false;

                if (!inventory_visible) {
                    strcpy_s(player.last_selected_message, sizeof(player.last_selected_message), "");
                }
                break;
            case 'e': case 'E':
                quest_visible = !quest_visible;
                inventory_visible = false;
                showing_detail = false;
                selected_index = 0;
                break;
            }
            // 에너지 처리
            if (input != 'q' && input != 'Q' && input != 16) {
                player.energy--;
                if (player.energy <= 0) {
                    printf(" 에너지가 다 떨어졌습니다. 자동으로 하루가 지납니다.\n");
                    update_day();
                    Sleep(1000);
                }
            }
            //맵 그리기
            draw_map();

			//퀘스트 그리기
            //인벤토리 그리기
            if (inventory_visible) {
                draw_inventory();
            }// 
            else if (quest_visible) {
                draw_quest_info(); // ← 테두리 항상 그림
				draw_quest_list();
                draw_quest_message();
                if (showing_detail) {
                    //draw_quest_detail(active_quests[selected_index]);
                }
               
            }

        }
    }
}

