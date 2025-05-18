//farm: 경작 관리 내용
#pragma once

#define FARM_WIDTH 5
#define FARM_HEIGHT 1


typedef enum {
    TILE_EMPTY,
    TILE_PLOWED,
    TILE_PLANTED,
    TILE_GROWING,
    TILE_READY
} TileState;

typedef struct {
    TileState state;
    int crop_id;
    int grow_day;
    bool watered_today;
} FarmTile;

extern FarmTile farm[FARM_HEIGHT][FARM_WIDTH];

void init_farm();
