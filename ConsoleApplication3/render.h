#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include "text.h"
#include "unitmanager.h"
#include "music.h"
#include "Buffer.h"

using namespace std;
#pragma comment(lib,"winmm.lib")

using Func = pair<bool,int>(Player::*)(Unit&);


struct Data {
	static COORD pos ;

	static int button_x;
	static int item_x;
	static int weapon_x;
	static char puttingItemSlot[6];
	static int puttingItem_x;
	static char puttingWeaponSlot[2];
	static int puttingWeapon_x;
	static char itemSlot[30];
	static int itemSlot_x;
	static char weaponSlot[30];
	static int weaponSlot_x;
	static int state;
	static int alertCount;
	static short maxCount;
	static short currentCount;
	static int skillCount;
	static int gameRound;
	static bool skillOn;
	static bool setItem;
	static bool itemOn;
	static bool setWeapon;
	static bool weaponOn;
	static Func* skillSet;
	static Func weaponSkill[20];
};


void Map();
void Status();

class Text_Align {
public:
	static void text_center(const char* text);

	static void text_center(int length);

	static void text_center(int& a, int& b, int length);

	static void line_center(int a, int b, int line);
};

void SkillCoefficient(const char* string);


class Text {
public:
	virtual void Render() abstract;
};

class HowToPlay : public Text {
public:
	void Render() override;
};

class PlayerInfo : public Text {
public:
	void Render();
};


class InGame : public Text {
public:
	void Render();
};

class Story : public Text {

	void Render();
};

class Item : public Text {
	void Render();
};

class Weapon : public Text {
	void Render();
};

void Button();


void Play();



void ItemInformation();



void SkillInformation();



class Warning {
public:
	static void GameOver();

	static void Alert();
};

