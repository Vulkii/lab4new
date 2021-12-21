#include <iostream>
#include "Grid.h"
class Tile;
/**
 * Grid implementation
 */
Grid::Grid() :_height(10), _width(10), tileHeight(64), tileWidth(64)
{
}
bool Grid::setTiles(std::vector<Layer> tmp, int width, int height, Objects* obj)
{
	_width = width;
	_height = height;
	try {
		int n = 0;
		for (int i = 0; i < height; ++i)
		{
			std::vector<Tile> newTileList;
			for (int j = 0; j < width; j++)
			{
				sf::Sprite newTile(tmp[0].tiles[n]);
				Tile tile;
				tile.setTileNumber(n);
				tile.setState(findObjects(obj, tmp[0].tiles[n]));
				tile.setSprite(newTile);
				newTileList.push_back(tile);
				++n;
			}
			tileMap.push_back(newTileList);
		}
	}
	catch (...)
	{
		std::cout << "We have some trabl on setTiles";
		return false;
	}
	return true;
}
const Tile* Grid::getTile(int i, int j)const
{
	return &tileMap[i][j];
}

void Grid::draw(sf::RenderWindow& window) {
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			window.draw(tileMap[i][j].getSprite());
		}
	}
}

int Grid::findObjects(Objects* obj, sf::Sprite tile)
{
	int size = obj->roads.size();
	for (int i = 0; i < size; i++)
	{
		if (obj->roads[i].getPosition() == tile.getPosition())
			return 1;
	}
	size = obj->castles.size();
	for (int i = 0; i < size; i++)
	{
		if (obj->castles[i].getPosition() == tile.getPosition())
			return 2;
	}
	size = obj->liers.size();
	for (int i = 0; i < size; i++)
	{
		if (obj->liers[i].getPosition() == tile.getPosition())
			return 3;
	}
	return 0;
}
int Grid::setStateObject(sf::Vector2i Position, int type)
{
	try {
		int x = Position.x / tileWidth, y = Position.y / tileHeight;
		if (type == 2)
		{
			//add trap
			tileMap[y][x].setState(5);
		}
		if (type == 1)
		{
			//add tower
			tileMap[y][x].setState(4);
		}
		if(type == -1)
		{
			//remove tower, do state - forest
			tileMap[y][x].setState(0);
		}
		if (type == -2)
		{
			//remove trap, do state - road
			tileMap[y][x].setState(1);
		}
		return 1;
	}
	catch (...)
	{
		std::cout << "Probably need set tileWeight and tile Height" << std::endl;
		return 0;
	}
}

void Grid::setTexture(sf::Texture t)
{
	texture = t;
}

void Grid::setRectGrid(std::vector<sf::Rect<int>> rectG)
{
	this->subRects = rectG;
}