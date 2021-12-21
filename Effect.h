#pragma once

#ifndef __EFFECT_H_INCLUDED__
#define __EFFECT_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include "EffectType.h"
class Enemy;

/*!
\brief Represents an effect descriptor

Enables processing of the effect timer and control of enemy parameters
*/
class Effect
{
public:
	Effect() = default;

	/*!
	\brief Initializes an effect class constructor
	\param [in] type - type of effect 
	\param [in] hp <- indicates the enemy parameter: hp 
	\param [in]	speed <- indicates the enemy parameter: speed (if effect type - frost, then copy speed)
	\param [in] incDamage <- indicates the enemy parameter: increase damage (additional damage coefficient)
	*/
	Effect(EffectType, float* hp, float* speed, float* incDamage);
	Effect(const Effect& c);
	const Effect& operator=(const Effect& c);


	/*!
	\brief The method of the class that handles the time tick

	Updates the effect timer and take damage enemy if effect type - poison
	\param [in] hp  - current hp of enemy
	*/
	void update(sf::Time, float*);

	/*!
	\brief Returns all real parameters of the enemy (for freezing and weakening )
	\param [in] speed <- indicates the enemy parameter: speed 
	\param [in] incDamage <- indicates the enemy parameter: increase damage (additional damage coefficient)
	*/
	void returnState(float*, float*);
	EffectType getType()const { return type; }
	void setTime(sf::Time newTime);
	bool checkTime();
private:
	EffectType type;
	int quantity;
	sf::Time time;
	const sf::Time TIME_MAX = sf::seconds(2.f);
	float real_speed;
	sf::Time coldown;
};

#endif