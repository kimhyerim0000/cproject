#pragma once

#define MAX_INVENTORY 20
#define ITEM_NAME_LEN 20

#pragma once

#include "item.h"
#define MAX_INVENTORY 20
#define ITEM_NAME_LEN 20

// �κ��丮 ������ ����ü
typedef struct {
    char name[ITEM_NAME_LEN];
    int quantity;
} InventoryItem;

// �κ��丮 ��ü ����
typedef struct {
    InventoryItem items[MAX_INVENTORY];
    int count;  // ���� ���� ���� ������ ��
	int max_slots; // �ִ� ���� ��
} Inventory;

// �Լ� ����
void init_inventory(Inventory* inv);
int add_item(Inventory* inv, const char* name, int amount);
int remove_item(Inventory* inv, const char* name, int amount);
int get_item_count(Inventory* inv, const char* name);
void print_inventory(const Inventory* inv);
