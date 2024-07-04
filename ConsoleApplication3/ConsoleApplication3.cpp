#pragma once
#ifndef _MAIN_
#define _MAIN_
#include "메인.h"
#endif


void Render()
{
	Data::keyInput = 0;
	Map();
	TextManager::Get()->Update();
	Button();
	Play();
	if (Data::state >= 1 && Data::state < 3)
		Status();


	if (Data::alertCount)
		Warning::Alert();
	else if (Data::skillOn)
		SkillInformation();

}

void Gameplay()
{
	while (UnitManager::Get()->returnPlayer().AP() < 100 || UnitManager::Get()->returnEnemy().AP() < 100) {
		UnitManager::Get()->returnPlayer().APCharge();
		UnitManager::Get()->returnEnemy().APCharge();
		Render();
		Sleep(30);
	}
	while (UnitManager::Get()->returnPlayer().AP() >= 100 || UnitManager::Get()->returnEnemy().AP() >= 100)
	{
		if (UnitManager::Get()->returnPlayer().AP() >= UnitManager::Get()->returnEnemy().AP())
		{

			if (UnitManager::Get()->returnPlayer().StunTime())
			{
				--UnitManager::Get()->returnPlayer().StunTime();
				UnitManager::Get()->returnPlayer().AP() -= 100;
				UnitManager::Get()->returnEnemy().WTF()=true;
				Data::keyInput = 1;
			}
			else PlayerTurn();
			if (Data::keyInput)
				Render();

			if (UnitManager::Get()->returnEnemy().ReturnHP() <= 0)
				NextRound();

		}
		else
		{
			Sleep(1000);
			EnemyTurn();
			Render();
			if (UnitManager::Get()->returnPlayer().AP() >= 100)
				Render();

			if (UnitManager::Get()->returnPlayer().ReturnHP() <= 0)
			{
				Map();
				Warning::GameOver();
				ResetGame();
			}
		}
		rewind(stdin);
	}
	EndTurn();

}

int main(){

	system("mode con: cols=104 lines=41");

	

	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	//playingBgm();
	TextManager::Get()->SetRenderer(STORY);
	
	while(1)
	{
		while (!gameover)
		{
			if (Data::keyInput)
			{
 				Render();
			}
			if(Data::state!=2) KeyValue();
			else Gameplay();


		}
		Map();
		Warning::GameOver();
		ResetGame();
	}


	return 0;

}

