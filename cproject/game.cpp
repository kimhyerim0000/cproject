
#include "farm.h"
#include "item.h"
#include "player.h"
#include "inventory.h"  // 인벤토리 함수 사용

#include <stdio.h>
#include <conio.h>
#include <string.h>

void handle_input(Player* player) {
    char key = _getch();

    if (key == 'z') {
        int x = player->x;
        int y = player->y;

        if (y == 0 && x < FARM_WIDTH) {
            FarmTile* tile = &farm[y][x];

            if (tile->state == TILE_PLOWED) {
                //// 현재 선택된 아이템 이름
                //if (player->current_item >= player->inventory.count) {
                //    printf("선택된 아이템이 유효하지 않습니다.\n");
                //    return;
                //}

                const char* item_name = player->inventory.items[player->current_item].name;
                int qty = get_item_count(&player->inventory, item_name);
                if (qty <= 0) {
                    printf("해당 씨앗이 없습니다: %s\n", item_name);
                    return;
                }

                // crop_list에서 해당 작물 인덱스 찾기
                int crop_index = -1;
                for (int i = 0; i < crop_count; i++) {
                    if (strcmp(crop_list[i].name, item_name) == 0) {
                        crop_index = i;
                        break;
                    }
                }

                if (crop_index == -1) {
                    printf("이 아이템은 작물이 아닙니다: %s\n", item_name);
                    return;
                }

                // 아이템 하나 소비하고 밭에 심기
                if (remove_item(&player->inventory, item_name, 1)) {
                    tile->state = TILE_PLANTED;
                    tile->crop_id = crop_index;
                    tile->grow_day = 0;
                    tile->watered_today = false;
                    printf("🌱 '%s' 씨앗을 심었습니다!\n", item_name);
                }
                else {
                    printf("씨앗 소모 실패.\n");
                }
            }
            else {
                printf("여기는 심을 수 없는 타일입니다.\n");
            }
        }
    }
}
