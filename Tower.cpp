#include "Tower.h"
#include "EntityManager.h"

Tower::Tower(const Tile* tile, TowerType typ) :Bulding(tile), LEVEL_MAX(2), level(1), table(), type(typ), target(nullptr), angleOfRotation(0)
{

	int t = type;
	setTexture(t);
	sf::Rect <int> rect(0, 0, 64, 64);
	_tile.setTexture(texturpack[0], rect);
	this->setOrigin();
	_tile.setPositionToCenter();
	//table.setEffect(type);
}

void Tower::setOrigin()
{
	//DANGER 32 = 64/2 64 -tile size 
	_tile.setOrigin(WIDTH / 2, HEIGHT / 2);
}
void Tower::update(sf::Time frametime)
{
	//std::cout << this->table.damage << "  ";
	elapsedTime += frametime;
	float rotation;
	if (target != nullptr)
	{
		sf::Vector2f tar = getTarget()->getPosition();
		sf::Vector2f center(32, 32);
		tar = tar + center;
		sf::Vector2f dir = tar - getTile()->getSprite().getPosition();

		rotation = 90 + (atan2(dir.y, dir.x)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
		float speed = 1.5 * 3.14159265;
		float relrotation = 180 / 3.14159265;
		if (rotation <= 270 && rotation >180)
			rotation = -90 + rotation - 270;
		float accuracy = 3;//measurement accuracy 1~3 depends from speed rotation
		if (!((angleOfRotation < (rotation + accuracy)) && ((rotation - accuracy) < angleOfRotation)))
		{
			if (abs(angleOfRotation - rotation) > 180)
			{
				if (angleOfRotation > 0)
				{
					angleOfRotation += relrotation * speed * frametime.asSeconds();
				}
				else
				{
					angleOfRotation -= relrotation * speed * frametime.asSeconds();
				}
				if (angleOfRotation < -180)
				{
					angleOfRotation = 360 + angleOfRotation;
				}
				if (angleOfRotation > 180)
				{
					angleOfRotation =  angleOfRotation - 360;
				}
			}
			else
			{
				if (angleOfRotation > rotation)
				{
					angleOfRotation -= relrotation * speed * frametime.asSeconds();
				}
				else
				{
					angleOfRotation += relrotation * speed * frametime.asSeconds();
				}

			}
		}
		else
		{
			angleOfRotation = rotation;
		}
		_tile.setRotation(angleOfRotation);//поворачиваем спрайт на эти градусы
	}
	const sf::Time oneSecond = sf::seconds(1.f);
	//shot System
	if (target != nullptr && rotation == angleOfRotation)
	{
		if (elapsedTime.asSeconds() > oneSecond.asSeconds() / table.attackSpeed)
		{
			elapsedTime = sf::Time::Zero;
			if (target->takeDamage(table.damage, table.type_ef))
			{
				_manager->addGold(target->getGold());
				//target->selfdestruction();
			}
		}
	}
	target = nullptr;
}
void Tower::draw(sf::RenderWindow* window)
{
	_tile.setTexture(texturpack[level - 1]);
	window->draw(_tile.getSprite());
}

void Tower::setTexture(int type)
{
	if (type == 1)
	{
		sf::Image widget; //создаем объект Image (изображение)
		widget.loadFromFile("data/simple_tower.png");//загружаем в него файл
		widget.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur;
		textur.loadFromImage(widget);
		sf::Image widget2; //создаем объект Image (изображение)
		widget2.loadFromFile("data/simple_tower_2.png");//загружаем в него файл
		widget2.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur2;
		textur2.loadFromImage(widget2);

		texturpack.push_back(textur);
		texturpack.push_back(textur2);
		table.type_ef = EffectType::none;
	}
	if (type == 2)//frost
	{
		sf::Image widget; //создаем объект Image (изображение)
		widget.loadFromFile("data/magic_tower_f.png");//загружаем в него файл
		widget.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur;
		textur.loadFromImage(widget);
		sf::Image widget2; //создаем объект Image (изображение)
		widget2.loadFromFile("data/magic_tower_f_2.jpg");//загружаем в него файл
		widget2.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur2;
		textur2.loadFromImage(widget2);

		texturpack.push_back(textur);
		texturpack.push_back(textur2);
		table.type_ef = EffectType::frost;
	}
	if (type == 3)//frost
	{
		sf::Image widget; //создаем объект Image (изображение)
		widget.loadFromFile("data/magic_tower_p.png");//загружаем в него файл
		widget.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur;
		textur.loadFromImage(widget);
		sf::Image widget2; //создаем объект Image (изображение)
		widget2.loadFromFile("data/magic_tower_p_2.png");//загружаем в него файл
		//widget2.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur2;
		textur2.loadFromImage(widget2);

		texturpack.push_back(textur);
		texturpack.push_back(textur2);
		table.type_ef = EffectType::poison;
	}
	if (type == 4)//weakness
	{
		sf::Image widget; //создаем объект Image (изображение)
		widget.loadFromFile("data/magic_tower_m.png");//загружаем в него файл
		widget.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur;
		textur.loadFromImage(widget);
		sf::Image widget2; //создаем объект Image (изображение)
		widget2.loadFromFile("data/magic_tower_m_2.jpg");//загружаем в него файл
		widget2.createMaskFromColor(sf::Color(255, 255, 255));
		sf::Texture textur2;
		textur2.loadFromImage(widget2);

		texturpack.push_back(textur);
		texturpack.push_back(textur2);
		table.type_ef = EffectType::m_weakness;
	}
}

void Tower::lvlUP()
{
	if (level + 1 <= LEVEL_MAX)
	{
		this->level++;
		table.up();
	}
}

bool TableStateTower::up()
{
	damage += 30;
	attackSpeed += 0.3;
	range += 40;
	return true;
}
void TableStateTower::setEffect(TowerType type_t)
{
	int type = type_t;
	switch (type)
	{
	case(1):
		type_ef = EffectType::none;
		break;
	case(2):
		type_ef = EffectType::frost;
		break;
	case(3):
		type_ef = EffectType::poison;
		break;
	case(4):
		type_ef = EffectType::m_weakness;
		break;
	default:
		break;
	}
}
Tower::Tower(const Tower& c)
{
	if (this != &c)
	{
		_manager = c._manager;
		this->angleOfRotation = c.angleOfRotation;
		this->target = c.target;
		this->_tile = c._tile;
		this->level = c.level;
		this->type = c.type;
		this->texturpack = c.texturpack;
		this->table = c.table;
	}
}
const Tower& Tower::operator=(const Tower& c)
{
	if (this != &c)
	{
		_manager = c._manager;
		this->angleOfRotation = c.angleOfRotation;
		this->target = c.target;
		this->_tile = c._tile;
		this->level = c.level;
		this->type = c.type;
		this->texturpack = c.texturpack;
		this->table = c.table;
	}
	return *this;
}
void Tower::setAngle(float angle)
{
	if (abs(angle) <= 180)
	{
		angleOfRotation = angle;
	}
	else
	{
		throw "Inccorrcet angle";
	}
}