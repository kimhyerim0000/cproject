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
