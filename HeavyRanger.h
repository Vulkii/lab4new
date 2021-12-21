#pragma once
#ifndef __HEAVYRANGER_H_INCLUDED__
#define __HEAVYRANGER_H_INCLUDED__
#include "Enemy.h"
/*!
\brief It is a subtype of the enemy class-a fast and heavily armed soldier in uniform
\bug default perameters
\todo fix defualt parameters and fix balance of game
*/
class HeavyRanger:public Enemy
{
public:
	HeavyRanger(std::list<sf::Vector2i>);
	void draw(sf::RenderWindow* window);
private:
	sf::Texture texture;
};

#endif
