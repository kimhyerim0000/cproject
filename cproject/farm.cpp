#include "farm.h"
#include "item.h"
#include <stdio.h>

FarmTile farm[FARM_HEIGHT][FARM_WIDTH];



void init_farm() {
    for (int y = 0; y < FARM_HEIGHT; y++) {
        for (int x = 0; x < FARM_WIDTH; x++) {
            farm[y][x].state = TILE_EMPTY;
            farm[y][x].seed_id = -1;
            farm[y][x].grow_day = 0;
            farm[y][x].watered_today = false;
        }
    }
    // 기본 텃밭 5칸 설정
    for (int x = 0; x < 5; x++) {
        farm[0][x].state = TILE_PLOWED;
    }
}
void update_farm() {
    for (int y = 0; y < FARM_HEIGHT; y++) {
        for (int x = 0; x < FARM_WIDTH; x++) {
            FarmTile* tile = &farm[y][x];
            if ((tile->state== TILE_GROWING|| tile->state == TILE_PLANTED) && tile->watered_today) {
                tile->grow_day++; //얘는 심긴 씨앗이 며칠째인지 세는 변수
                int required = seed_list[tile->seed_id].seed_grow;
                if (tile->grow_day >= required) {
                    tile->state = TILE_READY;
                }
                else {
                    tile->state = TILE_GROWING;
                }
                tile->watered_today = false; // 하루 지났으므로 초기화
            }
        }
    }
}

void draw_farm() {
    for (int y = 0; y < FARM_HEIGHT; y++) {
        for (int x = 0; x < FARM_WIDTH; x++) {
            FarmTile tile = farm[y][x];  // ← 이 줄이 있어야 switch에서 tile.state 사용 가능

            switch (tile.state) {
            case TILE_PLOWED:  printf("[ ]"); break;
            case TILE_PLANTED: printf("[s]"); break;
            case TILE_GROWING: printf("[g]"); break;
            case TILE_READY:   printf("[R]"); break;
            case TILE_EMPTY:   printf(". "); break;   // 수정된 부분!
            default:           printf(". "); break;
            }
        }
        printf("\n");
    }
}

