#pragma once
#include <stdbool.h>

#define MAX_NAME_LEN 50
#define MAX_ACTIVE_QUESTS 3
#define MAX_TOTAL_QUESTS 10

typedef struct {
    char name[MAX_NAME_LEN];       // 퀘스트 이름
    int target_harvest;            // 목표 수확량
    int current_progress;          // 현재 진행 상황
    int reward_money;              // 보상 금액
    bool completed;                // 완료 여부
    char target_crop[MAX_NAME_LEN]; // 목표 작물 이름
} Quest;

// 퀘스트 함수 선언
void init_quest(Quest* q, const char* name, const char* crop_name, int target, int reward);
bool register_quest(Quest* q);
void update_quest_progress(Quest* q, const char* harvested_crop_name, int harvested_amount);
bool check_quest_completion(Quest* q);
void give_quest_reward(Quest* q, int* player_money);
void update_all_quest_progress(const char* crop_name, int harvested);
void setup_quests();

// 외부 전역 변수 선언
extern Quest quest_list[MAX_TOTAL_QUESTS];
extern int total_quests;
extern Quest* active_quests[MAX_ACTIVE_QUESTS];
extern int active_quest_count;
