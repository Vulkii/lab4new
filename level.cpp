#include "level.h"
#include "GameState.h"
#include <map>
#include <cstdlib>
///////////////////////////////////////

Level::Level() :width(0), height(0), tileHeight(0), tileWidth(0), firstTileID(0), logicalGrid(), constructError(false)
{ }
Level::Level(std::string filename) : Level()
{
	this->LoadFromFile(filename);
	if (constructError)
	{
		exit(0);
	}
}
bool Level::LoadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса 
{
	std::vector<Layer> layers;
	TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument

	// загружаем XML-карту
	if (!levelFile.LoadFile())//если не удалось загрузить карту
	{
		std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
		constructError = true;
		return false;
	}

	// работаем с контейнером map
	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	// пример карты: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));

	// Берем описание тайлсета и идентификатор первого тайла
	TiXmlElement* tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	TiXmlElement* image;
	image = tilesetElement->FirstChildElement("image");
	std::string imagepath = image->Attribute("source");

	// пытаемся загрузить тайлсет
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
		constructError = true;
		return false;
	}


	img.createMaskFromColor(sf::Color(255, 255, 255));//для маски цвета.сейчас нет маски
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//сглаживание

	// получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	// вектор из прямоугольников изображений (TextureRect)
	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	this->logicalGrid.setRectGrid(subRects);
	// работа со слоями
	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");

	while (layerElement)
	{
		Layer layer;

		// если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		//  контейнер <data> 
		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
			constructError = true;
		}

		//  контейнер <tile> - описание тайлов каждого слоя
		TiXmlElement* tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");

		if (tileElement == NULL)
		{
			std::cout << "Bad map. No tile information found." << std::endl;
			constructError = true;
			return false;
		}

		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;
			//Ищем ID объектов
			int roadIDentifcation = findRoadID(subRectToUse), lierIDentifcation = -1, castleIDentifcation = -1;
			if (roadIDentifcation < 0)
			{
				lierIDentifcation = findLierID(subRectToUse);
				if (lierIDentifcation < 0)
				{
					castleIDentifcation = findCastleID(subRectToUse);
				}
			}
			// Устанавливаем TextureRect каждого тайла
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				if (roadIDentifcation > 0)
					obj.roads.push_back(sprite);
				if (lierIDentifcation > 0)
					obj.liers.push_back(sprite);
				if (castleIDentifcation > 0)
					obj.castles.push_back(sprite);

				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
			}
			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}

		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	// работа с объектами
	TiXmlElement* objectGroupElement;
	// если есть слои объектов
	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			//  контейнер <object>
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");
			while (objectElement)
			{
				// получаем все данные - тип, имя, позиция, и тд
				std::string objectName;
				int id = atoi(objectElement->Attribute("id"));
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				if (roadList.roads.find(objectName) == roadList.roads.end())
				{
					std::list<sf::Vector2i> ad;
					roadList.roads[objectName] = ad;
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}

				// экземпляр объект
				//hanlde object of road
				sf::Vector2i point;
				point.x = x;
				point.y = y;
				//	if (obj->liers[0].getPosition() == point)
				std::map < std::string, std::list<sf::Vector2i> > ::iterator it;
				it = roadList.roads.find(objectName);
				(*it).second.push_back(point);
				//убедиться , что координаты мышки высчитываются так же))
				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No ojecr layers found..." << std::endl;
	}
	if (obj.liers.size() < 1 || obj.castles.size() < 1)
	{
		std::cout << " You have incorrect map(quantity of castles or liers<1)" << std::endl;
		constructError = true;
		return false;
	}

	//Check correct  Roads!
	this->constructError = countinuityRoad();
	if (constructError)
		return false;

	logicalGrid.setTexture(this->tilesetImage);
	logicalGrid.setTiles(layers, width, height, &obj);

	return true;
}

sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}
void Level::DrawGrid(sf::RenderWindow& window)//риусем объекты
{
	logicalGrid.draw(window);
}
int Level::findRoadID(int ID)const
{
	for (int i = 0; i < N; ++i)
		if (ID == roadID[i])
			return ID;
	return -1;
}
int Level::findCastleID(int ID)const
{
	for (int i = 0; i < Nc; ++i)
		if (ID == castleID[i])
			return ID;
	return -1;
}
int Level::findLierID(int ID)const
{
	for (int i = 0; i < Nl; ++i)
		if (ID == lierID[i])
			return ID;
	return -1;
}

bool Level::setObject(sf::Vector2i Position, int type)
{
	this->logicalGrid.setStateObject(Position, type);
	return true;
}

bool Level::countinuityRoad()
{
	if (this->roadList.roads.empty())
	{
		std::cout << " You have not any roads" << std::endl;
		return true;
	}
	bool  er_entity;
	er_entity = checkEntityErrors();
	if (er_entity)
	{
		std::cout << "Tile of Catsle or Lier doesn't coincides with check Points" << std::endl;
		return true;
	}
	//auto it_roads = obj.roads.begin();
	int size_r = obj.roads.size();
	int summary = 0;
	for (auto road : obj.roads)
	{
		for (int k = 1; k <= roadList.roads.size(); k++)
		{
			std::string key = "solid" + std::to_string(k);
			std::map<std::string, std::list <sf::Vector2i>>::iterator it_m = roadList.roads.find(key);
			std::list <sf::Vector2i> tmp = (*it_m).second;
			std::list <sf::Vector2i>::iterator it = tmp.begin();
			if (tmp.size() < 2)
			{
				std::cout << "You need at least 2 checkpoints " << std::endl;
				return true;
			}
			auto it_next = ++it;
			it = tmp.begin();
			int old = summary;
			for (it_next; it_next != tmp.end(); ++it_next)
			{
				if ((((int)road.getPosition().x <= it_next->x)&&
					((int)road.getPosition().x >= it->x))||
					(((int)road.getPosition().y <= it_next->y) &&
					((int)road.getPosition().y >= it->y)))
				{
					summary++;
					break;
				}
			}
			if (old< summary)
			{
				break;
			}
		}
	}
	if (summary == size_r)
		return false;
	else
	{
		std::cout << "Road of object doesn't coincides with tile of road" << std::endl;
		return true;
	}
}
bool Level::checkEntityErrors()
{
	bool error = false;
	int size = obj.castles.size();
	int size_l = obj.liers.size();
	int counter = 0;
	for (int k = 1; k <= roadList.roads.size(); k++)
	{
		std::string key = "solid" + std::to_string(k);
		std::map<std::string, std::list <sf::Vector2i>>::iterator it_m = roadList.roads.find(key);
		std::list <sf::Vector2i> tmp = (*it_m).second;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size_l; j++)
			{
				bool flag;
				flag = checkCorrectRoadEnd(&obj.liers[j], &obj.castles[i],&tmp);
				if (flag)
					counter++;
			}
		}
	}
	if (counter != roadList.roads.size())
		error = true;
	return error;
}
bool Level::checkCorrectRoadEnd(sf::Sprite *lier, sf::Sprite* castle, std::list <sf::Vector2i>* checkPoints)
{
	auto it = checkPoints->begin();
	if (((*it).x == (int)lier->getPosition().x) && ((*it).y == (int)lier->getPosition().y))
	{
		for (int i = 0; i < checkPoints->size()-1; i++)
		{
			++it;
		}
		if (((*it).x == (int)castle->getPosition().x) && ((*it).y == (int)castle->getPosition().y))
			return true;
	}
	return false;
}