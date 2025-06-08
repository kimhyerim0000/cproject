#pragma execution_character_set("utf-8")

#include "player.h"
#include "base.h"
#include "intro.h"

#include <stdio.h>
#include <iostream>
void run_game();

int main() 
{
	show_intro();
	Player player;
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	SetConsole();
	
	titleDraw();
	menuDraw();

	run_game();
	
	
	return 0;
}