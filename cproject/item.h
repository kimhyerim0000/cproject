#pragma once

#define MAX_ITEMS 50
#define MAX_NAME_LEN 20

// 계절 구분용 enum
typedef enum {
    SPRING = 1,
    SUMMER,
    FALL,
    WINTER
} Season;

typedef struct {
    char name[MAX_NAME_LEN];  // 작물 이름
    Season season;            // 계절
    int grow_days;            // 성장에 필요한 날짜
    int sell_price;           // 판매 가격
} Crop;

// 작물 리스트
extern Crop crop_list[10];
extern int crop_count;
