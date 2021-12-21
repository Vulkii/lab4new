#pragma once
#ifndef __SCORE_H_INCLUDED__
#define __SCORE_H_INCLUDED__
#include "Entity.h"

/*!
\brief Illustrates the player's game score and balance
\warning kills doesn't add score
\todo add points  from kills enemy
*/
class Score:public Entity
{
public:
	Score();
	virtual void update(sf::Time);
	int  getGold()const;

	/*!
	\brief Draws the game account and balance*/
	void draw(sf::RenderWindow* window);
	bool setGold(int);
private:
	sf::Font font;
	sf::Text textGold;
	sf::Text textScore;
	int gold;
	int score;

};

#endif