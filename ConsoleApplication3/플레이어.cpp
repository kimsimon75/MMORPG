#include "플레이어.h"
#include "적.h"

class Enemy;

void Player::basic_Attack(Unit& target)
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
}
