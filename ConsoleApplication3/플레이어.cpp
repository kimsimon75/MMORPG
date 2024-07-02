#pragma once
#include "�÷��̾�.h"
#include "��.h"

class Enemy;

pair<bool, int> Player::basic_Attack(Unit& target)
{
	if (playerNumber == 4)
	{
		int damage = intelligence * 0.1;
		target.current_hp -= damage;
		max_hp += damage;
		current_hp += damage;
	}
	else
	{
		int damage = attack - target.armor;
		if (damage < 0)
			damage = 0;
		target.current_hp -= (damage);
	}
	return make_pair(0, 0);
}
