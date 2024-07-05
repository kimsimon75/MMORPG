#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include "텍스트.h"
#include "유닛메니저.h"
#include "뮤직.h"

using namespace std;
#pragma comment(lib,"winmm.lib")

using Func = pair<bool,int>(Player::*)(Unit&);
COORD boy;


struct Data {
	static COORD pos ;

	static int button_x;
	static int state;
	static int alertCount;
	static short keyInput;
	static short maxCount;
	static short currentCount;
	static int skillCount;
	static int gameRound;
	static bool skillOn;
	static Func* skillSet;

	void posinit()
	{
		pos.X = 0;
		pos.Y = 0;
	}
};

COORD Data::pos{ 0,0 };
int Data::button_x = 1;
int Data::state = 0;
int Data::alertCount = 0;
short Data::keyInput = 1;
short Data::maxCount = 4;
short Data::currentCount = 0;
int Data::skillCount = 0;
int Data::gameRound = 0;
bool Data::skillOn = false;
Func* Data::skillSet = nullptr;

void Map();
void Status();





class Text_Align {
public:
	static void text_center(const char* text)
	{
		Data::pos.X = (105 - (int)strlen(text)) / 2;
	}

	static void text_center(int length)
	{
		Data::pos.X = (105 - length) / 2;
	}

	static void text_center(int& a, int& b, int length)
	{
		Data::pos.X = a + (b - a - length) / 2;
	}

	static void line_center(int a, int b, int line)
	{
		Data::pos.Y = a + ((b - a - line) / 2);
	}
};

void SkillCoefficient(const char* string)
{

	if (strlen(string) != 0 && strcmp(string, "없음") != 0)
	{
		char ch[50] = {};
		char ch2[200] = {};
		int a;

		if (string[0] == '0')
			a = 0;
		else if (string[0] == '1')
			a = 1;
		strcpy(ch, string + 2);
		strcat(ch2, "계수 : ");
		strcat(ch2, ch);
		strcat(ch2, " = ");
		strcat(ch2, Calculate(ch));
		strcat(ch2, a ? " 초" : " 데미지");

		Data::pos.Y += 2;
		Text_Align::text_center(ch2);

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("%s", ch2);
	}
}


class Text {
public:
	virtual void Render() abstract;
};

class HowToPlay : public Text {
public:
	void Render() override
	{

	}
};

class PlayerInfo : public Text {
public:
	void Render()
	{
		for (int i = 0; i < 4; i++) // 설명글
		{
			Data::pos.Y = 2 + i * 2;
			Text_Align::text_center(unit[Data::button_x - 1][i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%s", unit[Data::button_x - 1][i]);
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
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf(printf_temp);

		}
		puts("");
		fclose(rfp);

	}
};


class InGame : public Text {
public:
	void Render()
	{
		if (!Data::skillOn)
		{
			for (int i = 0; i < 4; i++) // 설명글
			{
				Data::pos.Y = 2 + i * 2;
				Text_Align::text_center(enemy[Data::gameRound][i]);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("%s", enemy[Data::gameRound][i]);
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
		if (UnitManager::Get()->returnEnemy().GetDamage(false))
			playingAttackSound();

		for (int i = 0; i < ((UnitManager::Get()->returnEnemy().GetDamage(false)) ? 4 : 1); i++)
		{
			Data::pos.X = X;
			if (UnitManager::Get()->returnEnemy().iced_time())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			}
			if (UnitManager::Get()->returnEnemy().GetDamage(false))
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
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("?");
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
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf(printf_temp);
			}
			if (UnitManager::Get()->returnEnemy().GetDamage(false))
			{
				Sleep(100);
				Data::keyInput = 1;
			}
			else if (UnitManager::Get()->returnEnemy().WTF())
			{
				Sleep(1000);
				Data::keyInput = 1;
				UnitManager::Get()->returnEnemy().WTF() = false;
			}

			puts("");
			fclose(rfp);
		}

		if (UnitManager::Get()->returnEnemy().GetDamage(true))
			mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		 if (UnitManager::Get()->returnPlayer().WTF())
		{ 
			Data::pos.Y = 33;
			Text_Align::text_center("??");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("??");
			Sleep(1000);
			UnitManager::Get()->returnPlayer().WTF() = false;

		}
	}
};

class Story : public Text {

	void Render()

	{
		for (int i = 0; i < 3; i++)
		{
			Data::pos.Y = 2 + i * 2;
			Text_Align::text_center(story[i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%s\n\n", story[i]);
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
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf(printf_temp);

		}
		puts("");
		fclose(rfp);
	}
};

static void Map()
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 40; i++)
		{
			printf("%s\n", map[i]);
		}
	}

static void Button()
{
	{

		if (Data::state <= 2 && Data::alertCount <= 1)
			for (int k = 0; k < ((Data::state == 2) ? ((UnitManager::Get()->returnPlayer().GetDamage(false)) ? 4 : 1) : 1); k++)
			{
				if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false))
				{
					Map();
					Status();
					InGame inGame;
					inGame.Render();
					playingGetDamage();
				}

				for (int i = (Data::alertCount) ? 1 : 0; i < ((Data::alertCount) ? 3 : 4); i++)
				{
					if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false))
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					else
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Data::button_x == i + Data::currentCount + 1) ? 14 : 15);
					for (int j = 0; j < 5; j++)
					{
						Data::pos.X = 6 + 24 * i;
						Data::pos.Y = 32 + j;
						int X = Data::pos.X;
						if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false))
							Data::pos.X = (k % 2 == 0) ? X - 2 : X + 2;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
						printf("%s\n", button[j]);
					}
				}
				if (Data::state == 2 && UnitManager::Get()->returnPlayer().GetDamage(false))
					Sleep(100);
			}
		if (Data::state==2 && UnitManager::Get()->returnPlayer().GetDamage(true))
			mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);

	}
}


static void Play()
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
				int length = (int)strlen((Data::alertCount == 1) ? alert[0][i] : ((Data::skillOn) ? skills[UnitManager::Get()->returnPlayer().PN() - 1][i] : text[Data::state][i]));
				Text_Align::text_center(start, end, length);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("%s", (Data::alertCount == 1) ? alert[0][i] : ((Data::skillOn) ? skills[UnitManager::Get()->returnPlayer().PN() - 1][i] : text[Data::state][i]));
			}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		if (!Data::alertCount)
		{
			if (Data::currentCount > 0)
			{
				Data::pos.X = 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("<--");
			}

			if (Data::currentCount + 4 < ((Data::skillOn) ? Data::skillCount : Data::maxCount))
			{
				Data::pos.X = 99;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("-->");
			}
		}
		if (Data::state == 2)
		{
			Data::pos.Y = 30;
			Text_Align::text_center("     / 100 | A  P |      / 100");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("     / 100 | A  P |      / 100");
			Text_Align::text_center("     / 100 | A  P |      / 100");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%d", UnitManager::Get()->returnEnemy().AP());
			Text_Align::text_center("     / 100 | A  P |      / 100");
			Data::pos.X += 20;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%d", UnitManager::Get()->returnPlayer().AP());
		}

	}
}

static void Status()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	if (Data::state == 2)
	{
		Data::pos.X = 5;
		Data::pos.Y = 12;
		for (int i = 0; i < 7; i++) // 스테이터스
		{
			int* p = (int*)&UnitManager::Get()->returnEnemy();
			Data::pos.Y += 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);

			if (i == 0)
				printf("%s : %d + %d / %d", unitInfo[i], p[i], p[i + 9], p[i + 7]);
			else if (i == 1)
				printf("%s : %d / %d", unitInfo[1], p[i], p[i + 7]);
			else
				printf("%s : %d", unitInfo[i], p[i]);

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	if (Data::state >= 2)
	{
		Data::pos.Y = 10;
		Data::pos.X = 80;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("Round : %d", Data::gameRound + 1);
	}
	Data::pos.X = 60 + Data::state * 10;
	Data::pos.Y = 12;

	for (int i = 0; i < 7; i++)
	{
		Data::pos.Y += 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		int* p = (int*)&UnitManager::Get()->returnPlayer();
		if (i == 0)
		{
			if (!UnitManager::Get()->returnPlayer().BarrierCool())
				printf("%s : %d / %d", unitInfo[i], p[i] + p[i + 9], p[i + 7]);
			else
			{
				printf("%s : ", unitInfo[i]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("%d + %d ", p[i], p[i + 9]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("/ %d", p[i + 7]);
			}
		}
		else if (i == 1)
			printf("%s : %d / %d", unitInfo[1], p[i], p[i + 7]);
		else
			printf("%s : %d", unitInfo[i], p[i]);
	}


	if (Data::state == 2 && UnitManager::Get()->returnEnemy().PoisonTime())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		Data::pos.X = 6;
		Data::pos.Y = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("●%d", UnitManager::Get()->returnEnemy().PoisonTime());
	}
	if (Data::state == 2 && UnitManager::Get()->returnEnemy().IgniteTime())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		Data::pos.X = 10;
		Data::pos.Y = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("●%d", UnitManager::Get()->returnEnemy().IgniteTime());
	}

	if (UnitManager::Get()->returnPlayer().PoisonTime())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		Data::pos.X = 95;
		Data::pos.Y = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("%d●", UnitManager::Get()->returnPlayer().PoisonTime());
	}
	if (UnitManager::Get()->returnPlayer().IgniteTime())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		Data::pos.X = 91;
		Data::pos.Y = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("%d●", UnitManager::Get()->returnPlayer().IgniteTime());
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


}



static void SkillInformation()
{
	for (int i = 0; i < 4; i++) // 설명글
	{
		if (strlen(skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]) == 0)
			break;
		Data::pos.Y = 2 + i * 2;
		Text_Align::text_center(skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
		printf("%s", skillinfo[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1][i]);
	}
	SkillCoefficient(skillCoefficient[UnitManager::Get()->returnPlayer().PN() - 1][Data::button_x - 1]);
}



class Warning {
public:
	static void GameOver()
	{
		Data::keyInput = 1;
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

				printf("%d %d", max, line);
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
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf(printf_temp);
		}
		puts("");
		fclose(rfp);

		Sleep(1500);
		gameover = false;


	}

	static void Alert()

	{
		Data::pos.X = 30;
		Data::pos.Y = 19;
		for (char i = 0; i < 9; i++)
		{
			Data::pos.Y += 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%s", textBox[i]);
		}
		if (Data::alertCount == 1)
		{
			int line = 1;
			Text_Align::text_center(alert[Data::alertCount - 1][0]);
			Text_Align::line_center(20, 29, line);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
			printf("%s", alert[Data::alertCount - 1][0]);
		}
		else if (Data::alertCount >= 2)
		{
			int line = 0;
			for (; strlen(alert[Data::alertCount - 1][line]); line++) {}

			Text_Align::line_center(20, 29, 2 * line - 1);

			for (int i = 0; i < line; i++)
			{
				Text_Align::text_center(alert[Data::alertCount - 1][i]);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Data::pos);
				printf("%s", alert[Data::alertCount - 1][i]);
				Data::pos.Y += 2;
			}
			for (int i = 0; i < 40; i++)
			{
				if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					break;
				Sleep(50);
			}
			Data::alertCount = 0;
			Data::skillOn = true;
			Data::keyInput = 1;
		}
	}
};

