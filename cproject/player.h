#pragma once
#define max_energy 100
#include <windows.h>
#include"inventory.h"

//키보드값 반환시 int menuDraw로 이동
#define Z 4
#define X 5
#define C 6
#define F 7
#define Q 8


typedef struct {
	char name[20];
	char sign;        //사용자 캐릭터
	int x, y;		//사용자 시작 좌표
	int region;     //사용자 지역 (0: 농장, 1: 광장)
	int energy;     //사용자 에너지
	int weather; //날씨 (0: 맑음, 1: 비)
	int money;
	int day;
	int season; // 1:봄 2:여름 3:가을 4:겨울

	// 인벤토리 관련
	int current_item; // '> '가 가리키는 인벤토리 아이템 인덱스
	int selected_index; //  shift를 눌렀을때 선택된 아이템 인덱스
	Inventory inventory; //인벤토리	
	//int inventory_slot; //보유 가능한 인벤토리 슬롯수
	char last_selected_message[100];

	// 퀘스트 관련
	int quest_progress; //퀘스트 진행 상태
	int selected_quest_index;     // 퀘스트 목록 커서 위치 (화면에 '>' 표시용)
	int active_quest_index;       // 실제 선택한 퀘스트 번호 (ENTER로 선택되었을 때 기록)

} Player;

extern Player player;

void init_player(Player* player);
