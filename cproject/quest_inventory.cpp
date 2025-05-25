#pragma execution_character_set("utf-8")
#include "quest_inventory.h"
#include <string.h>
#include <stdio.h>
QuestInventory player_quest_list;

void initialize_player_quests() {
    init_quest_inventory(&player_quest_list);

    Quest q1 = { "감자 수확왕", 5, 0, 300, false, "감자" };
    Quest q2 = { "당근 장인",   7, 0, 350, false, "당근" };
    Quest q3 = { "토마토 대작전", 6, 0, 400, false, "토마토" };

    add_quest(&player_quest_list, &q1);
    add_quest(&player_quest_list, &q2);
    add_quest(&player_quest_list, &q3);
}

void init_quest_inventory(QuestInventory* qinv) {
    qinv->quest_count = 0;
    for (int i = 0; i < MAX_ACTIVE_QUESTS; i++) {
        qinv->active_quests[i].completed = false;
        qinv->active_quests[i].current_progress = 0;
        qinv->active_quests[i].target_crop[0] = '\0';
        qinv->active_quests[i].name[0] = '\0';
        qinv->active_quests[i].reward_money = 0;
        qinv->active_quests[i].target_harvest = 0;
    }
}

int add_quest(QuestInventory* qinv, const Quest* new_quest) {
    if (qinv->quest_count >= MAX_ACTIVE_QUESTS) return 0; // 슬롯 부족

    qinv->active_quests[qinv->quest_count] = *new_quest;  // 값 복사
    qinv->quest_count++;
    return 1;
}

void update_quest_progress(QuestInventory* qinv, const char* crop_name) {
    for (int i = 0; i < qinv->quest_count; i++) {
        Quest* quest = &qinv->active_quests[i];

        if (!quest->completed && strcmp(quest->target_crop, crop_name) == 0) {
            quest->current_progress++;

            if (quest->current_progress >= quest->target_harvest) {
                quest->completed = true;
            }
        }
    }
}

void complete_quest(QuestInventory* qinv, int index) {
    if (index < 0 || index >= qinv->quest_count) return;

    // 완료된 퀘스트를 제거하고 앞으로 땡김
    for (int i = index; i < qinv->quest_count - 1; i++) {
        qinv->active_quests[i] = qinv->active_quests[i + 1];
    }

    qinv->quest_count--;
}
