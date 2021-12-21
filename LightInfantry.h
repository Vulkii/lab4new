#pragma once
#ifndef __LIGHTINFANTRY_H_INCLUDED__
#define __LIGHTINFANTRY_H_INCLUDED__
#include "Enemy.h"
/*!
\brief Represents a subtype of the enemy class - an ordinary man in uniform
\bug default perameters
\todo fix defualt parameters and fix balance of game
*/
class LightInfantry:public Enemy
{
public:
	LightInfantry(std::list<sf::Vector2i>);
	void draw(sf::RenderWindow* window);
private:
	sf::Texture texture;
};
#endif
