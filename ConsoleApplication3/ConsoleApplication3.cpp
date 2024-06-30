
#ifndef _MAIN_
#define _MAIN_
#include "메인.h"
#endif
void Render()
{
	keyInput = 0;
	Map();
	Button();
	Play();
	if (state >= 1 && state < 3)
		Status();

	TextManager::Get()->Update();

	if (alertCount)
		Alert();
	if (skillOn)
		SkillInformation();

}



int main(){

	system("mode con: cols=104 lines=41");

	

	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	playingBgm();
	TextManager::Get()->SetRenderer(STORY);
	
	while(1)
	{
		while (!gameover)
		{
			if (keyInput)
			{
 				Render();
			}
			KeyValue();

		}
		Map();
		GameOver();
		ResetGame();
	}


	return 0;

}

