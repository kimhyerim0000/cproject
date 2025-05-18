#pragma execution_character_set("utf-8")

#include "player.h"
#include "base.h"
#include <stdio.h>
#include <conio.h>

//포함 내용
// 사용자가 보유중인 인벤토리 
// 사용자가 가진 퀘스트
// 즉, 사용자가 행동하는거
Player player;

void init_player(Player* player) {
	player->sign = '@';
	player->x = 1;
	player->y = 1;
	player->region = 0;
	player->energy = max_energy;
	player->weather = 0; // 0: 맑음, 1: 비
	player->money = 100;
	player->day = 1;
	player->season = 1;

	//인벤토리 관련
	player->current_item = 0;
	player->selected_index = 0; // 인벤토리에서 선택된 아이템 인덱스
	player->inventory.count = 0;
	player->inventory.max_slots = MAX_INVENTORY;
	strcpy_s(player->last_selected_message, sizeof(player->last_selected_message), "");
	
	//퀘스트 관련
	player->quest_progress = 0;

	// 작물 0~2번 인벤토리에 추가
	for (int i = 0; i < 3; i++) {
		const char* name = crop_list[i].name;
		add_item(&player->inventory, name, 3 - i); // 감자 3, 당근 2, 토마토 1
	}

	// 씨앗 0~2번 인벤토리에 추가
	for (int i = 0; i < 3; i++) {
		const char* name = seed_list[i].name_seeds;
		add_item(&player->inventory, name, 3 - i); // 감자 씨앗 3, 당근 씨앗 2, 토마토 씨앗 1
	}

	////동적 item추가가 아닌 출력 시험용  inventoryItem item목록
	//player->inventory.count = 3; // 아이템 수
	//player->inventory.max_slots = MAX_INVENTORY;

	//strcpy_s(player->inventory.items[0].name, "감자");
	//player->inventory.items[0].quantity = 3;

	//strcpy_s(player->inventory.items[1].name, "토마토");
	//player->inventory.items[1].quantity = 2;

	//strcpy_s(player->inventory.items[2].name, "단호박");
	//player->inventory.items[2].quantity = 1;
}
//void move_player(Player* player) {
//	while (true) {
//		char inputASDW = _getch();
//		switch (inputASDW) {
//		case 'w':
//			if (true) {
//				player->y++;
//				printf("player x: %d, y: %d\n", player->x, player->y);
//			}
//			break;
//		case 'a':
//			if (player->x > 0) {
//				player->x--;
//				printf("player x: %d, y: %d\n", player->x, player->y);
//
//			}
//			break;
//		case 's':
//			if (player->y > 0) {
//				player->y--;
//				printf("player x: %d, y: %d\n", player->x, player->y);
//
//			}
//			break;
//		case 'd':
//			if (true) { // 콘솔 x축 최대범위로 수정
//				player->x++;
//				printf("player x: %d, y: %d\n", player->x, player->y);
//			}
//			break;
//		}
//	}
//}
	/*void sleep_player(Player * player) {
		while (_kbhit()) {
			if (_getch() == 't') {
				player->x = 1;
				player->y = 1;
				player->energy = max_energy;
				player->day++;
				if (player->day == 15) {
					player->day = 1;
					player->season++;
				}
			}

		}*/
	//}
