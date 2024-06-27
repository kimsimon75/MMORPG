#pragma once
#include "·»´õ.h"
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
	void SetRenderer(TEXTID id) {
		if (text != nullptr)
		{
			delete text;
			text = nullptr;
		}
		switch (id)
		{
		case STORY:
			text = new Story;
			break;
		case PLAYERINFO:
			text = new PlayerInfo;
			break;
		case HOWTOPLAY:
			text = new HowToPlay;
			break;
		case ENEMY:
			text = new EnemyInfo;
			break;
		}
	}

	void Update()
	{
		text->Render();
	}
};

TextManager* TextManager::p = nullptr;