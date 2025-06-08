#pragma execution_character_set("utf-8")
#include "farm.h"
#include "item.h"
#include "player.h"
#include "inventory.h"  // 인벤토리 함수 사용

#include <stdio.h>
#include <conio.h>
#include <string.h>

void handle_input(Player* player) {
    int x = player->x;
    int y = player->y;

    // 범위 체크
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "맵 범위를 벗어났습니다.");
        return;
    }

    FarmTile* tile = &farm[y][x];

    // 오직 갈아엎은 땅(PLOWED)에만 심기 가능
    if (tile->state == TILE_PLOWED) {
        const char* selected_name = player->inventory.items[player->current_item].name;

        // 씨앗 이름과 매칭
        int seed_index = -1;
        for (int i = 0; i < seed_count; i++) {
            if (strcmp(seed_list[i].seed_name, selected_name) == 0) {
                seed_index = i;
                break;
            }
        }

        if (seed_index != -1) {
            tile->state = TILE_PLANTED;
            tile->seed_id = seed_index;
            tile->grow_day = 0;
            tile->watered_today = false;

            remove_item(&player->inventory, selected_name, 1);

            sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                "'%s'을(를) 심었습니다.", selected_name);
        }
        else {
            sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                "'%s'은(는) 씨앗이 아닙니다.", selected_name);
        }
    }
    else {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "이 위치에는 심을 수 없습니다.");
    }
}

void water_crop_at_player_position(Player* player) {
    int x = player->x;
    int y = player->y;

    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "맵을 벗어난 위치입니다.");
        return;
    }

    FarmTile* tile = &farm[y][x];

    if (tile->state == TILE_PLANTED || tile->state == TILE_GROWING) {
        tile->watered_today = true;
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "작물에 물을 주었습니다.");
    }
    else {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "이 위치에는 물을 줄 수 없습니다.");
    }
}

void harvest_crop_at_player_position(Player* player) {
    int x = player->x;
    int y = player->y;

    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "맵을 벗어난 위치입니다.");
        return;
    }

    FarmTile* tile = &farm[y][x];

    if (tile->state == TILE_READY && tile->seed_id != -1) {
        const char* crop_name = crop_list[tile->seed_id].crop_name;

        add_item(&player->inventory, crop_name, 1);

        tile->state = TILE_EMPTY;
        tile->seed_id = -1;
        tile->grow_day = 0;
        tile->watered_today = false;

        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "'%s'을(를) 수확했습니다!", crop_name);
    }
    else {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "수확할 수 있는 작물이 없습니다.");
    }
}

void place_farm_tile(Player* player) {
    int y = player->y;
    int startX = player->x;

    if (y < 0 || y >= MAP_HEIGHT) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "맵을 벗어난 위치입니다. (y)");
        return;
    }

    if (startX < 0 || startX + 4 >= MAP_WIDTH) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "오른쪽으로 밭을 5칸 설치할 공간이 부족합니다.");
        return;
    }

    if (player->farm_tile <= 0) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "밭 타일이 없습니다.");
        return;
    }

    // 설치
    for (int dx = 0; dx < 5; dx++) {
        int x = startX + dx;
        if (farm[y][x].state == TILE_EMPTY) {
            farm[y][x].state = TILE_PLOWED;
        }
    }

    player->farm_tile--;
    sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
        "밭을 가로로 5칸 설치했습니다.");
}


