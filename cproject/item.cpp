// 수확 가능 작물, 플랜트 가능 씨앗, 아이템
#pragma execution_character_set("utf-8")

#include "item.h"

// 수확 가능 종류
Crop crop_list[10] = {
    {"감자",      SPRING, 5,  100},
    {"당근",      SPRING, 4,  120},
    {"토마토",    SUMMER, 6,  150},
    {"옥수수",    SUMMER, 7,  180},
    {"블루베리",  SUMMER, 6,  200},
    {"단호박",    FALL,   8,  250},
    {"무",        FALL,   5,  130},
    {"고구마",    FALL,   6,  160},
    {"시금치",    WINTER, 4,  110},
    {"브로콜리",  WINTER, 6,  170}
};

int crop_count = 10;

//씨앗 종류
Seed seed_list[10] = {
	{"감자 씨앗",  SPRING, 5,  100},
	{"당근 씨앗",  SPRING, 4,  120},
	{"토마토 씨앗",SUMMER, 6,  150},
	{"옥수수 씨앗",SUMMER, 7,  180},
	{"블루베리 씨앗",SUMMER,6,200},
	{"단호박 씨앗",FALL,   8,250},
	{"무 씨앗",    FALL,   5,130},
	{"고구마 씨앗",FALL,   6,160},
	{"시금치 씨앗",WINTER, 4,110},
	{"브로콜리 씨앗",WINTER,6,170}
};

int seed_count = 10;
