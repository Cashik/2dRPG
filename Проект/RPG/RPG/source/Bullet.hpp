#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"


class Bullet :public Entity
{
public:
	float lifeTime;

	Bullet(AnimationManager &a, Level &lev, int x, int y, bool dir, float speed=0.3, float _lifeTime=60) :Entity(a, x, y)
	{
		option("Bullet", speed, 10, "move");
		lifeTime = _lifeTime;
		if (dir) dx = -speed;
		obj = lev.GetObjects("solid");
	}

	void update(float time)
	{
		x += dx*time;
		lifeTime -= time/1000.;

		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				Health = 0;
			}

		if (Health <= 0 || lifeTime<0) {
			anim.set("explode"); 
			dx = 0;
			if (anim.isPlaying() == false) 
				life = false;
		}


		if (dx < 0) {
			anim.flip(1);
		}
		else
		{
			anim.flip(0);
		}
		anim.tick(time);
	}

};

#endif BULLET_H
