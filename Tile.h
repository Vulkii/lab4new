#pragma once

#ifndef __TILE_H_INCLUDED__
#define __TILE_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "Type.h"

/*!
\brief It is a class that describes a landscape element.

It is necessary to implement the logic of building towers and traps, and also contains the texture of the map square.
*/
class Tile {
public: 

    /*!
    \Method of the class that sets the state of the cell

    All cell States are described in the Type.h file
    */
void setState(int );

void setSprite(const sf::Sprite& tmp) { sprite = tmp; sprite.setPosition(tmp.getPosition()); }
void setTileNumber(int);
void setColor(sf::Color col) { sprite.setColor(col); }
const sf::Sprite getSprite()const;
int getState() const;
int getTileNumber() const;  
void setTexture(sf::Texture&, sf::IntRect);
void setTexture(sf::Texture& t) { sprite.setTexture(t); }
const sf::Sprite* getSpriteV();
void setOrigin(float, float);
void setRotation(float);
void setPositionToCenter();
void setPosition(sf::Vector2f);
private: 
    Type state;
    int tileNumber;
    sf::Sprite sprite;
    
};
#endif