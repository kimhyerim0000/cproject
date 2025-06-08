//farm: 경작 관리 내용
#pragma once

#include "base.h"

#define FARM_WIDTH MAP_WIDTH
#define FARM_HEIGHT MAP_HEIGHT


typedef enum {
    TILE_EMPTY,
    TILE_PLOWED,
    TILE_PLANTED,
    TILE_GROWING,
    TILE_READY
} TileState;

typedef struct {
    TileState state;
    int seed_id;
    int grow_day;
    bool watered_today;
} FarmTile;

extern FarmTile farm[FARM_HEIGHT][FARM_WIDTH];

void init_farm();
void update_farm();
void draw_farm();
