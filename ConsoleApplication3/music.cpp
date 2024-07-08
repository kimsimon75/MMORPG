#include "music.h"

MCI_OPEN_PARMS openBgm = {};
MCI_PLAY_PARMS playBgm = {};
MCI_OPEN_PARMS openShuffleSound = {};
MCI_PLAY_PARMS playShuffleSound = {};
MCI_OPEN_PARMS openGetDamageSound = {};
MCI_PLAY_PARMS playGetDamageSound = {};
MCI_OPEN_PARMS openRestoreSound = {};
MCI_PLAY_PARMS playRestoreSound = {};
MCI_OPEN_PARMS openfemaleSound = {};
MCI_OPEN_PARMS openGetDamage3Sound = {};
MCI_OPEN_PARMS openGetDamage2Sound = {};

int dwID;

void playingBgm(void) {
    openBgm.lpstrElementName = BGM;            //파일 오픈
    openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;

    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openBgm);    //음악 반복 재 생
}

void playingAttackSound(void) {
    openShuffleSound.lpstrElementName = SHUFFLE;    //파일 오픈
    openShuffleSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openShuffleSound);
    dwID = openShuffleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openShuffleSound);    //음악을 한 번 재생
}

void playingBarkSound(void) {
    openShuffleSound.lpstrElementName = BARK;    //파일 오픈
    openShuffleSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openShuffleSound);
    dwID = openShuffleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openShuffleSound);    //음악을 한 번 재생
}

void playingGetDamage(void) {
    openGetDamageSound.lpstrElementName = PLAYER;    //파일 오픈
    openGetDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamageSound);
    dwID = openGetDamageSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamageSound);    //음악을 한 번 재생
}

void playingRestore(void) {
    openRestoreSound.lpstrElementName = RESTORE;    //파일 오픈
    openRestoreSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openRestoreSound);
    dwID = openRestoreSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openRestoreSound);    //음악을 한 번 재생
}

void playingFemale(void) {
    openfemaleSound.lpstrElementName = FEMALE;    //파일 오픈
    openfemaleSound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openfemaleSound);
    dwID = openfemaleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openfemaleSound);    //음악을 한 번 재생
}

void playingGetDamage2(void) {
    openGetDamage2Sound.lpstrElementName = PLAYER2;    //파일 오픈
    openGetDamage2Sound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamage2Sound);
    dwID = openGetDamage2Sound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamage2Sound);    //음악을 한 번 재생
}

void playingGetDamage3(void) {
    openGetDamage3Sound.lpstrElementName = PLAYER3;    //파일 오픈
    openGetDamage3Sound.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamage3Sound);
    dwID = openGetDamage3Sound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamage3Sound);    //음악을 한 번 재생
}