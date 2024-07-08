#pragma once
#include "enemy.h"
#include "unit.h"

int Enemy::ReturnMaxMP()
{
	return max_mp;
}

void Enemy::Special_Attack(Unit& target, int gameRound)
{
	if (gameRound == 0)
		PoisonAttack(target);
}