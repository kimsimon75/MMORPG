#pragma once
#ifndef _TEXT_
#define _TEXT_
#include "텍스트메니저.h"
#endif


bool SP = false;
bool Dead = false;
bool stopTheGame = false;
bool playerTurn = false;
bool leftKey = true;
bool rightKey = true;
bool spaceKey = true;
bool escKey = true;

#define BEEPSOUND 560

void Render();

void NextRound()
{
	Data::keyInput = 1;
	UnitManager::Get()->returnEnemy().ReturnHP() = 0;
	TextManager::Get()->Update();
  	UnitManager::Get()->SetEnemy(++Data::gameRound);

 	UnitManager::Get()->NextRound(UnitManager::Get()->returnPlayer()); 
	UnitManager::Get()->returnPlayer().GameRound() = Data::gameRound;
}


void ResetGame()
{
	TextManager::Get()->SetRenderer(STORY);
	if(&UnitManager::Get()->returnPlayer()!=nullptr)
	UnitManager::Get()->returnPlayer().AP() = 0;
	UnitManager::Get()->SetEnemy(0);
	delete[] Data::skillSet;
	Data::skillSet = nullptr;
	Data::skillCount = 0;
	Data::skillOn = false;
	Data::button_x = 1;
	Data::state = 0;
	Data::gameRound = 0;

}

void EnemyTurn()
{
	Data::keyInput = 1;

		if (UnitManager::Get()->returnEnemy().ReturnHP() <= 0)
		{
			NextRound();
		}
		else
		{

			if (!UnitManager::Get()->returnEnemy().StunTime() && !UnitManager::Get()->returnEnemy().iced_time())
			{
				TextManager::Get()->Update();
				if (UnitManager::Get()->returnEnemy().ReturnMaxMP() != 0 && UnitManager::Get()->returnEnemy().ReturnMP() >= UnitManager::Get()->returnEnemy().ReturnMaxMP())
				{
					UnitManager::Get()->returnEnemy().Special_Attack(UnitManager::Get()->returnPlayer(), Data::gameRound);
					UnitManager::Get()->returnEnemy().ReturnMP() = 0;
					SP = true;
				}
				else
					UnitManager::Get()->returnEnemy().basic_Attack(UnitManager::Get()->returnPlayer());
				if (!UnitManager::Get()->returnPlayer().GetDamage(false))
					UnitManager::Get()->returnPlayer().WTF() = true;
			}
	}
	if (UnitManager::Get()->returnEnemy().StunTime())
		UnitManager::Get()->returnEnemy().StunTime()--;
	if (UnitManager::Get()->returnEnemy().iced_time())
		UnitManager::Get()->returnEnemy().iced_time()--;
	UnitManager::Get()->returnEnemy().AP() -= 100;
}

void EndTurn()
{
	Data::keyInput = 1;
		

  	if (UnitManager::Get()->returnEnemy().PoisonTime()) UnitManager::Get()->returnEnemy().GetPoison();

	if (UnitManager::Get()->returnEnemy().IgniteTime()) UnitManager::Get()->returnEnemy().GetIgnite();

	if (UnitManager::Get()->returnPlayer().PoisonTime()) UnitManager::Get()->returnPlayer().GetPoison();

	if (UnitManager::Get()->returnPlayer().IgniteTime()) UnitManager::Get()->returnPlayer().GetIgnite();


	if (Data::gameRound == 1 && UnitManager::Get()->returnEnemy().GetDamage(false))
		UnitManager::Get()->returnEnemy().DamageUp(); 

 	if (UnitManager::Get()->returnEnemy().ReturnHP() <= 0)
		NextRound();
	
	if (SP == false) UnitManager::Get()->returnEnemy().ManaCharge();

	else SP = false;


	Render();


	UnitManager::Get()->returnPlayer().ManaCharge();

	if (UnitManager::Get()->returnEnemy().ReturnHP() <= 0)
		NextRound();


	if (UnitManager::Get()->returnPlayer().BarrierCool()) UnitManager::Get()->returnPlayer().BarrierCool()--;

	if (!UnitManager::Get()->returnPlayer().BarrierCool())UnitManager::Get()->returnPlayer().BarrierSize() = 0;

	if (!UnitManager::Get()->returnPlayer().BarrierSize())UnitManager::Get()->returnPlayer().BarrierCool() = 0;

	if (UnitManager::Get()->returnPlayer().ReturnHP() <= 0)
		gameover = true;

	if (UnitManager::Get()->returnPlayer().ShowBuff())
	{
		--UnitManager::Get()->returnPlayer().ShowBuff();
	}

	if (UnitManager::Get()->returnPlayer().IntelCool())
	{
		--UnitManager::Get()->returnPlayer().IntelCool();
	}

	UnitManager::Get()->returnEnemy().Restoring();
	UnitManager::Get()->returnPlayer().Restoring();
}

void PlayerTurn()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 )
	{
		if(leftKey)
		{
			Data::keyInput = 1;
			if (Data::state <= 2)
			{
				Beep(BEEPSOUND, 50);
				Data::button_x--;
				if (Data::button_x < ((Data::alertCount == 1) ? 2 : 1))
				{
					Data::button_x = (Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount);
				}
				if (Data::Data::state == 1)
				{
					UnitManager::Get()->SetPlayer(Data::button_x);
					Data::gameRound = 0;
				}

			}
			leftKey = false;
		}
	}
	else leftKey = true;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (rightKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			if (Data::state <= 2)
			{
				Data::button_x++;
				if (Data::button_x > ((Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount)))
					Data::button_x = (Data::alertCount == 1) ? 2 : 1;
				if (Data::state == 1)
				{
					UnitManager::Get()->SetPlayer(Data::button_x);
					Data::gameRound = 0;
				}
			}
			rightKey = false;
		}
	}
	else rightKey = true;
	if (Data::button_x - 1 > Data::currentCount + 3)
	{
		Data::currentCount = Data::button_x - 4;
	}
	if (Data::button_x - 1 < Data::currentCount)
	{
		Data::currentCount = Data::button_x - 1;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if(spaceKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			if (Data::alertCount == 1)
			{
				switch (Data::button_x)
				{
				case 3:
					ResetGame();
				case 2:
					Data::alertCount = 0;
					stopTheGame = true;
					break;
				}
			}
			else
			{
				if (Data::skillOn)
				{
					if (Data::skillCount == Data::button_x)
					{
						stopTheGame = true;
					}
					else
					{
						pair<bool, int> p = (UnitManager::Get()->returnPlayer().*Data::skillSet[Data::button_x - 1])(UnitManager::Get()->returnEnemy());
						if (p.first == 0)
						{
							if (p.second < 0)
							{
								Data::alertCount = 6;
								UnitManager::Get()->returnPlayer().SetAlertCount() = 0;
								Data::keyInput = 1;
							}
							else if (UnitManager::Get()->returnPlayer().ReturnHP() - p.second >= 0)
							{
								Data::alertCount = -1;
								UnitManager::Get()->returnPlayer().SetAlertCount() = Data::alertCount;
								(UnitManager::Get()->returnPlayer().*Data::skillSet[Data::button_x - 1])(UnitManager::Get()->returnEnemy());

								if (UnitManager::Get()->returnPlayer().SetAlertCount() >= 1)
								{
									Data::alertCount = UnitManager::Get()->returnPlayer().SetAlertCount();
									UnitManager::Get()->returnPlayer().SetAlertCount() = 0;
									Data::keyInput = 1;
								}
								else
								{
									Data::alertCount = 0;
									UnitManager::Get()->returnPlayer().SetAlertCount() = Data::alertCount;
								}
							}
							else
							{
								Data::alertCount = 2;
								Data::keyInput = 1;
							}
						}
						else
						{
							if (UnitManager::Get()->returnPlayer().ReturnMP() - p.second >= 0)
							{
								Data::alertCount = -1;
								UnitManager::Get()->returnPlayer().SetAlertCount() = Data::alertCount;
								(UnitManager::Get()->returnPlayer().*Data::skillSet[Data::button_x - 1])(UnitManager::Get()->returnEnemy());

								if (UnitManager::Get()->returnPlayer().SetAlertCount() >= 1)
								{
									Data::alertCount = UnitManager::Get()->returnPlayer().SetAlertCount();
									UnitManager::Get()->returnPlayer().SetAlertCount() = 0;
									Data::keyInput = 1;
								}
								else
								{
									Data::alertCount = 0;
									UnitManager::Get()->returnPlayer().SetAlertCount() = Data::alertCount;
								}
							}
							else
							{
								Data::alertCount = 3;
								Data::keyInput = 1;
							}
						}
					}
					Data::skillOn = false;
				}
				else
					switch (Data::button_x)
					{
					case 1:
						UnitManager::Get()->returnPlayer().basic_Attack(UnitManager::Get()->returnEnemy());
						break;
					case 2:
						stopTheGame = true;
						Data::skillOn = true;
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
			if (Data::alertCount)
				stopTheGame = true;
			if (stopTheGame)
				stopTheGame = false;
			else
			{
				playerTurn = false;
				UnitManager::Get()->returnPlayer().AP() -= 100;
				if (!UnitManager::Get()->returnEnemy().GetDamage(false) && !UnitManager::Get()->returnEnemy().iced_time()) UnitManager::Get()->returnEnemy().WTF() = true;

				if (UnitManager::Get()->returnEnemy().GetDamage(false))
				{
					if (UnitManager::Get()->returnEnemy().ReturnHP() < 0)
						UnitManager::Get()->returnEnemy().ReturnHP() = 0;
					if (Data::gameRound == 1)
						UnitManager::Get()->returnEnemy().DamageUp();
					TextManager::Get()->Update();
				}
			}
			Data::currentCount = 0;
			Data::button_x = 1;
			spaceKey = false; 
	   	} 
	}
	else spaceKey = true;

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (escKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			Data::currentCount = 0;
			if (Data::alertCount == 1)
			{
				Data::button_x = 1;
				Data::alertCount = 0;
			}
			else if (Data::skillOn)
			{
				Data::button_x = 1;
				Data::skillOn = false;
			}
			else
			{
				Data::alertCount = 1;
				Data::button_x = 2;
			}
			escKey = false;
		}
	}
	else escKey = true;
	Data::maxCount = 0;
	for (int i = 0; (int)strlen(text[Data::state][i]); i++)
	{
		Data::maxCount++;
	}  

	if (UnitManager::Get()->returnPlayer().ShowBuff())
	{
		UnitManager::Get()->returnPlayer().SetDamage(1.5);
	}
	else if (UnitManager::Get()->returnPlayer().PN() != 3)
	{
		UnitManager::Get()->returnPlayer().SetDamage(1.0);
	}

	if (UnitManager::Get()->returnPlayer().PN() != 4)
	{
		if (UnitManager::Get()->returnPlayer().IntelCool())
		{
			UnitManager::Get()->returnPlayer().SetIntel(50);
		}
		else
			UnitManager::Get()->returnPlayer().SetIntel(0);
	}

}


void KeyValue()
{
	static bool stopTheGame = false;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (leftKey)
		{
			Data::keyInput = 1;
			Beep(BEEPSOUND, 50);
			Data::button_x--;
			if (Data::button_x < ((Data::alertCount == 1) ? 2 : 1))
			{
				Data::button_x = (Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount);
			}
			if (Data::state == 1)
			{
				UnitManager::Get()->SetPlayer(Data::button_x);
				Data::gameRound = 0;
			}
			leftKey = false;
		}
	}
	else leftKey = true;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (rightKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			if (Data::state <= 2)
			{
				Data::button_x++;
				if (Data::button_x > ((Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount)))
					Data::button_x = (Data::alertCount == 1) ? 2 : 1;
				if (Data::state == 1)
				{
					UnitManager::Get()->SetPlayer(Data::button_x);
					Data::gameRound = 0;
				}
			}
			rightKey = false;
		}
	}
	else rightKey = true;
	if (Data::button_x - 1 > Data::currentCount + 3)
	{
		Data::currentCount = Data::button_x - 4;
	}
	if (Data::button_x - 1 < Data::currentCount)
	{
		Data::currentCount = Data::button_x - 1;
	}


	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (spaceKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			switch (Data::state)
			{
			case 0: // 메뉴창
				switch (Data::button_x)
				{
				case 1:
					Data::state = 1;
					TextManager::Get()->SetRenderer(PLAYERINFO);
					UnitManager::Get()->SetPlayer(Data::button_x);
					break;
				case 2:
				case 3:
					Data::state = 3;
					TextManager::Get()->SetRenderer(HOWTOPLAY);
					break;
				case 4:
					PostMessage(GetConsoleWindow(), WM_CLOSE, NULL, NULL);
					break;
				}
				break;
			case 1: // 케릭터 선택창
			{
				TextManager::Get()->SetRenderer(INGAME);

				UnitManager::Get()->SetPlayer(Data::button_x);
				UnitManager::Get()->SetEnemy(0);
				Data::skillCount = 0;

				while (strlen(skills[Data::button_x - 1][Data::skillCount])) { ++Data::skillCount; }
				Data::skillSet = new Func[Data::skillCount - 1];

				switch (Data::button_x)
				{
				case 1:
					Data::skillSet[0] = &Player::DamageUp;
					Data::skillSet[1] = &Player::Rush;
					Data::skillSet[2] = &Player::DoubleAttack;
					break;
				case 2:
					Data::skillSet[0] = &Player::fireball;
					Data::skillSet[1] = &Player::ignite;
					Data::skillSet[2] = &Player::IceMagic;
					Data::skillSet[3] = &Player::PutOnBarrier;
					Data::skillSet[4] = &Player::RaiseIntel;
					break;
				case 3:
					Data::skillSet[0] = &Player::DamageAbsorb;
					Data::skillSet[1] = &Player::PoisonAttack;
					Data::skillSet[2] = &Player::Dart;
					Data::skillSet[3] = &Player::Enemy_s_;
					break;
				case 4:
					Data::skillSet[0] = &Player::IntelligenceAbsorb;
					Data::skillSet[1] = &Player::PowerOfGod;
					Data::skillSet[2] = &Player::Heal;
					break;
				}
				Data::state = 2;

			}
			break;
			}
			Data::currentCount = 0;
			Data::button_x = 1;
			spaceKey = false;
		}
	}
	else spaceKey = true;

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (escKey)
		{
			Beep(BEEPSOUND, 50);
			Data::keyInput = 1;
			Data::currentCount = 0;

			ResetGame();
			escKey = false;
		}
	}
	else escKey = true;
	Data::maxCount = 0;
	for (int i = 0; (int)strlen(text[Data::state][i]); i++)
	{
		Data::maxCount++;
	}
}