#pragma once
#ifndef __CASTLE_H_INCLUDED__
#define __CASTLE_H_INCLUDED__
#include "Bulding.h"

/*!
\brief It is castle descriptor
*/
class Castle : public Bulding
{
public:
	Castle(const Tile *tile);


	virtual void update(sf::Time);//!Empty function

	/*!
	\brief Output information about the hp lock status
	\bug It may break due to frequent font loading
	\warning It may break due to frequent font loading
	\todo fix font
	*/
	void draw(sf::RenderWindow* window);
	bool takeDamage(float damage)
	{
		hp -= damage;
		if (hp <= 0)
		{
			hp = 0;
			return true;
		}
		return false;
	}
	float gethp()const { return hp; }
private:
	sf::Font font;
	sf::Text textCastle;
	float hp;
	const int HP_MAX;

};
#endif
