#pragma once
#include "quest.h"

#define MAX_ACTIVE_QUESTS 3  // ������ ���ÿ� ���� �� �ִ� �ִ� ����Ʈ ��

typedef struct {
    Quest active_quests[MAX_ACTIVE_QUESTS]; // ���� ������ ����Ʈ��
    int quest_count;                        // ���� ��ϵ� ����Ʈ ��
} QuestInventory;

extern QuestInventory player_quest_list; // �÷��̾��� ����Ʈ �κ��丮

// �Լ� ����
void initialize_player_quests();
void init_quest_inventory(QuestInventory* qinv);
int add_quest(QuestInventory* qinv, const Quest* new_quest);
void update_quest_progress(QuestInventory* qinv, const char* crop_name);
void complete_quest(QuestInventory* qinv, int index);
void print_quest_inventory(const QuestInventory* qinv);
