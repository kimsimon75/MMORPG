#pragma once
#include "render.h"
class TextManager
{
private:
	static TextManager* p;
public:
	static TextManager* Get()
	{
		if (p == nullptr)
		{
			p = new TextManager;
		}
		return p;
	}
private:
	Text* text = nullptr;
public:
	void SetRenderer(TEXTID id);

	void Update();
};
