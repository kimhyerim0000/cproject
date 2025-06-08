#pragma execution_character_set("utf-8")

#include "quest.h"
#include <string.h>
#include <stdio.h>

#define MAX_ACTIVE_QUESTS 3
// 전체 퀘스트 목록 정의
Quest quest_list[MAX_TOTAL_QUESTS] = {
    {"감자 수확왕",        5, 0, 500, false, "감자"},
    {"당근 장인",          7, 0, 600, false, "당근"},
    {"토마토 대작전",      6, 0, 750, false, "토마토"},
    {"옥수수 마스터",      8, 0, 900, false, "옥수수"},
    {"블루베리 꿈나무",    10, 0, 1000, false, "블루베리"},
    {"단호박 연구가",      4, 0, 1250, false, "단호박"},
    {"무 수확 챌린지",     6, 0, 650, false, "무"},
    {"고구마 달인",        7, 0, 850, false, "고구마"},
    {"시금치 캐기",        5, 0, 550, false, "시금치"},
    {"브로콜리 파티",      6, 0, 850, false, "브로콜리"},
};



