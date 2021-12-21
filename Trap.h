#pragma once
#ifndef __TRAP_H_INCLUDED__
#define __TRAP_H_INCLUDED__
#include "Bulding.h"
#include "EffectType.h"

/*!
\brief This is the trap descriptor.

In fact, it's just a timer bomb, it explodes (in a certain radius (40 pixels)),
deals damage to all enemies, at the moment when it's time to detonate
\bug It doesn't detonated if it doesn't see enemies 
\todo fix bug in MoveSystem
\warning It doesn't detonated if it doesn't see enemies
*/
class Trap : public Bulding
{
public:
	Trap(const Tile* tile, EffectType type);
	Trap(const Trap& c);
	const Trap& operator=(const Trap& c);

	/*!
	\brief A virtual overloaded method of the class that handles the time tick

	Deals damage if it's a poison tower, and adds up the time ticks until it's time to detonate.
	\param dt - tick time <- see in Game description
	*/
	virtual void update(sf::Time);
	void draw(sf::RenderWindow* window);
	float  getDamage()const { return damage; }
	EffectType  getEffectType() const { return type; }
	float getRange()const { return range; }
	bool getMode()const { return explosion; }
	void  setMode(bool mode) { explosion = mode; }
	bool checkTime()const;
private:
	sf::Texture texture;
	EffectType type;
	sf::Time elapsedTime;
	bool explosion;
	const sf::Time timeDetonation = sf::seconds(1.f /2);
	float damage;
	float range;
};

#endif