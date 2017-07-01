#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "level.hpp"
#include "Animation.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "MovingPlatform.hpp"
#include "HealthBar.hpp"
#include "Megaman.hpp"
#include "Cyclop.hpp"

using namespace sf;
using namespace std;

class Game {
public:

};


string RunGame(int heroNumber, int lvlNumber)
{
	///////////// инициализаци€ ///////////////////////////
	RenderWindow window(VideoMode(640, 320), "The Game!");

	View view(FloatRect(0, 0, 640, 320));

	Level lvl;
	lvl.LoadFromFile("files/Level" + to_string(lvlNumber) + ".tmx");

	Texture enemy_t, moveplatform_t, megaman_t, bullet_t, cyclop_t, bg;
	bg.loadFromFile("files/images/bg.png");
	enemy_t.loadFromFile("files/images/bigEnemy.png");
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
	megaman_t.loadFromFile("files/images/megaman.png");
	bullet_t.loadFromFile("files/images/bullet.png");
	cyclop_t.loadFromFile("files/images/cyclop.png");



	AnimationManager megamanAnim;
	megamanAnim.loadFromXML("files/anim_megaman.xml", megaman_t);
	megamanAnim.animList["jump"].loop = 0;

	AnimationManager cyclopAnim;
	cyclopAnim.loadFromXML("files/anim_cyclop.xml", cyclop_t);
	cyclopAnim.animList["jump"].loop = 0;

	AnimationManager bulletAnim, laserAnim;
	bulletAnim.create("move", bullet_t, 7, 10, 8, 8, 1, 0);
	bulletAnim.create("explode", bullet_t, 27, 7, 18, 18, 4, 0.01, 29, false);
	laserAnim.loadFromXML("files/laser.xml", cyclop_t);
	laserAnim.animList["explode"].loop = 0;




	AnimationManager anim3;
	anim3.loadFromXML("files/enemy.xml", enemy_t);
	anim3.animList["dead"].loop = 0;


	AnimationManager anim4;
	anim4.create("move", moveplatform_t, 0, 0, 95, 22, 1, 0);

	Sprite background(bg);
	background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);
	background.setScale(2, 2);

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	// считывание изначальных врагов
	std::vector<Object> e = lvl.GetObjects("enemy");
	int enemyCount = e.size();
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new ENEMY(anim3, lvl, e[i].rect.left, e[i].rect.top));

	e = lvl.GetObjects("MovingPlatform");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top));

	Object pl = lvl.GetObject("player");

	PLAYER * playerBuf;

	if (heroNumber == 1)
		playerBuf = new Megaman(megamanAnim, lvl, pl.rect.left, pl.rect.top);
	else
		playerBuf = new Cyclop(cyclopAnim, lvl, pl.rect.left, pl.rect.top);

	PLAYER & player = *playerBuf;


	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	Bar healthBar("files/images/HealthBar.jpg", Vector2f(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10));
	Bar expBar("files/images/ExpBar.jpg", Vector2f(center.x - size.x / 2 + 20, center.y - size.y / 2 + 10));


	Font font;
	font.loadFromFile("files/CyrilicOld.TTF");
	Text lvlLabel("Hero level:", font, 20);
	Text enemiesLabel("Enemies:", font, 20);
	// set the text style
	lvlLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);
	enemiesLabel.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Clock clock;

	/////////////////// основной цикл  /////////////////////
	while (window.isOpen() && player.life)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;  // здесь регулируем скорость игры

		if (time > 40) time = 40;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
					if (player.lastShootTime > player.shoot_cd) {
						if (heroNumber == 1) {
							entities.push_back(new Bullet(bulletAnim, lvl, player.x + 18, player.y + 18, player.dir));
						}
						else {
							entities.push_back(new Bullet(laserAnim, lvl, player.x + ((player.dir) ? (0) : (60)), player.y + 25, player.dir, 0.01, 0.5));
						}
						player.lastShootTime = 0;
					}
		}


		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) player.key["L"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) player.key["R"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) player.key["Up"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) player.key["Down"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Space)) player.key["Space"] = true;


		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false)
			{
				if (b->Name == "Enemy") {
					player.experience += 50;
					enemyCount--;
				}
				it = entities.erase(it);
				delete b;
			}
			else it++;
		}


		player.update(time);




		for (it = entities.begin(); it != entities.end(); it++)
		{
			//1. враги
			if ((*it)->Name == "Enemy")
			{
				Entity *enemy = *it;

				if (enemy->Health <= 0) continue;

				if (player.getRect().intersects(enemy->getRect()))
					if (player.dy > 0 && heroNumber == 2) {
						player.dy = -0.2;
						enemy->Health -= player.damage;
					}
					else if (!player.hit) {
						player.Health -= 33; player.hit = true;
						if (player.dir) player.x += 20;
						else player.x -= 20;
					}


					for (std::list<Entity*>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
					{
						Entity *bullet = *it2;
						if (bullet->Name == "Bullet")
							if (bullet->Health > 0)
								if (bullet->getRect().intersects(enemy->getRect()))
								{
									bullet->Health = 0;
									enemy->Health -= player.damage;
								}
					}
			}

			//2. движущиес€ платформы
			if ((*it)->Name == "MovingPlatform")
			{
				Entity *movPlat = *it;
				if (player.getRect().intersects(movPlat->getRect()))
					if (player.dy > 0)
						if (player.y + player.h < movPlat->y + movPlat->h)
						{
							player.y = movPlat->y - player.h + 3; player.x += movPlat->dx*time; player.dy = 0; player.STATE = PLAYER::stay;
						}
			}

			//3.. и т.д.
		}


		/////////////////////отображаем на экран/////////////////////
		view.setCenter(player.x, player.y);
		window.setView(view);

		background.setPosition(view.getCenter());
		window.draw(background);

		lvl.Draw(window);

		for (it = entities.begin(); it != entities.end(); it++)
			(*it)->draw(window);

		player.draw(window);
		center = view.getCenter();
		size = view.getSize();
		healthBar.update((player.Health / player.maxHealth),
			Vector2f(center.x - size.x / 2, center.y - size.y / 2));
		expBar.update((player.experience / float(player.experienceToNextLevel)),
			Vector2f(center.x - size.x / 2 + 20, center.y - size.y / 2));
		healthBar.draw(window);
		expBar.draw(window);
		lvlLabel.setString("Hero level:" + to_string(player.level));
		lvlLabel.setPosition(center.x + size.x / 2 - 150,
			center.y - size.y / 2 + 20);
		window.draw(lvlLabel);

		enemiesLabel.setString("Enemies:" + to_string(enemyCount));
		enemiesLabel.setPosition(center.x + size.x / 2 - 150,
			center.y - size.y / 2 + 50);
		window.draw(enemiesLabel);

		window.display();

		if (enemyCount==0)
			return "ѕоздравл€ю, вы прошли игру!";

		if (!player.life) 
			return "¬ас убили!";
	}

	
	return "¬ы не закончили игру!";

}

#endif GAME_H

