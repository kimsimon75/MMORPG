#pragma once
#include <Windows.h>
#include <mmsystem.h>             //����
#include <Digitalv.h>

#pragma comment (lib, "winmm.lib")               //����

extern MCI_OPEN_PARMS openBgm;
extern MCI_PLAY_PARMS playBgm;
extern MCI_OPEN_PARMS openShuffleSound;
extern MCI_PLAY_PARMS playShuffleSound;
extern MCI_OPEN_PARMS openGetDamageSound;
extern MCI_PLAY_PARMS playGetDamageSound;
extern MCI_OPEN_PARMS openRestoreSound;
extern MCI_PLAY_PARMS playRestoreSound;
extern MCI_OPEN_PARMS openfemaleSound;

extern MCI_OPEN_PARMS openGetDamage3Sound;
extern MCI_OPEN_PARMS openGetDamage2Sound;

#define BGM L"�Ҹ�\\����ǹ��� - �̷����ö����.mp3"    //BGM ��� ����
#define SHUFFLE L"�Ҹ�\\slash-21834.mp3"
#define BARK L"�Ҹ�\\bark.mp3"//ȿ���� ��� ����
#define PLAYER L"�Ҹ�\\MP_Zombie Moan.mp3"
#define RESTORE L"�Ҹ�\\MP_Shooting Star.mp3"
#define FEMALE L"�Ҹ�\\8055604933.mp3"
#define PLAYER2 L"�Ҹ�\\8055604272.mp3"
#define PLAYER3 L"�Ҹ�\\8055604271.mp3"
extern int dwID;




void playingBgm(void);
void playingAttackSound(void);

void playingBarkSound(void);

void playingGetDamage(void);

void playingRestore(void);

void playingFemale(void);

void playingGetDamage2(void);

void playingGetDamage3(void);
