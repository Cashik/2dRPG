#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "source\Player.hpp"

using namespace std;

class Megaman : public PLAYER
{
public:

	map<string, bool> key;

	Megaman(AnimationManager &a, Level &lev, int x, int y) :PLAYER(a, lev, x, y)
	{
		shoot_cd = 0.4;
		damage = 20;
		hpRegen = 1;
		maxHealth = Health = 100;
	}

	virtual void upStats() {
		shoot_cd = shoot_cd*0.9;
		damage = damage*1.1;
		hpRegen += 0.5;
		maxHealth = maxHealth*1.1;
		Health = Health*1.1;
	}

};

#endif MEGAMAN_H
