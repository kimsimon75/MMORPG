#include "Buffer.h"

void* hBuffer[2] = {nullptr, nullptr};

bool screenIndex = 0;

void InitBuffer()
{
	//현재 스크린 index값은 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : 화면크기
	//COORD size;
	//size.X = BufferWidth;
	//size.Y = BufferHeight;
	COORD size = { BUFFERWIDTH, BUFFERHEIGHT };

	//창 크기 왼쪽 : 0, 위쪽 : 0, 오른쪽 : 80 -1, 아래쪽 : 40 - 1
	SMALL_RECT rect = { 0, 0, BUFFERWIDTH - 1, BUFFERHEIGHT - 1 };

	//0번 버퍼 만들기
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0번 화면 버퍼 사이즈 설정(버퍼주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0번 창 사이즈 설정 
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1번 버퍼 만들기
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1번 화면 버퍼 사이즈 설정(버퍼주소, 크기)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1번 창 사이즈 설정 
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	//커서 정보 등록 : 깜박이는 커서 안보이게
	CONSOLE_CURSOR_INFO info;	//콘솔 커서 정보 구조체
	info.dwSize = 1;			//커서 크기
	info.bVisible = FALSE;		//커서 안보이게

	//0 & 1 각각의 버퍼에 커서 정보 등록
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

void FlipBuffer()
{
	//해당 버퍼 활성화
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0] -> [1] / [1] -> [0]
	screenIndex = !screenIndex;
}

void ClearBuffer()
{
	//시작 위치
	//pos.x = 0, pos.y = 0
	COORD pos = { 0,0 };
	//매개변수 채울려고
	DWORD dw;

	//화면을 ' '로 채움
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BUFFERWIDTH * BUFFERHEIGHT, pos, &dw);
}

void WriteBuffer(const COORD& const pos, int color, const char* format)
{
	//위치 설정
	//pos.X = x * 2, pos.Y = y;
	//커서 위치 이동
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	//색깔 바꿔주고
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//매개변수 채우기 위해
	DWORD dw;

	//해당 버퍼에 쓰기
	WriteFile(hBuffer[screenIndex], format, strlen(format), &dw, NULL);

}

void ReleaseBuffer()
{
	//버퍼 해제
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
