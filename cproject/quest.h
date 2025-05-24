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

extern Quest quest_list[MAX_TOTAL_QUESTS]; // 전체 퀘스트 목록
