 //Ű���� �Է�
#pragma comment (lib, "winmm.lib")    //����
#include <mmsystem.h>;                //����
#include <Digitalv.h>;                //����

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openShuffleSound;
MCI_PLAY_PARMS playShuffleSound;
#define BGM L"�Ҹ�\\����ǹ��� - �̷����ö����.mp3"    //BGM ��� ����
#define SHUFFLE L"�Ҹ�\\slash-21834.mp3"
#define BARK L"�Ҹ�\\bark.mp3"//ȿ���� ��� ����
int dwID;

void playingBgm(void) {
    openBgm.lpstrElementName = BGM;            //���� ����
    openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 ����
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openBgm);    //���� �ݺ� ���
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