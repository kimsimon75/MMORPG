#pragma once
#ifndef _MAIN_
#define _MAIN_
#include "메인.h"
#endif


void Render()
{
	Data::keyInput = 0;
	Renderer::Map();
	TextManager::Get()->Update();
	Renderer::Button();
	Renderer::Play();
	if (Data::state >= 1 && Data::state < 3)
		Renderer::Status();


	if (Data::alertCount)
		Warning::Alert();
	if (Data::skillOn)
		Renderer::SkillInformation();

}

void Gameplay()
{
	while (UnitManager::Get()->returnPlayer().AP() < 100 && UnitManager::Get()->returnEnemy().AP() < 100) {
		UnitManager::Get()->returnPlayer().APCharge();
		UnitManager::Get()->returnEnemy().APCharge();
		Render();
		Sleep(30);
	}
	if (UnitManager::Get()->returnPlayer().AP() >= 100 && UnitManager::Get()->returnEnemy().AP() >= 100)
	{
		if (UnitManager::Get()->returnPlayer().AP() >= UnitManager::Get()->returnEnemy().AP())	
		{
			PlayerTurn();
			if (!playerTurn)
			{
				EnemyTurn();
				EndTurn();
			}
		}
		else
		{
			EnemyTurn();
			
			PlayerTurn();
			if (!playerTurn)
			{
				EndTurn();
			}
		}

	}
	else if (UnitManager::Get()->returnPlayer().AP() >= 100)
	{
		PlayerTurn();
		if (!playerTurn)
			EndTurn();
	}
	else if (UnitManager::Get()->returnEnemy().AP() >= 100)
	{
		EnemyTurn();
		EndTurn();
	}
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
			if(Data::state!=2)
			KeyValue();
			if(Data::state==2)
			{
				Gameplay();
			}

		}
		Renderer::Map();
		Warning::GameOver();
		ResetGame();
	}


	return 0;

}

