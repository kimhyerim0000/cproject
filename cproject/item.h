// 수확 가능 작물, 플랜트 가능 씨앗, 아이템
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

typedef struct {
	char name_seeds[MAX_NAME_LEN];  // 씨앗 이름
	Season season;            // 계절
	int grow_days_seeds;            // 성장에 필요한 날짜
	int sell_price_seeds;           // 판매 가격
} Seed;

// 씨앗 리스트
extern Seed seed_list[10];
extern int seed_count;
