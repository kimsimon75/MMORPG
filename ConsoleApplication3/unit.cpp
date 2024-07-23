#define _CRT_SECURE_NO_WARNINGS
#include "unit.h"

 Unit::Unit(int hp, int mp, int attack, int intelligence, int agility, int armor, int restore)
{
	this->max_hp = hp;
	current_hp = hp;
	basic_hp = hp;;
	this->max_mp = mp;
	current_mp = mp;
	basic_mp = mp;
	this->attack = attack;
	basic_damage = attack;
	this->intelligence = intelligence;
	basic_intelligence = intelligence;
	this->agility = agility;
	basic_agility = agility;
	this->armor = armor;
	basic_armor = armor;
	this->restore = restore;
	basic_restore = restore;

	pre_hp = hp;
	barrier = 0;
}

 int& Unit::ReturnHP()
{
	return current_hp;
}

 int& Unit::ReturnMP()
{
	return current_mp;
}

 int& Unit::SetAlertCount()
{
	return alertCount;
}

 void Unit::RemoveBarrier(Unit& target, int damage)
 {
	 target.barrier -= damage;
	 if (target.barrier < 0)
	 {
		 target.current_hp += target.barrier;
		 target.barrier = 0;
	 }
 }

 bool Unit::GetDamage(bool test,const char* item,Unit* target)
{
	if (current_hp < pre_hp)
	{
		
		if (test == true)
		{
			if(item!=nullptr)
			{
				for (int i = 0; i < 6; i++)
					if (item[i] == 4)
						target->current_hp -= (pre_hp - current_hp) * 0.5;
			}
			pre_hp = current_hp;
		}
		return true;
	}
	else
		return false;
}

 int& Unit::StunTime()
{
	return stun;
}

 void Unit::Restoring()
{
	current_hp += restore;
	if (current_hp > max_hp)
		current_hp = max_hp;
	pre_hp = current_hp;
}

 void Unit::ManaCharge()
{
	current_mp += (intelligence + max_mp) / 10;
	if (current_mp > max_mp)
		current_mp = max_mp;
}

 void Unit::GetPoison()
{
	barrier -= poison_damage;
	if (barrier < 0)
	{
		current_hp += barrier;
		barrier = 0;
	}
	--poison_time;
}

 int Unit::PoisonTime()
{
	return poison_time;
}

 void Unit::GetIgnite()
{
	barrier -= ignite_damage;
	if (barrier < 0)
	{
		current_hp += barrier;
		barrier = 0;
	}
	--ignite_time;
}

 int Unit::IgniteTime()
{
	return ignite_time;
}

 void Unit::DamageUp()
{
	attack += basic_damage;
}

 bool& Unit::TurnReturn()
{
	return turn;
}

 int& Unit::iced_time()
{
	return iced;
}

 int& Unit::BarrierCool()
{
	return barrierCool;
}

 int& Unit::BarrierSize()
{
	return barrier;
}

 int& Unit::IntelCool()
{
	return intelUpCool;
}


 int& Unit::GetIntelligence()
{
	return intelligence;
}

 pair<const char*, int> Unit::GetElement(int number)
{
	if (number == 0)
		return make_pair("체력", max_hp);
	else if (number == 1)
		return make_pair("마나", max_mp);
	else if (number == 2)
		return make_pair("공격력", attack);
	else if (number == 3)
		return make_pair("지능", intelligence);
	else if (number == 4)
		return make_pair("민첩성", agility);
	else if (number == 5)
		return make_pair("방어도", armor);
	else
		return make_pair("체력재생", restore);
}

 bool Unit::Sustained_DPS()
{
	if (ignite_time || poison_time)
		return true;
	return false;
}

 int& Unit::AP()
{
	return attackPoint;
}

 void Unit::APCharge()
{
	attackPoint += 10 + (int)(agility * 0.05);
}

 bool& Unit::WTF()
{
	return wtf;
}

 pair<bool, int> Unit::PoisonAttack(Unit& target)
{
	target.poison_time = 2;
	target.poison_damage = (10 + (float)intelligence * 0.1) * (1 + (float)agility * 0.07);

	return make_pair(1, 30);
}

 pair<bool, int> Unit::basic_Attack(Unit& target)
{

	int damage = attack - target.armor;
	if (damage < 0)
		damage = 0;
	RemoveBarrier(target, damage);
	return make_pair(0, 0);
}

 pair<bool, int> Unit::Rush(Unit& target)
{
	if (alertCount == 0)
		return make_pair(0, 0);
	else if (alertCount == -1)
	{
		int damage = atoi(CalculateEx(skillCoefficient[0][1]+2)) - target.armor;
		if (damage < 0)
			damage = 0;
		RemoveBarrier(target, damage);
		stun = 2;
	}
}

 pair<bool, int> Unit::fireball(Unit& target)
{
	int mana = 20;

	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		int damage = atoi(CalculateEx(skillCoefficient[1][0]+2));
		if (damage < 0)
			damage = 0;
		RemoveBarrier(target, damage);
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::ignite(Unit& target)
{


	target.ignite_time = atoi(CalculateEx(skillCoefficient[1][1] + 2));
	target.ignite_damage = 30;
	return make_pair(0, 0);
}

 pair<bool, int> Unit::IceMagic(Unit& target)
{
	int mana = 50;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		target.iced = 2;
		current_mp -= mana;
	}
	return make_pair(1, mana);

}

 pair<bool, int> Unit::PutOnBarrier(Unit& target)
{
	int mana = 20;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		barrier = atoi(CalculateEx(skillCoefficient[1][3] + 2));
		barrierCool = 5;
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::RaiseIntel(Unit& target)
{
	int mana = 20;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		intelUpCool = 5;
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::Dart(Unit& target)
{
	int mana = 30;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		int damage = atoi(CalculateEx(skillCoefficient[2][2] + 2)) - armor;
		if (damage < 0)
			damage = 0;
		RemoveBarrier(target, damage);
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::DamageAbsorb(Unit& target)
{
	int mana = 20;
	int atk = 15;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
		if (target.attack <= 0)
			alertCount = 4;
		else if (target.attack <= atk)
		{
			absorbDamage += target.attack;
			target.attack = 0;
			current_mp -= mana;
		}
		else
		{
			absorbDamage += atk;
			target.attack -= atk;
			current_mp -= mana;
		}
	return make_pair(1, mana);

}

 pair<bool, int> Unit::IntelligenceAbsorb(Unit& target)
{
	int mana = 20;
	int intel = 20;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		if (target.intelligence <= 0)
			alertCount = 5;
		else if (target.intelligence <= intel)
		{
			absorbIntelligence += target.intelligence;
			target.intelligence = 0;
			current_mp -= mana;
		}
		else
		{
			absorbIntelligence += intel;
			target.intelligence -= intel;
			current_mp -= mana;
		}
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::PowerOfGod(Unit& target)
{
	int mana = 150;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		int damage = atoi(CalculateEx(skillCoefficient[3][1] + 2)) - target.armor;
		if (damage < 0)
			damage = 0;
		RemoveBarrier(target, damage);
		current_mp -= mana;
	}
	return make_pair(1, mana);
}

 pair<bool, int> Unit::Heal(Unit& target)
{
	int mana = 50;
	if (alertCount == 0)
		return make_pair(1, mana);
	else if (alertCount == -1)
	{
		current_hp += atoi(CalculateEx(skillCoefficient[3][2] + 2));
		if (current_hp > max_hp)
			current_hp = max_hp;
		pre_hp = current_hp;
		current_mp -= mana;
	}
	return make_pair(1, mana);
}
