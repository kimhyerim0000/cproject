#pragma once
#define max_energy 100
#include <windows.h>
#include"inventory.h"

//Ű���尪 ��ȯ�� int menuDraw�� �̵�
#define Z 4
#define X 5
#define C 6
#define F 7
#define Q 8


typedef struct {
	char name[20];
	char sign;        //����� ĳ����
	int x, y;		//����� ���� ��ǥ
	int region;     //����� ���� (0: ����, 1: ����)
	int energy;     //����� ������
	int weather; //���� (0: ����, 1: ��)
	int money;
	int day;
	int season; // 1:�� 2:���� 3:���� 4:�ܿ�

	// �κ��丮 ����
	int current_item; // '> '�� ����Ű�� �κ��丮 ������ �ε���
	int selected_index; //  shift�� �������� ���õ� ������ �ε���
	Inventory inventory; //�κ��丮	
	//int inventory_slot; //���� ������ �κ��丮 ���Լ�
	char last_selected_message[100];

	// ����Ʈ ����
	int quest_progress; //����Ʈ ���� ����
	int selected_quest_index;     // ����Ʈ ��� Ŀ�� ��ġ (ȭ�鿡 '>' ǥ�ÿ�)
	int active_quest_index;       // ���� ������ ����Ʈ ��ȣ (ENTER�� ���õǾ��� �� ���)

} Player;

extern Player player;

void init_player(Player* player);
