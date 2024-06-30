 //키보드 입력
#pragma comment (lib, "winmm.lib")    //음악
#include <mmsystem.h>;                //음악
#include <Digitalv.h>;                //음악

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openShuffleSound;
MCI_PLAY_PARMS playShuffleSound;
#define BGM L"소리\\배달의민족 - 미래도시라솔파.mp3"    //BGM 경로 지정
#define SHUFFLE L"소리\\slash-21834.mp3"
#define BARK L"소리\\bark.mp3"//효과음 경로 지정
int dwID;

void playingBgm(void) {
    openBgm.lpstrElementName = BGM;            //파일 오픈
    openBgm.lpstrDeviceType = L"mpegvideo";    //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(LPVOID)&openBgm);    //음악 반복 재생
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