#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "텍스트.h"
#include "유닛.h"
#include "유닛메니저.h"

using namespace std;

	COORD pos = { 0,0 };

	int gameRound = 0;

	int button_x = 1;
	int state = 0;
	int alertCount = 0;
	short keyInput = 1;
	short maxCount = 4;
	short currentCount = 0;

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
		for (int i = (alertCount == 1) ? 1 : currentCount, init = i; i < ((alertCount == 1) ? 3 : (maxCount<4) ? maxCount : currentCount+4); i++) // 버튼 틀 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (button_x == i + 1) ? 14 : 15);
			pos.X = 12 + 24 * ((alertCount == 1) ? i : (i - init));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", (alertCount==1) ? alert[0][i] : text[state][i]);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		if(currentCount>0)
		{
			pos.X = 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("<--");
		}

		if(currentCount+4<maxCount)
		{
			pos.X = 99;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("-->");
		}

		pos.X = 65 + state * 10;
		pos.Y = 12;

		if (state > 0)
			for (int i = 0; i < 7; i++)
			{
				pos.Y += 2;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				int* p = (int*)UnitManager::Get()->returnPlayer();
				if (i < 2)
					printf("%s : %d / %d", unitInfo[i], p[i], p[i + 7]);
				else
					printf("%s : %d", unitInfo[i], p[i]);
			}
		pos.Y += 3;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if (state >= 2)
			printf("Round : %d", gameRound + 1);


	}
}
void text_center( char* text)
{
	pos.X = (105 - (int)strlen(text)) / 2;
}

void text_center( int& length)
{
	pos.X = (105 - length) / 2;
}

void line_center(int a, int b, int& line)
{
	pos.Y = a + ceil(((double)b - a - line) / 2);
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
		for (int i = 0; i < 4; i++) // 그림 렌더
		{
			pos.Y =2 + i * 2;
			text_center(unit[button_x-1][i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", unit[button_x-1][i]);
		}

			char printf_temp[256];
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

		pos.X = 20 + state * 10;
		pos.Y = 12;
		for (int i = 0; i < 4; i++) // 설명글
		{
			pos.Y = 2 + i * 2;
			text_center(enemy[gameRound][i]);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf("%s", enemy[gameRound][i]);
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		pos.X = 5;
		pos.Y = 12;

		for (int i = 0; i < 7; i++) // 스테이터스
		{
			int* p = (int*)UnitManager::Get()->returnEnemy();
			pos.Y += 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			if(i<2)
			printf("%s : %d / %d", unitInfo[i], p[i], p[i+7]);
			else
				printf("%s : %d", unitInfo[i], p[i]);
		
		}

		char printf_temp[256];
		FILE* rfp;
		rfp = fopen(asciiArt2[gameRound], "rt"); // 그림 렌더
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
				max = strlen(printf_temp);
			line++;
		}  
		text_center(max);
		line_center(0, 40, line);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		rfp = fopen(asciiArt2[gameRound], "rt");
		while (fgets(printf_temp, 255, rfp) != NULL)
		{
			pos.Y += 1;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			printf(printf_temp);
		}
		puts("");
		fclose(rfp);

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
