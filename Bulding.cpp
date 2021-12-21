#include "Bulding.h"
void Bulding::setTile(const Tile* tile)
{
	_tile = *tile;
}
Bulding::Bulding(const Tile* tile)
{
	_tile.setSprite( tile->getSprite());
}
const Tile* Bulding::getTile()
{
	return &this->_tile;
}
Bulding::Bulding()
{

}