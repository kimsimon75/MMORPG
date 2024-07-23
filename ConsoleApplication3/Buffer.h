#pragma once
#include <Windows.h>

#define BUFFERWIDTH 105
#define BUFFERHEIGHT 40

extern void* hBuffer[2];

extern bool screenIndex;

void InitBuffer();

void FlipBuffer();

void ClearBuffer();

void WriteBuffer(const COORD& pos, int color, const char* format);


void ReleaseBuffer();


