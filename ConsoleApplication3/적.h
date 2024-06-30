#ifndef _UNIT_
#define _UNIT_
#include "РЏДж.h"
#endif
class Enemy : public Unit
{
private:
	friend class Player;
public:
	Enemy(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore) : Unit(hp, mp, attack, intelligence, agility, armor, restore) {

	}

	int ReturnMaxMP();
	
	void Special_Attack(Unit& target, int gameRound);





};

