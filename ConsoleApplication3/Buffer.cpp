#include "Buffer.h"

void* hBuffer[2] = {nullptr, nullptr};

bool screenIndex = 0;

void InitBuffer()
{
	//���� ��ũ�� index���� 0
	screenIndex = 0;

	//size.x = 80, size.y = 40 : ȭ��ũ��
	//COORD size;
	//size.X = BufferWidth;
	//size.Y = BufferHeight;
	COORD size = { BUFFERWIDTH, BUFFERHEIGHT };

	//â ũ�� ���� : 0, ���� : 0, ������ : 80 -1, �Ʒ��� : 40 - 1
	SMALL_RECT rect = { 0, 0, BUFFERWIDTH - 1, BUFFERHEIGHT - 1 };

	//0�� ���� �����
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//0�� ȭ�� ���� ������ ����(�����ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[0], size);
	//0�� â ������ ���� 
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	//1�� ���� �����
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//1�� ȭ�� ���� ������ ����(�����ּ�, ũ��)
	SetConsoleScreenBufferSize(hBuffer[1], size);
	//1�� â ������ ���� 
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	//Ŀ�� ���� ��� : �����̴� Ŀ�� �Ⱥ��̰�
	CONSOLE_CURSOR_INFO info;	//�ܼ� Ŀ�� ���� ����ü
	info.dwSize = 1;			//Ŀ�� ũ��
	info.bVisible = FALSE;		//Ŀ�� �Ⱥ��̰�

	//0 & 1 ������ ���ۿ� Ŀ�� ���� ���
	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

void FlipBuffer()
{
	//�ش� ���� Ȱ��ȭ
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);

	//[0] -> [1] / [1] -> [0]
	screenIndex = !screenIndex;
}

void ClearBuffer()
{
	//���� ��ġ
	//pos.x = 0, pos.y = 0
	COORD pos = { 0,0 };
	//�Ű����� ä�����
	DWORD dw;

	//ȭ���� ' '�� ä��
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BUFFERWIDTH * BUFFERHEIGHT, pos, &dw);
}

void WriteBuffer(const COORD& const pos, int color, const char* format)
{
	//��ġ ����
	//pos.X = x * 2, pos.Y = y;
	//Ŀ�� ��ġ �̵�
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	//���� �ٲ��ְ�
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	//�Ű����� ä��� ����
	DWORD dw;

	//�ش� ���ۿ� ����
	WriteFile(hBuffer[screenIndex], format, strlen(format), &dw, NULL);

}

void ReleaseBuffer()
{
	//���� ����
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
