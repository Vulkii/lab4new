#pragma once
#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tinyxml/tinyxml.h"
#include "State.h"
#include "Grid.h"
#include <list>
#include <map>
class GameState;

/*!
\brief Auxiliary structure that represents an associative array of map roads
*/
struct RoadObjects 
{
	std::map<std::string,std::list <sf::Vector2i>> roads;
};

/*!
\brief It is a landscape descriptor

Contains a logical grid of tiles. Required for loading data into the grid.
\warning Checks do not provide full verification of the card. There may be breakdowns due to the continuity of the road
\warning The size is 10 by 10 tiles, but this can be changed, Tiles must be 64 by 64 pixels
*/
class Level//главный класс - уровень
{
public:
	Level();
	Level(std::string filename);

	/*!
	\brief The main function of the class that implements loading a map from a file

	Need to download and parse the xml of the map.
	\warning Possibility of crash due to inaccuracy of the map
	*/
	bool LoadFromFile(std::string filename);//возвращает false если не получилось загрузить
	void DrawGrid(sf::RenderWindow& window);//риусем объекты
	sf::Vector2i GetTileSize();//получаем размер тайла
	bool setObject(sf::Vector2i Position, int );
	const Grid& getGrid()const { return logicalGrid;}
	std::map<std::string, std::list <sf::Vector2i>>* getRoad(){ return &roadList.roads; }
	bool getErrors()const { return constructError; }
private:
	bool constructError;

	/*!
	\brief General function of checking the card for logical

	Contain checkEntityErrors() and checkCorrectRoadEnd()
	\return constructError - Class instance-fixes an error(bool)
	*/
	bool countinuityRoad();

	/*!
	\brief Checks the relationship between road objects and road tiles
	\return constructError - Class instance-fixes an error(bool)
	*/
	bool checkEntityErrors();

	/*!
	\brief Checks the ends of road objects
	\return constructError - Class instance-fixes an error (bool)
	*/
	bool checkCorrectRoadEnd(sf::Sprite*, sf::Sprite* , std::list <sf::Vector2i>*);

	int findRoadID(int ID)const;
	int findCastleID(int ID)const;
	int findLierID(int ID)const;
	int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
	int firstTileID;//получаем айди первого тайла
	sf::Rect<float> drawingBounds;//размер части карты которую рисуем
	RoadObjects roadList;
	sf::Texture tilesetImage;//текстура карты
	Grid logicalGrid;
	Objects obj;
};
	
const int roadID[]
{
	153,154,155,156,
	176,177,178,179,
	199,200,201,202,
	222,223,224,225
};
const int N = sizeof(roadID) / sizeof(roadID[0]);

const int castleID[]
{
	40,44,63,67,
	86,90,109,113
};
const int Nl = sizeof(roadID) / sizeof(roadID[0]);

const int lierID[]
{
	41,64,87,110,
	45,68,91,114
};
const int Nc = sizeof(roadID) / sizeof(roadID[0]);

#endif