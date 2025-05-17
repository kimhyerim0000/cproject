#pragma once

#define MAX_INVENTORY 20
#define ITEM_NAME_LEN 20

#pragma once

#include "item.h"
#define MAX_INVENTORY 20
#define ITEM_NAME_LEN 20

// 인벤토리 아이템 구조체
typedef struct {
    char name[ITEM_NAME_LEN];
    int quantity;
} InventoryItem;

// 인벤토리 전체 구조
typedef struct {
    InventoryItem items[MAX_INVENTORY];
    int count;  // 현재 보유 중인 아이템 수
	int max_slots; // 최대 슬롯 수
} Inventory;

// 함수 선언
void init_inventory(Inventory* inv);
int add_item(Inventory* inv, const char* name, int amount);
int remove_item(Inventory* inv, const char* name, int amount);
int get_item_count(Inventory* inv, const char* name);
void print_inventory(const Inventory* inv);
