#pragma once
#include "Enemy.h"
#ifndef __HEAVYINFANTRY_H_INCLUDED__
#define __HEAVYINFANTRY_H_INCLUDED__
/*!
\brief It is a subtype of the enemy class-a slow but heavily armed soldier in uniform
\bug default perameters
\todo fix defualt parameters and fix balance of game
*/
class HeavyInfantry :public Enemy
{

public:
	HeavyInfantry(std::list<sf::Vector2i>);
	void draw(sf::RenderWindow* window);
private:
	sf::Texture texture;
};
#endif

