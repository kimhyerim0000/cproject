#include "inventory.h"
#include <string.h>
#include <stdio.h>

void init_inventory(Inventory* inv) {
    inv->count = 0;
    inv->max_slots = MAX_INVENTORY;
    for (int i = 0; i < MAX_INVENTORY; i++) {
        inv->items[i].name[0] = '\0';
        inv->items[i].quantity = 0;
    }
}

int add_item(Inventory* inv, const char* name, int amount) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name , name) == 0) {
            inv->items[i].quantity += amount;
            return 1;
        }
    }
    if (inv->count < MAX_INVENTORY) {
        strcpy_s(inv->items[inv->count].name, name);
        inv->items[inv->count].quantity = amount;
        inv->count++;
        return 1;
    }
    return 0; // 인벤토리 가득 참
}

int remove_item(Inventory* inv, const char* name, int amount) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            if (inv->items[i].quantity >= amount) {
                inv->items[i].quantity -= amount;
                if (inv->items[i].quantity == 0) {
                    for (int j = i; j < inv->count - 1; j++) {
                        inv->items[j] = inv->items[j + 1];
                    }
                    inv->count--;
                }
                return 1;
            }
            return 0; // 수량 부족
        }
    }
    return 0; // 해당 아이템 없음
}

int get_item_count(Inventory* inv, const char* name) {
    for (int i = 0; i < inv->count; i++) {
        if (strcmp(inv->items[i].name, name) == 0) {
            return inv->items[i].quantity;
        }
    }
    return 0;
}

void print_inventory(const Inventory* inv) {
    printf("📦 인벤토리:\n");
    for (int i = 0; i < inv->count; i++) {
        printf(" - %s: %d개\n", inv->items[i].name, inv->items[i].quantity);
    }
}
