#pragma once
#include "quest.h"

#define MAX_ACTIVE_QUESTS 3  // 유저가 동시에 가질 수 있는 최대 퀘스트 수

typedef struct {
    Quest active_quests[MAX_ACTIVE_QUESTS]; // 현재 수락한 퀘스트들
    int quest_count;                        // 현재 등록된 퀘스트 수
} QuestInventory;

extern QuestInventory player_quest_list; // 플레이어의 퀘스트 인벤토리

// 함수 선언
void initialize_player_quests();
void init_quest_inventory(QuestInventory* qinv);
int add_quest(QuestInventory* qinv, const Quest* new_quest);
void update_quest_progress(QuestInventory* qinv, const char* crop_name);
void complete_quest(QuestInventory* qinv, int index);
void print_quest_inventory(const QuestInventory* qinv);
