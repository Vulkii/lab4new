#pragma once
#ifndef __ENEMYWAVE_H_INCLUDED__
#define __ENEMYWAVE_H_INCLUDED__
#include "Enemy.h"

/*!
\brief Class describing the enemy wave controller

Able to generate a wave and when hp of enemy = 0 - remove the enemy.
*/
class EnemyWave :public Entity
{
public:
	EnemyWave(std::list <sf::Vector2i>,int);//Create wave
	void draw(sf::RenderWindow* window);
	/*!
	\brief A virtual overloaded method of the class that handles the time tick

	Sends each enemy a time tick and records the hp status of each enemy in the wave
	*/
	virtual void update(sf::Time);//update all of enemy in wave
	std::vector<Enemy*> getEnemies()const;

	//! remove Enemy from vector
	bool removeEnemy(Enemy*);
private:
	int curr; ///< Counter of "live" enemies
	const sf::Time cooldown = sf::seconds(3.f);
	sf::Time elapsedTime;
	std::vector<Enemy*> wave;
};

#endif