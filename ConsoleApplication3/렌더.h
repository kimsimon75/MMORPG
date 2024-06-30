#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mmsystem.h>
#include "텍스트.h"
#include "유닛메니저.h"
#include "뮤직.h"

using namespace std;
#pragma comment(lib,"winmm.lib")

using Func = void(Player::*)(Unit&);

class Data {

};
	COORD pos = { 0,0 };

	int gameRound = 0;

	int button_x = 1;
	int state = 0;
	int alertCount = 0;
	short keyInput = 1;
	short maxCount = 4;
	short currentCount = 0;
	int skillCount = 0;
	bool myTurn = false;
	bool enemyTurn = false;
	bool skillOn = false;
	Func* skillSet = nullptr;

	void text_center(const char* text)
	{
		pos.X = (106 - (int)strlen(text)) / 2;
	}

	void text_center(int& length)
	{
		pos.X = (106 - length) / 2;
	}
	void text_center(int& a, int& b, int& length)
	{
		pos.X = a + (b - a - length) / 2;
	}

	void line_center(int a, int b, int& line)
	{
		pos.Y = a +((b - a - line) / 2);
	}


	void Map()
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int i = 0; i < 40; i++)
		{
			printf("%s\n", map[i]);
		}
	}



void Button()
{
	
	if(state<=2)
	for (int i =(alertCount==1)? 1 : 0; i < ((alertCount == 1) ? 3 : 4); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (button_x == i+currentCount + 1) ? 14 : 15);
		for (int j = 0; j < 5; j++)
		{
			pos.X = 6 + 24 * i;
			pos.Y = 32 + j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s\n", button[j]);
		}
	}

}


void Play()
{
	if(state<3)   
	{
		pos.Y = 34;
		for (int i = (alertCount == 1) ? 1 : currentCount, init = i; i < ((alertCount == 1) ? 3 : (((skillOn) ? skillCount : maxCount) < 4) ? ((skillOn) ? skillCount : maxCount) : currentCount + 4); i++) // 버튼 텍스트 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (button_x == i + 1) ? 14 : 15);

			int start = 8 + 24 * ((alertCount == 1) ? i : (i-init));
			int end = 24 + 24 * ((alertCount == 1) ? i : (i - init));
			int length = (int)strlen((alertCount == 1) ? alert[0][i] : ((skillOn) ? skills[UnitManager::Get()->returnPlayer().PN() - 1][i] : text[state][i]));
			text_center(start, end, length);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", (alertCount == 1) ? alert[0][i] : ((skillOn) ? skills[UnitManager::Get()->returnPlayer().PN()-1][i] : text[state][i]));
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		if(alertCount!=1)
		{
			if (currentCount > 0)
			{
				pos.X = 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("<--");
			}

			if (currentCount + 4 < ((skillOn) ? skillCount : maxCount))
			{
				pos.X = 99;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("-->");
			}
		}

	}
}

void Status()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	if(state==2)
	{
		pos.X = 5;
		pos.Y = 12;
		for (int i = 0; i < 7; i++) // 스테이터스
		{
			int* p = (int*)&UnitManager::Get()->returnEnemy();
			pos.Y += 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			if (i < 2)
				printf("%s : %d / %d", unitInfo[i], p[i], p[i + 7]);
			else
				printf("%s : %d", unitInfo[i], p[i]);

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	pos.X = 65 + state * 10;
	pos.Y = 12;

		for (int i = 0; i < 7; i++)
		{
			pos.Y += 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			int* p = (int*)&UnitManager::Get()->returnPlayer();
			if (i < 2)
				printf("%s : %d / %d", unitInfo[i], p[i], p[i + 7]);
			else
				printf("%s : %d", unitInfo[i], p[i]);
		}

	if (state >= 2)
	{
		pos.Y += 3;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("Round : %d", gameRound + 1);
	}

	if (UnitManager::Get()->returnPlayer().poison == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		pos.X = 6;
		pos.Y = 30;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("●%d", UnitManager::Get()->returnPlayer().PoisonTime());
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void GameOver()
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

			printf("%d %d", max, line);
			max = (int)strlen(printf_temp);
		}
		line++;
	}
	fclose(rfp);
	text_center(max);
	line_center(-4, 41, line);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	rfp = fopen("이미지\\게임오버.tmg", "rt");
	while (fgets(printf_temp, 255, rfp) != NULL)
	{
		pos.Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf(printf_temp);
	}
	puts("");
	fclose(rfp);

		Sleep(1500);
		gameover = false;


}



void Alert()
{
	pos.X = 30;
	pos.Y = 19;
	for (char i = 0; i < 9; i++)
	{
		pos.Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("%s", textBox[i]);
	}	
	if (alertCount == 1)
	{
		int line = 1;
		text_center(alert[0][0]);
		line_center(20, 28, line);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("%s", alert[0][0]);
	}
}

void SkillInformation()
{
	for (int i = 0; i < 4; i++) // 설명글
	{
		pos.Y = 4 + i * 2;
		text_center(skillinfo[UnitManager::Get()->returnPlayer().PN()-1][button_x - 1][i]);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		printf("%s", skillinfo[UnitManager::Get()->returnPlayer().PN()-1][button_x - 1][i]);
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
			pos.Y =2 + i * 2;
			text_center(unit[button_x-1][i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", unit[button_x-1][i]);
		}

			char printf_temp[256]; // 그림 렌더
			FILE* rfp;
			rfp = fopen(asciiArt1[button_x - 1], "rt");
			pos.Y = 10;
			pos.X = 15;
			if(rfp==NULL)
				return ;

			while (fgets(printf_temp, 255, rfp) != NULL)
			{
				pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf(printf_temp);

			}
			puts("");
			fclose(rfp);

	}
};


class EnemyInfo : public Text {
	void Render()
	{
		if(!skillOn)
		{
			for (int i = 0; i < 4; i++) // 설명글
			{
				pos.Y = 2 + i * 2;
				text_center(enemy[gameRound][i]);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf("%s", enemy[gameRound][i]);
			}
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		
		pos.X = 5;
		pos.Y = 12;

		char printf_temp[256];
		FILE* rfp;
		rfp = fopen(asciiArt2[gameRound], "rt"); // 그림 렌더
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
		text_center(max);
		line_center(0, 40, line);
		int X = pos.X;
		if (UnitManager::Get()->returnEnemy().GetDamage(false))
			playingAttackSound();

		for (int i = 0; i < ((UnitManager::Get()->returnEnemy().GetDamage(false)) ? 4 : 1); i++)
		{
			if(UnitManager::Get()->returnEnemy().GetDamage(false))
			{
				Map();
				Status();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				pos.X = (i % 2 == 1) ? X - 2 : X + 2;
			}
				line_center(0, 40, line);
			rfp = fopen(asciiArt2[gameRound], "rt");
			while (fgets(printf_temp, 255, rfp) != NULL)
			{
				pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				printf(printf_temp);
			}
			if (UnitManager::Get()->returnEnemy().GetDamage(false))
			{
				Sleep(100);
				keyInput = 1;
			}

			puts("");
			fclose(rfp);
		}
		if (UnitManager::Get()->returnEnemy().GetDamage(false))
		mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL);
		UnitManager::Get()->returnEnemy().GetDamage(true);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

};

class Story : public Text {

	void Render()
	{
		for (int i = 0; i < 3; i++)
		{
			pos.Y = 2+i*2;
			text_center(story[i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
		pos.Y += 2;
		pos.X = 18;
		while (fgets(printf_temp, 255, rfp) != NULL)
		{
			pos.Y += 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf(printf_temp);		

		}
		puts("");
		fclose(rfp);
	}
};
