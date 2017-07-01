#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

using namespace std;

class Bar
{
public:
	Texture t;
	Sprite s;
	int max;
	Vector2f pos;
	RectangleShape bar;

	Bar(string texture, Vector2f pos = Vector2f(0,0))
	{
		t.loadFromFile(texture);
		s.setTexture(t);

		this->pos = pos;

		bar.setFillColor(Color(0,0,0));
		max = 100;
	}

	void update(float p, Vector2f pos = Vector2f(0, 0))
	{
		this->pos = pos;
		if (p>=0 && p<=1) 
			bar.setSize( Vector2f(10, 65*(1-p)) );
	}

   	void draw(RenderWindow &window)
	{
		s.setPosition(pos.x + 10, pos.y + 10);
		bar.setPosition(pos.x + 11, pos.y + 13);

		window.draw(s);
		window.draw(bar);
	}

};

#endif HEALTHBAR_H
