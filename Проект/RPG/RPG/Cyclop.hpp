#ifndef CYCLOP_H
#define CYCLOP_H

#include "source\Player.hpp"

using namespace std;

class Cyclop : public PLAYER
{
public:

	map<string, bool> key;

	Cyclop(AnimationManager &a, Level &lev, int x, int y) :PLAYER(a, lev, x, y)
	{
		shoot_cd = 1;
		damage = 100;
		hpRegen = 0;
		maxHealth = Health = 120;
	}

	virtual void upStats() {
		//shoot_cd = shoot*0.9;
		damage = damage*1.2;
		hpRegen += 0.25;
		maxHealth = maxHealth*1.11;
		Health = Health*1.11;
	}

};

#endif CYCLOP_H
