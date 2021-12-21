#pragma once
#ifndef __TOWER_H_INCLUDED__
#define __TOWER_H_INCLUDED__
#include "Bulding.h"
#include "EffectType.h"
#include "Enemy.h"
enum TowerType;


//!Table of tower parameters
struct TableStateTower
{
	float range;
	float damage;
	float attackSpeed;
	EffectType type_ef;
	TableStateTower() : range(100), damage(50), attackSpeed(1.5) { ; }
	bool up();
	void setEffect(TowerType type_t);
};


/*!
\brief The class implements the descriptor of the tower.

Able to deal <Target> damage as well as an effect ( in the case of a magic tower ) 
Able to turn relative to the target,make a shot in accordance with its attack speed.
The player earns money from tower kills
\bug Some textures look crooked :C
*/
class Tower : public Bulding
{
public:


	Tower(const Tower&);
	Tower(const Tile* tile, TowerType);

	/*!
	\brief A virtual overloaded method of the class that handles the time tick

	\param frameTime -	time tick corresponding to 1/60 of a second
	The function implements the rotation and firing of the tower at the enemy, if the shot is successful,
	it adds money to the player. 
	As a result of the shot (or not) resets the target
	*/
	virtual void update(sf::Time);

	/*!
	\brief A class method that simply draws a tower (a sprite rotated by an angle)*/
	void draw(sf::RenderWindow* window);

	TowerType getTowerType()const { return type; }
	int getLevel()const { return level; }
	const Tower& operator=(const Tower&);
	void lvlUP();
	void setTarget(Enemy* tmp) 
	{
		target = tmp;
	}
	void removeColor() { target->setColor(sf::Color::White); }
	Enemy* getTarget()const { return target; }
	float  getRange()const { return  table.range; }


	/*!
	\brief Specifies the starting point of the sprite in the center*/
	void setOrigin();
	void setAngle(float angle);
	float getAngle()const { return angleOfRotation; }
	const TableStateTower& getTable() const { return table; }
private:
	sf::Time elapsedTime;
	float angleOfRotation;
	Enemy* target;
	void setTexture(int);
	TowerType type;
	int level;
	const int LEVEL_MAX = 2;
	TableStateTower table;
	std::vector<sf::Texture> texturpack;//contain texture level 1 and 2
};

#endif