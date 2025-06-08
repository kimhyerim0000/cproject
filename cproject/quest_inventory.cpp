#pragma execution_character_set("utf-8")
#include "quest_inventory.h"
#include <string.h>
#include <stdio.h>
#include "player.h"
QuestInventory player_quest_list;

void initialize_player_quests() {
    init_quest_inventory(&player_quest_list);

    Quest q1 = { "감자 수확왕", 5, 0, 300, false, "감자" };
    Quest q2 = { "당근 장인",   7, 0, 350, false, "당근" };
    Quest q3 = { "토마토 대작전", 6, 0, 400, false, "토마토" };
    Quest q4 = { "옥수수 마스터", 8, 0, 500, false, "옥수수" };
    Quest q5 = { "블루베리 꿈나무",    10, 0, 600, false, "블루베리" };
    Quest q6 = { "단호박 연구가",      4, 0, 550, false, "단호박" };
    Quest q7 = { "무 수확 챌린지",     6, 0, 330, false, "무" };
    Quest q8 = { "고구마 달인",        7, 0, 420, false, "고구마" };
    Quest q9 = { "시금치 캐기",        5, 0, 310, false, "시금치" };
    Quest q10 = { "브로콜리 파티",      6, 0, 470, false, "브로콜리" };

    add_quest(&player_quest_list, &q1);
    add_quest(&player_quest_list, &q2);
    add_quest(&player_quest_list, &q3);
    add_quest(&player_quest_list, &q4);
    add_quest(&player_quest_list, &q5);
    add_quest(&player_quest_list, &q6);
    add_quest(&player_quest_list, &q7);
    add_quest(&player_quest_list, &q8);
    add_quest(&player_quest_list, &q9);
    add_quest(&player_quest_list, &q10);
    
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
// 뭐야 메서드 만들어놓고 왜 안쓰는데
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

//// 퀘스트 제거하고 땡기는건데 안쓸거임. 안쓰는 메서드임
//void complete_quest(QuestInventory* qinv, int index) {
//    if (index < 0 || index >= qinv->quest_count) return;
//
//    // 완료된 퀘스트를 제거하고 앞으로 땡김
//    for (int i = index; i < qinv->quest_count - 1; i++) {
//        qinv->active_quests[i] = qinv->active_quests[i + 1];
//    }
//
//    qinv->quest_count--;
//
//
//}
