#ifndef _TEXT_
#define _TEXT_
#include "텍스트메니저.h"
#endif

bool SP = false;
bool Dead = false;

#define BEEPSOUND 560

void EnemyTurn()
{
	if (UnitManager::Get()->returnEnemy().returnHP() <= 0)
	{
		UnitManager::Get()->returnEnemy().returnHP() = 0;
		TextManager::Get()->Update();
		UnitManager::Get()->SetEnemy(++gameRound);
		UnitManager::Get()->returnPlayer().poison = false;
	}
	else
	{
		if (gameRound == 1 && UnitManager::Get()->returnEnemy().GetDamage(false))
			UnitManager::Get()->returnEnemy().DamageUp();
		if (UnitManager::Get()->returnEnemy().ReturnMaxMP() != 0 && UnitManager::Get()->returnEnemy().ReturnMP() >= UnitManager::Get()->returnEnemy().ReturnMaxMP())
		{
			UnitManager::Get()->returnEnemy().Special_Attack(UnitManager::Get()->returnPlayer(), gameRound);
			UnitManager::Get()->returnEnemy().ReturnMP() = 0;
			SP = true;
		}
		else
			UnitManager::Get()->returnEnemy().basic_Attack(UnitManager::Get()->returnPlayer());
	}

}

void EndTurn()
{
	if (UnitManager::Get()->returnPlayer().ShowBuff())
	{
		UnitManager::Get()->returnPlayer().SetDamage(1.5);
		--UnitManager::Get()->returnPlayer().ShowBuff();
	}
	else
	{
		UnitManager::Get()->returnPlayer().SetDamage(1.0);
	}
	if (SP == false)
	{
		UnitManager::Get()->returnEnemy().ManaCharge();
		if (UnitManager::Get()->returnEnemy().poison)
			UnitManager::Get()->returnEnemy().GetPoison();

		if (UnitManager::Get()->returnPlayer().poison)
			UnitManager::Get()->returnPlayer().GetPoison();

	}
	else
		SP = false;
	UnitManager::Get()->returnPlayer().ManaCharge();


	if (UnitManager::Get()->returnPlayer().returnHP() <= 0)
		gameover = true;

	UnitManager::Get()->returnEnemy().Restoring();
	UnitManager::Get()->returnPlayer().Restoring();
}

void ResetGame()
{
	TextManager::Get()->SetRenderer(STORY);
	if (&UnitManager::Get()->returnPlayer())
		UnitManager::Get()->returnPlayer().poison = false;
	delete[] skillSet;
	skillSet = nullptr;
	skillCount = 0;
	skillOn = false;
	button_x = 1;
	state = 0;
	gameRound = 0;

}

void KeyValue()
{
	static bool stopTheGame = false;

	while (state >= 2 && UnitManager::Get()->returnPlayer().StunTime())
	{
		keyInput = 1;
		EnemyTurn();
		EndTurn();
		UnitManager::Get()->returnPlayer().StunTime()--;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		keyInput = 1;
		if (state <= 2)
		{

			button_x--;
			if (button_x < ((alertCount == 1) ? 2 : 1))
			{
				button_x = (alertCount == 1) ? 3 : ((skillOn) ? skillCount : maxCount);
			}
			if (state == 1)
			{
				UnitManager::Get()->SetPlayer(button_x);
				gameRound = 0;
			}

			Beep(BEEPSOUND, 50);
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		keyInput = 1;
		if (state <= 2)
		{
			button_x++;
			if (button_x > ((alertCount == 1) ? 3 : ((skillOn) ? skillCount : maxCount)))
				button_x = (alertCount == 1) ? 2 : 1;
			if (state == 1)
			{
				UnitManager::Get()->SetPlayer(button_x);
				gameRound = 0;
			}
			Beep(BEEPSOUND, 50);
		}
	}
	if (button_x - 1 > currentCount + 3)
	{
		currentCount = button_x - 4;
	}
	if (button_x - 1 < currentCount)
	{
		currentCount = button_x - 1;
	}


	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
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
				TextManager::Get()->SetRenderer(HOWTOPLAY);
				break;
			case 4:
				PostMessage(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
				break;
			}
			break;
		case 1: // 케릭터 선택창
		{
			TextManager::Get()->SetRenderer(ENEMY);

			UnitManager::Get()->SetPlayer(button_x);
			UnitManager::Get()->SetEnemy(0);
			skillCount = 0;

			while (strlen(skills[button_x - 1][skillCount])) { ++skillCount; }
			skillSet = new Func[skillCount - 1];

			switch (button_x)
			{
			case 1:
				skillSet[0] = &Player::DamageUp;
				skillSet[1] = &Player::Rush;
				skillSet[2] = &Player::DoubleAttack;
				break;
			case 2:
				skillSet[0] = &Player::DamageUp;
				skillSet[1] = &Player::DamageUp;
				skillSet[2] = &Player::DamageUp;
				break;
			case 3:
				skillSet[0] = &Player::DamageUp;
				skillSet[1] = &Player::DamageUp;
				skillSet[2] = &Player::DamageUp;
				break;
			case 4:
				skillSet[0] = &Player::DamageUp;
				skillSet[1] = &Player::DamageUp;
				skillSet[2] = &Player::DamageUp;
				break;
			default:

				skillSet[0] = &Player::DamageUp;
				skillSet[1] = &Player::DamageUp;
				skillSet[2] = &Player::DamageUp;
				break;
			}
			state = 2;

		}
		break;
		case 2: // 게임 시작
			if (alertCount == 1)
			{
				switch (button_x)
				{
				case 3:
					ResetGame();
				case 2:
					alertCount = 0;
					stopTheGame = true;
					break;
				}
			}
			else
			{
				if (skillOn)
				{
					if (skillCount == button_x)
					{
						stopTheGame = true;
					}
					else
						(UnitManager::Get()->returnPlayer().*skillSet[button_x - 1])(UnitManager::Get()->returnEnemy());
					skillOn = false;
				}
				else
					switch (button_x)
					{
					case 1:
						UnitManager::Get()->returnPlayer().basic_Attack(UnitManager::Get()->returnEnemy());
						break;
					case 2:
						stopTheGame = true;
						skillOn = true;
						break;
					case 3:
						stopTheGame = true;
						break;
					case 4:
						stopTheGame = true;
					case 5:
						stopTheGame = true;
					default:
						break;
					}
			}
			if (stopTheGame)
				stopTheGame = false;

			else
			{
				EnemyTurn();
				EndTurn();
			}
			break;
		}
		currentCount = 0;
		button_x = 1;
		Beep(BEEPSOUND, 50);
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		keyInput = 1;
		currentCount = 0;
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
	maxCount = 0;
	for (int i = 0; (int)strlen(text[state][i]); i++)
	{
		maxCount++;
	}
}