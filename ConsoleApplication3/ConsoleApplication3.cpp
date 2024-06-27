
#include "텍스트메니저.h"
#include "유닛메니저.h"
#include <conio.h>

#define BEEPSOUND 560

void EnemyTurn()
{

	if (UnitManager::Get()->returnEnemy() != nullptr && UnitManager::Get()->returnEnemy()->returnHP() <= 0)
	{

		UnitManager::Get()->SetEnemy(++gameRound);
	}
	else
	UnitManager::Get()->returnEnemy()->basic_Attack(UnitManager::Get()->returnPlayer());

}

void ResetGame()
{
	TextManager::Get()->SetRenderer(STORY);
	button_x = 1;

	state = 0;
}

void KeyValue()
{


	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		keyInput = 1;
		if (state <= 2)
		{

			button_x--;
			if (button_x < ((alertCount == 1) ? 2 : 1))
			{
				button_x = (alertCount == 1) ? 3 : maxCount;
			}

			Beep(BEEPSOUND, 50);
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		keyInput = 1;
		if(state<=2)
		{
			button_x++;
			if (button_x > ((alertCount == 1) ? 3 : maxCount))
				button_x = (alertCount == 1) ? 2 : 1;
			Beep(BEEPSOUND, 50);
		}
	}
	if (button_x - 1 > currentCount + 3)
	{
		currentCount = button_x - 4;
		Alert();
	}
	if (button_x - 1 < currentCount)
	{
		currentCount = button_x - 1;
	}
	if (state == 1)
	{
		UnitManager::Get()->returnPlayer()->SetPN(button_x);
		gameRound = 0;
  	} 
	
	if (_getch()==(VK_SPACE))
	{
		keyInput = 1;
		switch (state)
		{
		case 0: // 메뉴창
			switch (button_x)
			{
			case 1:
				state = 1;
				TextManager::Get()->SetRenderer(PLAYERINFO);
				UnitManager::Get()->SetPlayer(button_x);
				break;
			case 2:
			case 3:
				state = 3;
				button_x = 1;
				TextManager::Get()->SetRenderer(HOWTOPLAY);
				break;
			case 4:
				PostMessage(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
				button_x = 1;
				break;
			}
			break;
		case 1: // 케릭터 선택창
		{
			TextManager::Get()->SetRenderer(ENEMY);

			UnitManager::Get()->SetPlayer(button_x);
			UnitManager::Get()->SetEnemy(0);
			button_x = 1;
			state = 2;
			
		}
			break;
		case 2: // 게임 시작
			if (alertCount == 1)
			{
				switch (button_x)
				{
				case 2:
					button_x = 1;
					alertCount = 0;
					break;
				case 3:
					alertCount = 0;
					ResetGame();
					break;
				}
			}
			else
			switch (button_x)
			{
			case 1:
				UnitManager::Get()->returnPlayer()->basic_Attack(UnitManager::Get()->returnEnemy());

				break;
			default:
				break;
			}
			EnemyTurn();
			UnitManager::Get()->returnEnemy()->Restoring();
			UnitManager::Get()->returnPlayer()->Restoring();
			break;

		}

		Beep(BEEPSOUND, 50);
 	}
	if (state == 2) maxCount = 5;
	else maxCount = 4;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		keyInput = 1;
		currentCount = 0;
		maxCount = 4;
		if (state == 2)
		{
			alertCount = 1;
			button_x = 2;
		}
		else if (state >= 1)
		{
			ResetGame();
		}
			
		Beep(BEEPSOUND, 50);
	}
}


int main(){

	system("mode con: cols=104 lines=41");

	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	
	TextManager::Get()->SetRenderer(STORY);
	
	while (1)
	{
		if(keyInput)
		{
			Map();
			Button();
			Play();

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			TextManager::Get()->Update();
			keyInput = 0;
		}

		if (alertCount)
			Alert();
		KeyValue();
	}
	return 0;

}

