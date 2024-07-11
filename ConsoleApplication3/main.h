#pragma once
#ifndef _TEXT_
#define _TEXT_
#include "textmanager.h"
#endif


bool SP = false;
bool Dead = false;
bool stopTheGame = false;
bool leftKey = true;
bool rightKey = true;
bool downKey = true;
bool upKey = true;
bool spaceKey = true;
bool escKey = true;

#define BEEPSOUND 560

void Render();

void GetItem()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	Warning warning;
	int random = dis(gen);
	int pre = Data::itemSlot_x;
	switch (Data::gameRound)
	{
	case 0:
		Data::itemSlot[Data::itemSlot_x++] = 1;
		break;
	case 1:
			Data::itemSlot[Data::itemSlot_x++] = 2;
		break;
	}
	if(pre!=Data::itemSlot_x)
	{
		Data::alertCount = 7;
		warning.Alert();
	}
}
void GetWeapon()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	Warning warning;
	int random = dis(gen);
	int pre = Data::weaponSlot_x;
	switch (Data::gameRound)
	{
	case 0:
		Data::weaponSlot[Data::weaponSlot_x++] = 1;
		break;
	case 1:
			Data::weaponSlot[Data::weaponSlot_x++] = 2;
		break;
	}
	if (pre != Data::weaponSlot_x)
	{
		Data::alertCount = 8;
		warning.Alert();
	}
}

void SwapItem()
{
	char swap = Data::itemSlot[Data::item_x-1];
	Data::itemSlot[Data::item_x-1] = Data::puttingItemSlot[Data::puttingItem_x-1];
	Data::puttingItemSlot[Data::puttingItem_x-1] = swap;
}
void SwapWeapon()
{
	
	char swap = Data::weaponSlot[Data::weapon_x - 1];
	Data::weaponSlot[Data::weapon_x - 1] = Data::puttingWeaponSlot[Data::puttingWeapon_x - 1];
	Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] = swap;
	if (Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] - 1 != -1)
		Data::skillSet[Data::skillCount - 3 + Data::puttingWeapon_x - 1] = Data::weaponSkill[Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] - 1];
	else
		Data::skillSet[Data::skillCount - 3 + Data::puttingWeapon_x - 1] = nullptr;
}

void NextRound()
{
	Data::keyInput = 1;
	UnitManager::Get()->returnEnemy().ReturnHP() = 0;
	TextManager::Get()->Update();
	GetItem();
	GetWeapon();
  	UnitManager::Get()->SetEnemy(++Data::gameRound);

 	UnitManager::Get()->NextRound(UnitManager::Get()->returnPlayer()); 
	UnitManager::Get()->returnPlayer().GameRound() = Data::gameRound;
	UnitManager::Get()->returnPlayer().SetAbility(Data::puttingItemSlot, Data::puttingWeaponSlot);
}

void ResetGame()
{
	TextManager::Get()->SetRenderer(STORY);
	if(Data::state==2)
	{
		UnitManager::Get()->returnPlayer().AP() = 0;
		UnitManager::Get()->SetEnemy(0);
		delete[] Data::skillSet;
		Data::skillSet = nullptr;
		Data::skillCount = 0;
		fill_n(Data::itemSlot, sizeof(Data::itemSlot) / sizeof(Data::itemSlot[0]), 0);
		fill_n(Data::puttingItemSlot, sizeof(Data::puttingItemSlot) / sizeof(Data::puttingItemSlot[0]), 0);
		fill_n(Data::weaponSlot, sizeof(Data::weaponSlot) / sizeof(Data::weaponSlot[0]), 0);
		fill_n(Data::puttingWeaponSlot, sizeof(Data::puttingWeaponSlot) / sizeof(Data::puttingWeaponSlot[0]), 0);
		Data::weaponSlot_x = 0;
		Data::weapon_x = 0;
		Data::itemSlot_x = 0;
		Data::maxCount = 4;
	}
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

				if (UnitManager::Get()->returnPlayer().ReturnHP() <= 0)
					gameover = true;
				if (!UnitManager::Get()->returnPlayer().GetDamage(false))
					UnitManager::Get()->returnPlayer().WTF() = true;
			}
	}
	if (UnitManager::Get()->returnEnemy().StunTime())
		UnitManager::Get()->returnEnemy().StunTime()--;
	if (UnitManager::Get()->returnEnemy().iced_time())
		UnitManager::Get()->returnEnemy().iced_time()--;
	UnitManager::Get()->returnEnemy().AP() -= 100;
	UnitManager::Get()->returnEnemy().TurnReturn() = false;
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
	if (!gameover)
	{

		if (UnitManager::Get()->returnPlayer().IntelCool())
		{
			--UnitManager::Get()->returnPlayer().IntelCool();
		}

		UnitManager::Get()->returnEnemy().Restoring();
		UnitManager::Get()->returnPlayer().Restoring();
	}
}

void PlayerTurn()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (leftKey)
		{
			Data::keyInput = 1;
			if (Data::state <= 2)
			{
				Beep(BEEPSOUND, 50);
				if (Data::weaponOn)
					(Data::setWeapon ? Data::weapon_x : Data::puttingWeapon_x)--;
				else	
					(Data::itemOn ? (Data::setItem ? Data::item_x : Data::puttingItem_x) : Data::button_x)--;
				if (Data::button_x < ((Data::alertCount == 1) ? 2 : 1))
					Data::button_x = (Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount);

				if (Data::puttingItem_x < 1) Data::puttingItem_x = 6;
				if (Data::puttingWeapon_x < 1) Data::puttingWeapon_x = 1;
				if (Data::item_x == 10 || Data::item_x == 20 || Data::item_x == 0) Data::item_x++;
				if (Data::weapon_x == 10 || Data::weapon_x == 20 || Data::weapon_x == 0) Data::weapon_x++;

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
				if (Data::weaponOn)
					(Data::setWeapon ? Data::weapon_x : Data::puttingWeapon_x)++;
				else
					(Data::itemOn ? (Data::setItem ? Data::item_x : Data::puttingItem_x) : Data::button_x)++;
				if (Data::button_x > ((Data::alertCount == 1) ? 3 : ((Data::skillOn) ? Data::skillCount : Data::maxCount)))
					Data::button_x = (Data::alertCount == 1) ? 2 : 1;
				if (Data::puttingItem_x > 6)Data::puttingItem_x = 1;
				if (Data::puttingWeapon_x > 2) Data::puttingWeapon_x = 2;

				if (Data::item_x == 11 || Data::item_x == 21 || Data::item_x == 31 || Data::item_x > Data::itemSlot_x)	Data::item_x--;
				if (Data::weapon_x == 11 || Data::weapon_x == 21 || Data::weapon_x == 31 || Data::weapon_x > Data::weaponSlot_x)Data::weapon_x--;

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

	if (Data::setItem || Data::setWeapon)
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (downKey)
			{
				Beep(BEEPSOUND, 50);
				Data::keyInput = 1;

				if (Data::itemOn)
				{
					Data::item_x += 10;
					if (Data::item_x > Data::itemSlot_x)
						Data::item_x -= 10;
				}
				else
				{
					Data::weapon_x += 10;
					if (Data::weapon_x > Data::weaponSlot_x)
						Data::weapon_x -= 10;
				}
				downKey = false;
			}

		}
		else downKey = true;

	if (Data::setItem || Data::setWeapon)
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (upKey)
			{
				Beep(BEEPSOUND, 50);
				Data::keyInput = 1;

				if(Data::setItem)
				{
					Data::item_x -= 10;
					if (Data::item_x < 0)
						Data::item_x += 10;
				}
				else
				{
					Data::weapon_x -= 10;
					if (Data::weapon_x < 0)
						Data::weapon_x += 10;
				}
				upKey = false;
			}

		}
		else upKey = true;

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
			else if (Data::setWeapon)
			{
				stopTheGame = true;
				SwapWeapon();
				UnitManager::Get()->returnPlayer().SetAbility(Data::puttingItemSlot, Data::puttingWeaponSlot);
			}
			else if (Data::weaponOn)
			{
				stopTheGame = true;
				Data::setWeapon = true;
				Data::weapon_x = 1;
			}
			else if (Data::setItem)
			{
				stopTheGame = true;
				SwapItem();
				UnitManager::Get()->returnPlayer().SetAbility(Data::puttingItemSlot, Data::puttingWeaponSlot);
			}
			else if (Data::itemOn)
			{
				stopTheGame = true;
				Data::setItem = true;
				Data::item_x = 1;
			}
			else
			{
				if (Data::skillOn)
				{
					if (Data::skillCount == Data::button_x)
					{
						stopTheGame = true;
						Data::skillOn = false;
					}
					else if(Data::skillSet[Data::button_x-1] != nullptr)
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
						Data::skillOn = false;
					}
					else
					{
						stopTheGame = true;
						Data::alertCount = 9;
						Warning warning;
						warning.Alert();
					}
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
						Data::itemOn = true;
						Data::item_x = -1;
						Data::puttingItem_x = 1;
						TextManager::Get()->SetRenderer(ITEM);
						break;
					case 4:
						stopTheGame = true;
						Data::weaponOn = true;
						Data::weapon_x = -1;
						Data::puttingWeapon_x = 1;
						TextManager::Get()->SetRenderer(WEAPON);
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
				UnitManager::Get()->returnPlayer().TurnReturn() = false;
				UnitManager::Get()->returnPlayer().AP() -= 100;
				UnitManager::Get()->returnPlayer().SetAbility(Data::puttingItemSlot, Data::puttingWeaponSlot);
				UnitManager::Get()->returnPlayer().BuffRemove();
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
			else if (Data::setWeapon)
			{
				Data::setWeapon = false;
				Data::weapon_x = -1;
			}
			else if (Data::weaponOn)
			{
				Data::button_x = 1;
				Data::weaponOn = false;
				TextManager::Get()->SetRenderer(INGAME);
			}
			else if (Data::setItem)
			{
				Data::setItem = false;
				Data::item_x = -1;
			}
			else if (Data::itemOn)
			{
				Data::button_x = 1;
				Data::itemOn = false;
				TextManager::Get()->SetRenderer(INGAME);
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
				Data::button_x = 1;
				break;
			case 1: // 케릭터 선택창
			{
				TextManager::Get()->SetRenderer(INGAME);

				UnitManager::Get()->SetPlayer(Data::button_x);
				UnitManager::Get()->SetEnemy(0);
				Data::skillCount = 0;

				while (strlen(skills[Data::button_x - 1][Data::skillCount])) { ++Data::skillCount; }
				Data::skillCount += 3;
				Data::skillSet = new Func[Data::skillCount - 1];

				for (int i = 0; i < Data::skillCount - 1; i++)
					Data::skillSet[i] = nullptr;

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
			Data::button_x = 0;
			break;
			}
			Data::currentCount = 0;
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