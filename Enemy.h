#pragma once

#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "Effect.h"
#include "Entity.h"
#include <list>
#include "List.h"
class EnemyWave;


///The set of possible States of the enemy
enum EnemyType
{
	Light_Infantry = 1,///< default easy enemy
	Heavy_Infantry,///< heavy soldier , but slow
	Heavy_Ranhger ///< heavy soldier and FAST
};


/*!
\brief Is the specifier of the enemy

Contains a mountain of functions for interacting with class parameters, 
including attributes such as |Speed| , |hp| , |Money| and other. Also functions for interacting with the effects table
*/
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(std::list <sf::Vector2i>, EnemyType);
	void setEnemyWave(EnemyWave* wave);

	//Work with effects

	/*!
	\brief Method of the class intended for processing effects in void update()

	Checks the time of all effects and adds the time to the counter for all effects.
	\param [in] dt - time tick
	\return 0 if table of effects - empty and 1 if else
	\warning method can kill enemy and don't give money player
	*/
	int controlEffects(sf::Time);
	bool addEffect(EffectType);

	/*!
	\brief A method that searches for identical effects and updates the effect


	This method is designed to eliminate the collision of 2
	identical effects. if the same type of effect is found, the timer will simply update
	\param [in] type - EffectType - type effect, which enemy get from traps or tower
	\return 0 if table of effects - empty and 1 if else
	\warning method can kill enemy and don't give money player
	*/
	int findEffect(EffectType);
	void updateEf(sf::Time);
	void removeEffects();

	void setSpeed(float ef_speed) { speed = ef_speed; }
	float getSpeed() { return speed; }
	void setIncreaseDamage(float tmp) { increaseDamage = tmp; }
	float getIncreaseDamage() { return increaseDamage; }

	//work with moving	
	void update(sf::Time);
	void setVisible(bool vis) { visible = vis; }
	bool getVisible()const { return visible; }
	const sf::Vector2f getPosition()const { return sprite.getPosition(); }
	
	//Interaction with tower
	EnemyType getName()const { return name; }
	float  gethp()const { return hp; }
	const std::list <sf::Vector2i>* getPointsList()const { return &checkPoints; }
	void setColor(sf::Color col) {
		sprite.setColor(col);
	}
	void setOrigin();
	void reSetOrigin();

	//main functions (work with hp)

	/*!
	\brief The method is designed to destroy itself due to lack of hp

	If you remove this feature, the enemy will die in a loop, after dying from the effect, which is not good
	\warning method can kill enemy and don't give money player
	*/
	void selfdestruction();

	/*!
	\brief Method of the class that is intended for dealing damage and adding an effect to the table

	Checks the time of all effects and adds the time to the counter for all effects.
	\param [in] damage - Obviously the damage the poor guy will take
	\param [in] type - EffectType - type effect, which enemy get from traps or tower
	\return true if enemy is dead and false if else
	*/
	bool takeDamage(float damage, EffectType type);
	int getGold()const { return money; }
	void setHP(float ef_hp) { hp = ef_hp; }
	
protected:

	int points;
	bool visible;
	float speed;
	float hp;
	const int HP_MAX;
	float increaseDamage;
	best_list::List<Effect> effects;
	int money;
	sf::Sprite sprite;
	sf::RectangleShape rectHealthbar;
	std::list <sf::Vector2i> checkPoints;
	EnemyType name;
	sf::Texture healthbar;
	EnemyWave* _wave;
};

#endif

