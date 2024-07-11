#pragma once

enum TEXTID {
	STORY = 1,
	PLAYERINFO,
	HOWTOPLAY,
	INGAME,
	ITEM,
	WEAPON,
};

extern const char map[40][160];

extern const char button[5][31];
extern const char textBox[9][67];
extern const char itemBox[3][10];

extern const char itemMap[40][160];

extern const char text[4][6][16];

extern const char skills[4][7][16];

extern const char weaponSkill[21][18];

extern const char itemName[20][30];

extern const char weaponName[20][30];

extern const char itemForm[21][4];

extern const char weaponForm[21][4];

extern const char skillCoefficient[4][6][120];

extern const char weaponSkillCoefficient[20][120];

extern const char skillinfo[4][6][4][120];

extern const char weapon_Skill_info[21][3][120];

extern const char unitInfo[9][15];
extern const char itemInfo[21][3][120];
extern const char weaponInfo[21][3][120];
extern const char asciiArt1[4][30];
extern const char asciiArt2[20][40];
extern const char story[8][123];
extern const char howToPlay[][123];
extern const char unit[4][4][142];

extern const char enemy[4][4][142];

extern const char alert[9][5][142];