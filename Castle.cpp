#pragma warning(disable : 4996)
#include "Castle.h"
#include <iostream>

Castle::Castle(const Tile* tile):HP_MAX (1000), hp (1000), Bulding(tile)
{
	
}
void Castle::draw(sf::RenderWindow* window)
{
	if (!font.loadFromFile("data/CyrilicOld.ttf"))
	{
		std::cout << "Error of downdload FONT of the text" << std::endl;
	}
	textCastle.setFont(font);
	textCastle.setCharacterSize(24);
	//textCastle.setColor(Color::Red);
	sf::Vector2f pos;
	pos = this->getTile()->getSprite().getPosition();
	pos.x -= 10;
	pos.y -= 10;
	textCastle.setPosition((int)pos.x, (int)pos.y);
	std::string strCastle =  std::to_string((int)this->hp) + "/" + std::to_string(this->HP_MAX);
	textCastle.setString(strCastle);
	
	window->draw(textCastle);
}
void Castle::update(sf::Time)
{
	;
}