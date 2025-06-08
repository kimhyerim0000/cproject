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

    if (y == 0 && x < FARM_WIDTH) { // 밭 영역인지 확인
        FarmTile* tile = &farm[y][x];

        if (tile->state == TILE_EMPTY) { // 현재 빈상태 [ ]임
            const char* selected_name = player->inventory.items[player->current_item].name;

            // crop_list에서 이름이 같은 작물의 인덱스 찾기
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
                    "'%s'을(를) 밭에 심었습니다.", selected_name);
            }
            else {
                sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                    "'%s'은(는) 심을 수 는 아이템입니다.", selected_name);
            }
        }
        else {
            sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                "여기는 씨앗을 심을 수 없습니다.");
        }
    }
}
void water_crop_at_player_position(Player* player) {
    int x = player->x;
    int y = player->y;

    if (y == 0 && x < FARM_WIDTH) {
        FarmTile* tile = &farm[y][x];

        if (tile->state == TILE_PLANTED || tile->state == TILE_GROWING) {
            tile->watered_today = true;


            sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                "작물에 물을 주었습니다.");
        }
        else {
            sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
                "여기는 작물이 자라고 있지 않습니다.");
        }
    }
    else {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "밭이 아닌 곳에는 물을 줄 수 없습니다.");
    }
}
void harvest_crop_at_player_position(Player* player) {
    int x = player->x;
    int y = player->y;

    if (y == 0 && x < FARM_WIDTH) {
        FarmTile* tile = &farm[y][x];

        if (tile->state == TILE_READY && tile->seed_id != -1) {
            const char* crop_name = crop_list[tile->seed_id].crop_name;

            // 인벤토리에 수확한 작물 추가
            add_item(&player->inventory, crop_name, 1);

            // 타일 초기화
            tile->state = TILE_EMPTY ;
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
    else {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "밭이 아닌 곳에서는 수확할 수 없습니다.");
    }
}
void place_farm_tile(Player* player) {
    int x = player->x;
    int y = player->y;

    if (x < 0 || x >= FARM_WIDTH || y < 0 || y >= FARM_HEIGHT) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "설치할 수 없는 위치입니다.");
        return;
    }

    if (player->farm_tile <= 0) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "밭 타일이 없습니다.");
        return;
    }

    if (farm[y][x].state != TILE_EMPTY) {
        sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
            "해당 위치에 설치할 수 없습니다.");
        return;
    }

    farm[y][x].state = TILE_PLOWED;
    player->farm_tile--;

    sprintf_s(player->last_selected_message, sizeof(player->last_selected_message),
        "밭을 설치했습니다.");
}

