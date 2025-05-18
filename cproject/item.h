// ��Ȯ ���� �۹�, �÷�Ʈ ���� ����, ������
#pragma once

#define MAX_ITEMS 50
#define MAX_NAME_LEN 20

// ���� ���п� enum
typedef enum {
    SPRING = 1,
    SUMMER,
    FALL,
    WINTER
} Season;

typedef struct {
    char name[MAX_NAME_LEN];  // �۹� �̸�
    Season season;            // ����
    int grow_days;            // ���忡 �ʿ��� ��¥
    int sell_price;           // �Ǹ� ����
} Crop;

// �۹� ����Ʈ
extern Crop crop_list[10];
extern int crop_count;

typedef struct {
	char name_seeds[MAX_NAME_LEN];  // ���� �̸�
	Season season;            // ����
	int grow_days_seeds;            // ���忡 �ʿ��� ��¥
	int sell_price_seeds;           // �Ǹ� ����
} Seed;

// ���� ����Ʈ
extern Seed seed_list[10];
extern int seed_count;
