#pragma once
#include <Windows.h>
#include <mmsystem.h>             //음악
#include <Digitalv.h>

#pragma comment (lib, "winmm.lib")               //음악

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

#define BGM L"소리\\배달의민족 - 미래도시라솔파.mp3"    //BGM 경로 지정
#define SHUFFLE L"소리\\slash-21834.mp3"
#define BARK L"소리\\bark.mp3"//효과음 경로 지정
#define PLAYER L"소리\\MP_Zombie Moan.mp3"
#define RESTORE L"소리\\MP_Shooting Star.mp3"
#define FEMALE L"소리\\8055604933.mp3"
#define PLAYER2 L"소리\\8055604272.mp3"
#define PLAYER3 L"소리\\8055604271.mp3"
extern int dwID;




void playingBgm(void);
void playingAttackSound(void);

void playingBarkSound(void);

void playingGetDamage(void);

void playingRestore(void);

void playingFemale(void);

void playingGetDamage2(void);

void playingGetDamage3(void);
