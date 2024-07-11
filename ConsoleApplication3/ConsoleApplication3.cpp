#pragma once
#ifndef _MAIN_
#define _MAIN_
#include "main.h"
#endif

bool nextTurn = false;

void Render()
{
	Data::keyInput = 0;
	Map();
	if (!Data::itemOn && !Data::weaponOn)
	{
		Button();
		TextManager::Get()->Update();
		Play();
		if (Data::state >= 1 && Data::state < 3)
			Status();
	}
	else
	{
		TextManager::Get()->Update();
		Status();
		ItemInformation();
	}


		if (Data::alertCount)
			Warning::Alert();
		else if (Data::skillOn)
			SkillInformation();


}

void Gameplay()
{
	playingRestore();
	Data::button_x = 0;
	while (UnitManager::Get()->returnPlayer().AP() < 100 || UnitManager::Get()->returnEnemy().AP() < 100) {
		UnitManager::Get()->returnPlayer().APCharge();
		UnitManager::Get()->returnEnemy().APCharge();
		Render();
		Sleep(30);
	}
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);
	while (UnitManager::Get()->returnPlayer().AP() >= 100 || UnitManager::Get()->returnEnemy().AP() >= 100)
	{
		if (gameover)
			break;
		if (UnitManager::Get()->returnPlayer().AP() >= UnitManager::Get()->returnEnemy().AP())
		{
			
				if (UnitManager::Get()->returnPlayer().StunTime())
				{
					--UnitManager::Get()->returnPlayer().StunTime();
					UnitManager::Get()->returnPlayer().AP() -= 100;
					UnitManager::Get()->returnEnemy().WTF() = true;
					Sleep(1000);
					Data::keyInput = 1;
				}
				else 
				{
					if (UnitManager::Get()->returnPlayer().TurnReturn() == false)
					{
						UnitManager::Get()->returnPlayer().TurnReturn() = true;
						Data::button_x = 1;
						Data::keyInput = 1;
					}
					PlayerTurn();
				}
				if (Data::keyInput)
					Render();

				if (UnitManager::Get()->returnEnemy().ReturnHP() <= 0)
					NextRound();

		}
		else
		{
			UnitManager::Get()->returnEnemy().TurnReturn() = true;
			Data::button_x = 0;
			Render();
			Sleep(500);
			EnemyTurn();
			Render();
			if (UnitManager::Get()->returnPlayer().AP() >= 100)
				Render();
		}
	}
	if(!gameover)
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

	Data::weaponSkill[0] = &Player::ShieldBash;
	Data::weaponSkill[1] = &Player::Bite;
	
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

