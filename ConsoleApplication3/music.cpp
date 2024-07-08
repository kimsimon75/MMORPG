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
    openBgm.lpstrElementName = BGM;            //���� ����
    openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;

    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openBgm);    //���� �ݺ� �� ��
}

void playingAttackSound(void) {
    openShuffleSound.lpstrElementName = SHUFFLE;    //���� ����
    openShuffleSound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openShuffleSound);
    dwID = openShuffleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openShuffleSound);    //������ �� �� ���
}

void playingBarkSound(void) {
    openShuffleSound.lpstrElementName = BARK;    //���� ����
    openShuffleSound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openShuffleSound);
    dwID = openShuffleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openShuffleSound);    //������ �� �� ���
}

void playingGetDamage(void) {
    openGetDamageSound.lpstrElementName = PLAYER;    //���� ����
    openGetDamageSound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamageSound);
    dwID = openGetDamageSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamageSound);    //������ �� �� ���
}

void playingRestore(void) {
    openRestoreSound.lpstrElementName = RESTORE;    //���� ����
    openRestoreSound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openRestoreSound);
    dwID = openRestoreSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openRestoreSound);    //������ �� �� ���
}

void playingFemale(void) {
    openfemaleSound.lpstrElementName = FEMALE;    //���� ����
    openfemaleSound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openfemaleSound);
    dwID = openfemaleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openfemaleSound);    //������ �� �� ���
}

void playingGetDamage2(void) {
    openGetDamage2Sound.lpstrElementName = PLAYER2;    //���� ����
    openGetDamage2Sound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamage2Sound);
    dwID = openGetDamage2Sound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamage2Sound);    //������ �� �� ���
}

void playingGetDamage3(void) {
    openGetDamage3Sound.lpstrElementName = PLAYER3;    //���� ����
    openGetDamage3Sound.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openGetDamage3Sound);
    dwID = openGetDamage3Sound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openGetDamage3Sound);    //������ �� �� ���
}