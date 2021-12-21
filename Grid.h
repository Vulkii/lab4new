/**
 * Project TD_daigram_classes
 */
#ifndef _GRID_H
#define _GRID_H

#include "Tile.h"
#include <SFML/Graphics.hpp>

 /*!
 \brief Structure required for temporary storage of changing all objects on the map */
struct Objects {
	std::vector<sf::Sprite> roads;
	std::vector<sf::Sprite> castles;
	std::vector<sf::Sprite> liers;
};

/*!
\brief Structure required for the temporary storage of all tiles of a layer
*/
struct Layer//слои
{
	int opacity;//непрозрачность слоя
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

/*!
\brief A class that describes interaction with map tiles
*/
class Grid {
public:

	Grid();

	const Tile* getTile(int i, int  j)const;

	void draw(sf::RenderWindow& window);

	const std::vector<std::vector<Tile>>& getTiles() const { return tileMap; }

	void setTiles(const std::vector<std::vector<Tile>> newMap)
	{
		tileMap = newMap;
	}

	int findObjects(Objects* obj, sf::Sprite tile);

	bool setTiles(std::vector<Layer> tmp, int, int, Objects*);

	/*!
\brief Method of the class required to change the tile state.

All States are described in the Type.h file
\param position - the vector describing the coordinates of the tile
\param type - type of change 2 -> add Trap, 1-> add tower , -1 - remove Tower, -2 ->remove trap
\return int 1 if succes and 0 if fail
\warning Tiles must be 64 by 64 pixels
*/
	int setStateObject(sf::Vector2i Position, int);

	void setTexture(sf::Texture);

	void setRectGrid(std::vector<sf::Rect<int>> rectG);

private:
	int _width;
	int _height;
	int tileWidth, tileHeight;
	std::vector<sf::Rect<int>> subRects;//Прямоугольная сетка по ID
	sf::Texture texture;
	std::vector<std::vector<Tile>> tileMap;

};

#endif //_GRID_H