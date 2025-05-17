#include "quest.h"
#include <string.h>
#include <stdio.h>

#define MAX_ACTIVE_QUESTS 3
// 전체 퀘스트 목록 정의
Quest quest_list[MAX_TOTAL_QUESTS] = {
    {"감자 수확왕",        5, 0, 300, false, "감자"},
    {"당근 장인",          7, 0, 350, false, "당근"},
    {"토마토 대작전",      6, 0, 400, false, "토마토"},
    {"옥수수 마스터",      8, 0, 500, false, "옥수수"},
    {"블루베리 꿈나무",    10, 0, 600, false, "블루베리"},
    {"단호박 연구가",      4, 0, 550, false, "단호박"},
    {"무 수확 챌린지",     6, 0, 330, false, "무"},
    {"고구마 달인",        7, 0, 420, false, "고구마"},
    {"시금치 캐기",        5, 0, 310, false, "시금치"},
    {"브로콜리 파티",      6, 0, 470, false, "브로콜리"},
};

int total_quests = sizeof(quest_list) / sizeof(quest_list[0]);



// quest.cpp
Quest quest_list[MAX_TOTAL_QUESTS];
int total_quests = 0;
Quest* active_quests[MAX_ACTIVE_QUESTS] = { 0 };
int active_quest_count = 0;

void setup_quests() {
    active_quest_count = 0;

    if (total_quests >= 3) {
        active_quests[0] = &quest_list[0];
        active_quests[1] = &quest_list[1];
        active_quests[2] = &quest_list[2];
        active_quest_count = 3;
    }
    else {
        for (int i = 0; i < total_quests; i++) {
            active_quests[i] = &quest_list[i];
            active_quest_count++;
        }
    }
}
void init_quest(Quest* q, const char* name, const char* crop_name, int target, int reward) {
    strcpy_s(q->name, sizeof(q->name), name);
    strcpy_s(q->target_crop, sizeof(q->target_crop), crop_name);
    q->target_harvest = target;
    q->current_progress = 0;
    q->reward_money = reward;
    q->completed = false;
}

// 🔐 퀘스트 등록 (진행 중 최대 3개까지만)
bool register_quest(Quest* q) {
    if (active_quest_count >= MAX_ACTIVE_QUESTS) {
        printf("❌ 이미 3개의 퀘스트를 진행 중입니다.\n");
        return false;
    }
    active_quests[active_quest_count++] = q;
    printf("🆕 퀘스트 [%s] 등록 완료!\n", q->name);
    return true;
}

// 🎯 수확 작물 이름과 비교하여 퀘스트 진행도 증가
void update_all_quest_progress(const char* crop_name, int harvested) {
    for (int i = 0; i < active_quest_count; i++) {
        update_quest_progress(active_quests[i], crop_name, harvested);
    }
}

void update_quest_progress(Quest* q, const char* harvested_crop_name, int harvested_amount) {
    if (q->completed) return;

    if (strcmp(q->target_crop, harvested_crop_name) == 0) {
        q->current_progress += harvested_amount;
        if (q->current_progress >= q->target_harvest) {
            q->completed = true;
            printf(" ✅ 퀘스트 [%s] 완료됨!\n", q->name);
        }
        else {
            printf(" ➕ 퀘스트 [%s] 진행 중: %d/%d\n", q->name, q->current_progress, q->target_harvest);
        }
    }
}

bool check_quest_completion(Quest* q) {
    return q->completed;
}

void give_quest_reward(Quest* q, int* player_money) {
    if (q->completed && q->reward_money > 0) {
        *player_money += q->reward_money;
        printf(" 💰 보상으로 %d원을 획득했습니다!\n", q->reward_money);
        q->reward_money = 0;  // 중복 방지
    }
}
