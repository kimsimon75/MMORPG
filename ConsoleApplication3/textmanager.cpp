#include "textmanager.h"

TextManager* TextManager::p = nullptr;

void TextManager::SetRenderer(TEXTID id) {
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
	case INGAME:
		text = new InGame;
		break;
	case ITEM:
		text = new Item;
		break;
	case WEAPON:
		text = new Weapon;
		break;
	}
}

void TextManager::Update()
{
	text->Render();
}
