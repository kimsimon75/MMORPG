#include "render.h"
#include "textmanager.h"


COORD Data::pos{ 0,0 };
int Data::button_x = 1;
int Data::item_x = 10;
int Data::weapon_x = 10;
char Data::puttingItemSlot[6] = {};
int Data::puttingItem_x = 1;
char Data::puttingWeaponSlot[2] = {};
int Data::puttingWeapon_x = 0;
char Data::itemSlot[30] = {};
int Data::itemSlot_x = 0;
char Data::weaponSlot[30] = {};
int Data::weaponSlot_x = 0;
int Data::state = 0;
int Data::alertCount = 0;
short Data::maxCount = 4;
short Data::currentCount = 0;
int Data::skillCount = 0;
int Data::gameRound = 0;
bool Data::skillOn = false;
bool Data::setItem = false;
bool Data::itemOn = false;
bool Data::setWeapon = false;
bool Data::weaponOn = false;
Func* Data::skillSet = nullptr;
Func Data::weaponSkill[20] = {};

void Map()
{
	Data::pos.X = 0;
	if (Data::itemOn || Data::weaponOn)
		for (int i = 0; i < 40; i++)
		{
			Data::pos.Y = i;
			WriteBuffer(Data::pos, 15, itemMap[i]);
		}
	else
		for (int i = 0; i < 40; i++)
		{
			Data::pos.Y = i;
			WriteBuffer(Data::pos, 15, map[i]);
		}
}

void Status()
{
	char buf[100];
	if (!Data::itemOn && !Data::weaponOn)
	{
		if (Data::state == 2 && UnitManager::Get()->returnEnemy().PoisonTime())
		{
			Data::pos.X = 6;
			Data::pos.Y = 30;
			sprintf(buf, "●%d", UnitManager::Get()->returnEnemy().PoisonTime());
			WriteBuffer(Data::pos, 10, buf);
		}
		if (Data::state == 2 && UnitManager::Get()->returnEnemy().IgniteTime())
		{
			Data::pos.X = 10;
			Data::pos.Y = 30;
			sprintf(buf, "●%d", UnitManager::Get()->returnEnemy().IgniteTime());
			WriteBuffer(Data::pos, 10, buf);
		}

		if (UnitManager::Get()->returnPlayer().PoisonTime())
		{
			Data::pos.X = 95;
			Data::pos.Y = 30;
			sprintf(buf, "%d●", UnitManager::Get()->returnPlayer().PoisonTime());
			WriteBuffer(Data::pos, 10, buf);
		}
		if (UnitManager::Get()->returnPlayer().IgniteTime())
		{
			Data::pos.X = 91;
			Data::pos.Y = 30;
			sprintf(buf, "%d●", UnitManager::Get()->returnPlayer().IgniteTime());
			WriteBuffer(Data::pos, 10, buf);
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

		if (Data::state == 2)
		{
			Data::pos.X = 5;
			Data::pos.Y = 12;
			for (int i = 0; i < 7; i++) // 스테이터스
			{
				int* p = (int*)&UnitManager::Get()->returnEnemy();
				Data::pos.Y += 2;

				if (i == 0)
					sprintf(buf, "%s : %d + %d / %d", unitInfo[i], p[i], p[i + 9], p[i + 7]);
				else if (i == 1)
					sprintf(buf, "%s : %d / %d", unitInfo[1], p[i], p[i + 7]);
				else
					sprintf(buf, "%s : %d", unitInfo[i], p[i]);
				WriteBuffer(Data::pos, 14, buf);
			}
		}
		if (Data::state >= 2)
		{
			Data::pos.Y = 10;
			Data::pos.X = 80;
			sprintf(buf, "Round : %d", Data::gameRound + 1);
			WriteBuffer(Data::pos, 15, buf);
		}
	}


	Data::pos.X = 60 + Data::state * 10;
	Data::pos.Y = 12;

	if (Data::itemOn || Data::weaponOn)
	{
		Data::pos.X = 4;
		Data::pos.Y = 23;
	}

	for (int i = 0; i < 7; i++)
	{
		Data::pos.Y += 2;
		int* p = (int*)&UnitManager::Get()->returnPlayer();
		if (i == 0)
		{
			if (!UnitManager::Get()->returnPlayer().BarrierCool())
			{
				sprintf(buf, "%s : %d / %d", unitInfo[i], p[i] + p[i + 9], p[i + 7]);
				WriteBuffer(Data::pos, 12, buf);
			}
			else
			{
				sprintf(buf, "%s : %d + ", unitInfo[i], p[i]);
				WriteBuffer(Data::pos, 12, buf);
				Data::pos.X += strlen(buf);

				sprintf(buf, "%d", p[i + 9]);
				WriteBuffer(Data::pos, 14, buf);
				Data::pos.X += strlen(buf);

				sprintf(buf, " / %d", p[i + 7]);
				WriteBuffer(Data::pos, 12, buf);
				Data::pos.X = 60 + Data::state * 10;
			}
		}
		else if (i == 1)
		{
			sprintf(buf, "%s : %d / %d", unitInfo[1], p[i], p[i + 7]);
			WriteBuffer(Data::pos, 9, buf);
		}
		else
		{
			sprintf(buf, "%s : %d", unitInfo[i], p[i]);
			WriteBuffer(Data::pos, 15, buf);
		}

	}
}

void Text_Align::text_center(const char* text)
{
	Data::pos.X = (105 - (int)strlen(text)) / 2;
}

void Text_Align::text_center(int length)
{
	Data::pos.X = (105 - length) / 2;
}

void Text_Align::text_center(int& a, int& b, int length)
{
	Data::pos.X = a + (b - a - length) / 2;
}

void Text_Align::line_center(int a, int b, int line)
{
	Data::pos.Y = a + ((b - a - line) / 2);
}

void SkillCoefficient(const char* string)
{

	if (strlen(string) != 0 && strcmp(string, "없음") != 0)
	{
		char ch[50] = {};
		char ch2[200] = {};
		int a = 0;

		a = atoi(string);
		strcpy(ch, string + 2);
		strcat(ch2, "계수 : ");
		strcat(ch2, ch);
		strcat(ch2, " = ");
		strcat(ch2, CalculateEx(ch));
		strcat(ch2, a ? (a == 1 ? " 초" : " 체력") : " 데미지");

		Data::pos.Y += 2;
		Text_Align::text_center(ch2);

		WriteBuffer(Data::pos, 15, ch2);
	}
}


void Button()
{
	if (Data::state <= 2 && Data::alertCount <= 1)
		for (int k = 0; k < ((Data::state == 2) ? ((UnitManager::Get()->returnPlayer().GetDamage(false, nullptr, nullptr)) ? 4 : 1) : 1); k++)
		{
			if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false, nullptr, nullptr))
			{
				Map();
				Status();
				InGame inGame;
				inGame.Render();
				if (UnitManager::Get()->returnPlayer().PN() == 2)
					playingFemale();
				else if (UnitManager::Get()->returnPlayer().PN() == 4)
					playingGetDamage();
				else if (UnitManager::Get()->returnPlayer().PN() == 3)
					playingGetDamage2();
				else
					playingGetDamage3();
			}

			for (int i = (Data::alertCount) ? 1 : 0; i < ((Data::alertCount) ? 3 : 4); i++)
			{
				for (int j = 0; j < 5; j++)
				{
					Data::pos.X = 6 + 24 * i;
					Data::pos.Y = 32 + j;
					int X = Data::pos.X;
					if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false, nullptr, nullptr))
						Data::pos.X = (k % 2 == 0) ? X - 2 : X + 2;
					WriteBuffer(Data::pos, Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false, nullptr, nullptr) ? 12 : Data::button_x == i + Data::currentCount + 1 ? 14 : 15, button[j]);

				}
			}
			if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false, nullptr, nullptr))
			{
				FlipBuffer();
				Sleep(100);
			}
		}
	if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(true,Data::puttingItemSlot,&UnitManager::Get()->returnEnemy()))
	{
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Play()
{
	if (Data::state < 3)
	{
		Data::pos.Y = 34;
		if (Data::alertCount <= 1)
			for (int i = (Data::alertCount == 1) ? 1 : Data::currentCount, init = i; i < ((Data::alertCount == 1) ? 3 : (((Data::skillOn) ? Data::skillCount : Data::maxCount) < 4) ? ((Data::skillOn) ? Data::skillCount : Data::maxCount) : Data::currentCount + 4); i++) // 버튼 텍스트 
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Data::button_x == i + 1) ? 14 : 15);

				int start = 8 + 24 * ((Data::alertCount == 1) ? i : (i - init));
				int end = 24 + 24 * ((Data::alertCount == 1) ? i : (i - init));
				int length = (int)strlen((Data::alertCount == 1) ? alert[0][i] : ((Data::skillOn) ? i == Data::skillCount - 3 ? Data::puttingWeaponSlot[0] ? weaponSkill[Data::puttingWeaponSlot[0] - 1] : "무기 1" : i == Data::skillCount - 2 ? Data::puttingWeaponSlot[1] ? weaponSkill[Data::puttingWeaponSlot[1] - 1] : "무기 2" : (i == Data::skillCount - 1 ? "뒤로가기" : skills[UnitManager::Get()->returnPlayer().PN() - 1][i]) : text[Data::state][i]));
				Text_Align::text_center(start, end, length);
				WriteBuffer(Data::pos, Data::button_x == i + 1 ? 14 : 15, (Data::alertCount == 1) ? alert[0][i] : ((Data::skillOn) ? i == Data::skillCount - 3 ? Data::puttingWeaponSlot[0] ? weaponSkill[Data::puttingWeaponSlot[0] - 1] : "무기 1" : i == Data::skillCount - 2 ? Data::puttingWeaponSlot[1] ? weaponSkill[Data::puttingWeaponSlot[1] - 1] : "무기 2" : (i == Data::skillCount - 1 ? "뒤로가기" : skills[UnitManager::Get()->returnPlayer().PN() - 1][i]) : text[Data::state][i]));
			}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		if (!Data::alertCount)
		{
			if (Data::currentCount > 0)
			{
				Data::pos.X = 2;
				WriteBuffer(Data::pos, 15, "<--");
			}

			if (Data::currentCount + 4 < ((Data::skillOn) ? Data::skillCount : Data::maxCount))
			{
				Data::pos.X = 99;
				WriteBuffer(Data::pos, 15, "-->");
			}
		}
		if (Data::state == 2)
		{
			Data::pos.Y = 30;
			Text_Align::text_center("     / 100 | A  P |      / 100");
			WriteBuffer(Data::pos, 15, "     / 100 | A  P |      / 100");

			Text_Align::text_center("     / 100 | A  P |      / 100");
			char buf[100];
			sprintf(buf, "%d", UnitManager::Get()->returnEnemy().AP());
			WriteBuffer(Data::pos, UnitManager::Get()->returnEnemy().TurnReturn() ? 10 : 15, buf);

			Data::pos.X += 20;
			sprintf(buf, "%d", UnitManager::Get()->returnPlayer().AP());
			WriteBuffer(Data::pos, UnitManager::Get()->returnPlayer().TurnReturn() ? 10 : 15, buf);
		}

	}
}

void ItemInformation()
{
	char buf[100];
	Data::pos.X = 30;
	Data::pos.Y = 25;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);

	if (Data::itemOn)
	{
		WriteBuffer(Data::pos, 15, "*아이템 정보*");
		if (Data::setItem)
		{
			if (Data::item_x - 1 >= 0)
			{
				if (Data::itemSlot[Data::item_x - 1] > 0)
				{
					Data::pos.Y += 2;
					sprintf(buf, "아이템 이름 : %s", itemName[Data::itemSlot[Data::item_x - 1] - 1]);
					WriteBuffer(Data::pos, 15, buf);

					for (int i = 0; strlen(itemInfo[Data::itemSlot[Data::item_x - 1] - 1][i]); i++)
					{
						Data::pos.Y += 2;
						sprintf(buf, "%s", itemInfo[Data::itemSlot[Data::item_x - 1] - 1][i]);
						WriteBuffer(Data::pos, 15, buf);
					}
				}
			}
		}
		else
		{
			if (Data::puttingItemSlot[Data::puttingItem_x-1] > 0)
			{
				Data::pos.Y += 2;
				sprintf(buf, "아이템 이름 : %s", itemName[Data::puttingItemSlot[Data::puttingItem_x - 1] - 1]);
				WriteBuffer(Data::pos, 15, buf);

				for (int i = 0; strlen(itemInfo[Data::puttingItemSlot[Data::puttingItem_x - 1] - 1][i]); i++)
				{
					Data::pos.Y += 2;
					sprintf(buf, "%s", itemInfo[Data::puttingItemSlot[Data::puttingItem_x - 1] - 1][i]);
					WriteBuffer(Data::pos, 15, buf);
				}
			}
		}
	}
	else
	{
		WriteBuffer(Data::pos, 15, "*무기 정보*");
		if (Data::setWeapon)
		{
			if (Data::weapon_x - 1 >= 0)
			{
				if(Data::weaponSlot[Data::weapon_x-1]>0)
				{
					Data::pos.Y += 2;
					sprintf(buf, "무기 이름 : %s", weaponName[Data::weaponSlot[Data::weapon_x - 1] - 1]);
					WriteBuffer(Data::pos, 15, buf);

					for (int i = 0; strlen(weaponInfo[Data::weaponSlot[Data::weapon_x - 1] - 1][i]); i++)
					{
						Data::pos.Y += 2;
						sprintf(buf, "%s", weaponInfo[Data::weaponSlot[Data::weapon_x - 1] - 1][i]);
						WriteBuffer(Data::pos, 15, buf);
					}
				}
			}
		}
		else
			if(Data::puttingWeaponSlot[Data::puttingWeapon_x-1]>0)
			{
				Data::pos.Y += 2;
				sprintf(buf, "무기 이름 : %s", weaponName[Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] - 1]);
				WriteBuffer(Data::pos, 15, buf);
				for (int i = 0; strlen(weaponInfo[Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] - 1][i]); i++)
				{
					Data::pos.Y += 2;
					sprintf(buf, "%s", weaponInfo[Data::puttingWeaponSlot[Data::puttingWeapon_x - 1] - 1][i]);
					WriteBuffer(Data::pos, 15, buf);
				}
			}
	}
}

void SkillInformation()
{
	char buf[100];
	if (Data::button_x != Data::skillCount)
	{
		for (int i = 0; i < 4; i++) // 설명글
		{

			if (strlen((Data::button_x + 2 - Data::skillCount >= 0) ? weapon_Skill_info[Data::puttingWeaponSlot[Data::button_x + 2 - Data::skillCount]][i] : skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]) == 0)
				break;
			Data::pos.Y = 2 + i * 2;
			Text_Align::text_center(Data::button_x + 2 - Data::skillCount >= 0 ? weapon_Skill_info[Data::puttingWeaponSlot[Data::button_x + 2 - Data::skillCount]][i] : skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]);
			sprintf(buf, "%s", Data::button_x + 2 - Data::skillCount >= 0 ? weapon_Skill_info[Data::puttingWeaponSlot[Data::button_x + 2 - Data::skillCount]][i] : skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]);
			WriteBuffer(Data::pos, 15, buf);
		}
		if (Data::button_x + 2 < Data::skillCount)
			SkillCoefficient(skillCoefficient[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1]);
		else if (Data::puttingWeaponSlot[Data::button_x + 2 - Data::skillCount] - 1 >= 0)
		{
			SkillCoefficient(weaponSkillCoefficient[Data::puttingWeaponSlot[Data::button_x + 2 - Data::skillCount] - 1]);
		}
	}
}

void HowToPlay::Render()
{

}

void PlayerInfo::Render()
{
	for (int i = 0; i < 4; i++) // 설명글
	{
		Data::pos.Y = 2 + i * 2;
		Text_Align::text_center(unit[Data::button_x - 1][i]);
		WriteBuffer(Data::pos, 15, unit[Data::button_x - 1][i]);
	}

	char printf_temp[256]; // 그림 렌더
	FILE* rfp;
	rfp = fopen(asciiArt1[Data::button_x - 1], "rt");
	Data::pos.Y = 10;
	Data::pos.X = 15;
	if (rfp == NULL)
		return;

	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		Data::pos.Y += 1;
		WriteBuffer(Data::pos, 15, printf_temp);

	}
	fclose(rfp);

}

void Warning::GameOver()
{
	char printf_temp[256];
	FILE* rfp;
	rfp = fopen("이미지\\게임오버.tmg", "rt"); // 그림 렌더
	if (rfp == NULL)
	{
		printf("파일 불러오기에 실패했습니다.\n");
		return;
	}

	int max = 0;
	int line = 0;
	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		if (strlen(printf_temp) > max)
		{
			max = (int)strlen(printf_temp);
		}
		line++;
	}
	fclose(rfp);
	Text_Align::text_center(max);
	Text_Align::line_center(-4, 41, line);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
	rfp = fopen("이미지\\게임오버.tmg", "rt");
	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		Data::pos.Y += 1;
		WriteBuffer(Data::pos, 15, printf_temp);
	}
	FlipBuffer();
	fclose(rfp);

	Sleep(1500);
	gameover = false;


}

void Warning::Alert()
{
	Map();
	Button();
	TextManager::Get()->Update();
	Play();
	Data::pos.X = 30;
	Data::pos.Y = 19;
	for (char i = 0; i < 9; i++)
	{
		Data::pos.Y += 1;
		WriteBuffer(Data::pos, 15, textBox[i]);
	}
	if (Data::alertCount == 1)
	{
		int line = 1;
		Text_Align::text_center(alert[Data::alertCount - 1][0]);
		Text_Align::line_center(20, 29, line);
		WriteBuffer(Data::pos, 15, alert[Data::alertCount - 1][0]);

	}
	else if (Data::alertCount == 7 || Data::alertCount == 8)
	{
		int line = 2;
		Text_Align::line_center(20, 29, 2 * line - 1);
		Text_Align::text_center(alert[Data::alertCount - 1][0]);
		WriteBuffer(Data::pos, 15, alert[Data::alertCount - 1][0]);

		Data::pos.Y += 2;
		char s1[50] = { "*" };
		strcat(s1, Data::alertCount == 7 ? itemName[Data::gameRound] : weaponName[Data::gameRound]);
		strcat(s1, "*");
		Text_Align::text_center(s1);
		WriteBuffer(Data::pos, 15, s1);
		FlipBuffer();
		while (1)
			if (_getch() == 32)
				break;
		Data::alertCount = 0;
	}
	else if (Data::alertCount >= 2)
	{
		int line = 0;
		for (; strlen(alert[Data::alertCount - 1][line]); line++) {}

		Text_Align::line_center(20, 29, 2 * line - 1);

		for (int i = 0; i < line; i++)
		{
			Text_Align::text_center(alert[Data::alertCount - 1][i]);
			WriteBuffer(Data::pos, 15, alert[Data::alertCount - 1][i]);
			Data::pos.Y += 2;
		}
		FlipBuffer();
		for (int i = 0; i < 40; i++)
		{
			if(_kbhit())
			if (_getch() == 32)
				break;
			Sleep(50);
		}
		Data::alertCount = 0;
		Data::skillOn = true;
	}
}

void Item::Render()
{
	for (int k = 0; k<3; k++)
	{
		for (int j = 0; j < 10; j++)
		{
			Data::pos.X = 4 + j * 10;
			Data::pos.Y = 2 + k * 5;
			for (int i = 0; i < 3; i++)
			{
				WriteBuffer(Data::pos, Data::itemSlot_x==0 ? 15 : k * 10 + j == Data::item_x - 1 ? (Data::setItem ? 10 : 14) : k * 10 + j < Data::itemSlot_x ? 14 : 15, itemBox[i]);
				Data::pos.Y += 1;
			}

			if (strlen(itemForm[Data::itemSlot[j + k * 10]]))
			{
				Data::pos.X = 6 + j * 10;
				Data::pos.Y = 3 + k * 5;
				WriteBuffer(Data::pos, 15, itemForm[Data::itemSlot[j + k * 10]]);
			}

		}
	}


	for (int i = 0; i < 6; i++)
	{
		Data::pos.X = 24 + i * 10;
		Data::pos.Y = 19;
		for (int j = 0; j < 3; j++)
		{
			WriteBuffer(Data::pos, i == Data::puttingItem_x - 1 ? Data::setItem ? 12 : 10 : 15, itemBox[j]);
			Data::pos.Y += 1;
		}

		Data::pos.X = 26 + i * 10;
		Data::pos.Y = 20;
		WriteBuffer(Data::pos, 15, itemForm[Data::puttingItemSlot[i]]);
	}
}

void Weapon::Render()
{
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 10; j++)
		{
			Data::pos.X = 4 + j * 10;
			Data::pos.Y = 2 + k * 5;
			for (int i = 0; i < 3; i++)
			{
				WriteBuffer(Data::pos,Data::weaponSlot_x == 0 ? 15 : k * 10 + j == Data::weapon_x - 1 ? Data::setWeapon ? 10 : 14 : k * 10 + j < Data::weaponSlot_x ? 14 : 15, itemBox[i]);
				Data::pos.Y += 1;
			}
			if (strlen(weaponForm[Data::weaponSlot[j + k * 10]]))
			{
				Data::pos.X = 6 + j * 10;
				Data::pos.Y = 3 + k * 5;
				WriteBuffer(Data::pos, 15, weaponForm[Data::weaponSlot[j + k * 10]]);
			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		Data::pos.X = 44 + i * 10;
		Data::pos.Y = 19;
		for (int j = 0; j < 3; j++)
		{
			WriteBuffer(Data::pos, i == Data::puttingWeapon_x - 1 ? Data::setWeapon ? 12 : 10 : 15, itemBox[j]);
			Data::pos.Y += 1;
		}
		Data::pos.X = 46 + i * 10;
		Data::pos.Y = 20;
		WriteBuffer(Data::pos, 15, weaponForm[Data::puttingWeaponSlot[i]]);
	}
}

void InGame::Render()
{
	if (!Data::skillOn)
	{
		for (int i = 0; i < 4; i++) // 설명글
		{
			Data::pos.Y = 2 + i * 2;
			Text_Align::text_center(enemy[Data::gameRound][i]);
			WriteBuffer(Data::pos, 15, enemy[Data::gameRound][i]);
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	Data::pos.X = 5;
	Data::pos.Y = 12;

	char printf_temp[256];
	FILE* rfp;
	rfp = fopen(asciiArt2[Data::gameRound], "rt"); // 그림 렌더
	if (rfp == NULL)
	{
		printf("파일 불러오기에  실패했습니다.\n");
		return;
	}

	int max = 0;
	int line = 0;
	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		if (strlen(printf_temp) > max)
			max = (int)strlen(printf_temp);
		line++;
	}
	fclose(rfp);
	Text_Align::text_center(max);
	Text_Align::line_center(0, 40, line);
	int X = Data::pos.X;
	if (UnitManager::Get()->returnEnemy().GetDamage(false, nullptr, nullptr))
		playingAttackSound();

	for (int i = 0; i < ((UnitManager::Get()->returnEnemy().GetDamage(false, nullptr, nullptr)) ? 4 : 1); i++)
	{
		Data::pos.X = X;
		if (UnitManager::Get()->returnEnemy().iced_time())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		}
		if (UnitManager::Get()->returnEnemy().GetDamage(false, nullptr, nullptr))
		{
			Map();
			Status();
			Data::pos.X = (i % 2 == 1) ? X - 2 : X + 2;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		}
		else if (UnitManager::Get()->returnEnemy().WTF())
		{
			Map();
			Status();
			Data::pos.Y = 6;
			Text_Align::text_center(1);
			WriteBuffer(Data::pos, 15, "?");
			Data::pos.X = X;

		}
		else
		{
			Text_Align::text_center(max);
		}
		Text_Align::line_center(0, 40, line);
		rfp = fopen(asciiArt2[Data::gameRound], "rt");
		while (fgets(printf_temp, 255, rfp) != NULL)
		{
			Data::pos.Y += 1;
			WriteBuffer(Data::pos, UnitManager::Get()->returnEnemy().iced_time() ? 9 : UnitManager::Get()->returnEnemy().GetDamage(false, nullptr,nullptr) ? 12 : 15, printf_temp);
		}
		if (UnitManager::Get()->returnEnemy().GetDamage(false, nullptr, nullptr))
		{
			FlipBuffer();
			Sleep(100);
		}
		else if (UnitManager::Get()->returnEnemy().WTF())
		{
			FlipBuffer();
			Sleep(1000);
			UnitManager::Get()->returnEnemy().WTF() = false;
		}
		fclose(rfp);
	}

	if (UnitManager::Get()->returnEnemy().GetDamage(true,nullptr,&UnitManager::Get()->returnPlayer()))
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (UnitManager::Get()->returnPlayer().WTF())
	{
		Data::pos.Y = 34;
		Text_Align::text_center("??");
		WriteBuffer(Data::pos, 15, "??");
		FlipBuffer();
		Sleep(1000);
		UnitManager::Get()->returnPlayer().WTF() = false;
	}
}

void Story::Render()

{
	for (int i = 0; i < 3; i++)
	{
		Data::pos.Y = 2 + i * 2;
		Text_Align::text_center(story[i]);
		WriteBuffer(Data::pos, 15, story[i]);
	}

	char printf_temp[256];
	FILE* rfp;
	rfp = fopen("이미지\\성.tmg", "rt");
	if (rfp == NULL)
	{
		printf("파일 불러오기에 실패했습니다.\n");
		return;
	}
	Data::pos.Y += 2;
	Data::pos.X = 18;
	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		Data::pos.Y += 1;
		WriteBuffer(Data::pos, 15, printf_temp);
	}
	fclose(rfp);
}
