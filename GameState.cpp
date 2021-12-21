
#include "GameState.h"
#include "Tile.h"
#include "Tower.h"
#include "EffectType.h"
GameState::GameState(sf::RenderWindow* window1) : window(window1), level("data/maps/TestMap.tmx"), eManager(level)
{
	eManager.setGameState(this);
}
bool GameState::handleEvent(const sf::Event& event)
{
	int choise = 0;
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.key.code == sf::Mouse::Right)
		{
			std::cout << "right" << std::endl;
			sf::Vector2i vec = sf::Mouse::getPosition(*window);
			int state = level.getGrid().getTile(vec.y / level.GetTileSize().y, vec.x / level.GetTileSize().x)->getState();
			if ((state == 0) && (eManager.getGold() >= 110))
			{
				choise = widget_buy(window);
				if (choise > 0)
				{
					TowerType type;
					if (choise == TowerType::SimpleTower)
						type = TowerType::SimpleTower;
					else
						if (choise == TowerType::MagicTowerF)
							type = TowerType::MagicTowerF;
						else
							if (choise == TowerType::MagicTowerM)
								type = TowerType::MagicTowerM;
							else
								type = MagicTowerP;

					if (!eManager.checkGold(type, 1))
					{
						level.setObject(vec,1);//Set state of tile

						Tower tower(level.getGrid().getTile(vec.y / level.GetTileSize().y, vec.x / level.GetTileSize().x), type);
						tower.setEManager(&eManager);
						eManager.addTower(tower);

					}
				}
				std::cout << "right-click - succesfuly" << std::endl;
				if (choise == -1)
					return false;
			}
			if (state == 4)//lvlUP
			{
				choise = widget_up(window);
				if (choise > 4)
				{
					if (choise == 5)
					{
						TowerType type;
						if (choise-4 == TowerType::SimpleTower)
							type = TowerType::SimpleTower;
						else
							if (choise-4 == TowerType::MagicTowerF)
								type = TowerType::MagicTowerF;
							else
								if (choise-4 == TowerType::MagicTowerM)
									type = TowerType::MagicTowerM;
								else
									type = MagicTowerP;
						if (!eManager.checkGold(type, 2))
						{
							eManager.lvlUP(vec);
						}
					}
					else
					{
						level.setObject(vec, -1);
						eManager.removeTower(vec);
					}
				}

				if (choise == -1)
					return false;
			}

			if (state == 1)
			{
				choise = widget_buy(window,true);
				if (choise > 0)
				{
					EffectType type;
					choise--;
					if (choise == EffectType::none)
						return false;
					else
						if (choise == EffectType::frost)
							type = EffectType::frost;
						else
							if (choise == EffectType::m_weakness)
								type = EffectType::m_weakness;
							else
								type = EffectType::poison;

					if (!eManager.checkGold(TowerType::SimpleTower, 1))
					{
						level.setObject(vec, 2);//Set state of tile/// 2== traps/// <0 == delete

						Trap trap(level.getGrid().getTile(vec.y / level.GetTileSize().y, vec.x / level.GetTileSize().x), type);
						trap.setEManager(&eManager);
						eManager.addTrap(trap);

					}
				}

				std::cout << "right-click - succesfuly" << std::endl;
				if (choise == -1)
					return false;
			}
		}
		//Здесь должна быть обратока выбор постройки и выбор альтертатив для улучшения

		if (event.key.code == sf::Mouse::Left)
		{
			std::cout << "left" << std::endl;
		}
	}

	return true;
}

bool GameState::update(sf::Time dt)
{
	eManager.update(dt);
	return true;
}
void GameState::setEManager(Level* lvl)
{
	eManager.setParameters(*lvl);
}
void GameState::addSystem(System* sys, int id_s)
{
	eManager.addSystem(sys, id_s);
}
void GameState::draw()
{
	//level.DrawMap(*window);
	level.DrawGrid(*window);
	eManager.draw(window);
}
const Level& GameState::getLevel()const
{
	return level;
}
int GameState::widget_buy(sf::RenderWindow* window, bool trap)
{
	int choise;
	sf::Vector2i vec = sf::Mouse::getPosition(*window);
	sf::Texture widget_buy;
	if (trap)
	{
		if (!widget_buy.loadFromFile("data/widget/widget_buy_effect_trap.jpg"))
		{
			std::cout << "Widget buy doesn't load" << std::endl;
			//	exit(0);
		}
	}
	else
	{
		if (!widget_buy.loadFromFile("data/widget/widget_buy_effect.jpg"))
		{
			std::cout << "Widget buy doesn't load" << std::endl;
			//	exit(0);
		}
	}
	sf::Sprite menu1(widget_buy);
	menu1.setTextureRect(sf::IntRect(0, 0, 64, 64));

	sf::Sprite menu2(widget_buy);
	menu2.setTextureRect(sf::IntRect(64, 0, 64, 64));

	sf::Sprite menu3(widget_buy);
	menu3.setTextureRect(sf::IntRect(0, 64, 64, 64));

	sf::Sprite menu4(widget_buy);
	menu4.setTextureRect(sf::IntRect(64, 64, 64, 64));

	menu1.setPosition(vec.x - 64, vec.y - 64);
	menu2.setPosition(vec.x, vec.y - 64);
	menu3.setPosition(vec.x - 64, vec.y);
	menu4.setPosition(vec.x, vec.y);


	bool isMenu = 1;
	int menuNumb = 0;
	sf::Vector2i tmp;
	sf::Event Event;
	int fluctuation_x, fluctuation_y, fluctuation_x2, fluctuation_y2;
	while (isMenu)
	{
		menuNumb = 0;
		tmp = sf::Mouse::getPosition(*window);
		fluctuation_x = (int)(tmp.x - vec.x);
		fluctuation_y = (int)(tmp.y - vec.y);
		//std::cout << "x: " << tmp.x << " y: " << tmp.y;
	//	std::cout << "\nf1 x: " << fluctuation_x << " f1 y: " << fluctuation_y;
		if ((abs(fluctuation_x) <= 64 && fluctuation_x < 0) && (abs(fluctuation_y) <= 64 && fluctuation_y < 0))
		{
			menu1.setColor(sf::Color::Red); menuNumb = 1;
		}
		else
		{
			menu1.setColor(sf::Color::White);
		}


		if ((abs(fluctuation_x) <= 64 && fluctuation_x > 0) && (abs(fluctuation_y) <= 64 && fluctuation_y < 0))
		{
			menu2.setColor(sf::Color::Red); menuNumb = 2;
		}
		else
		{
			menu2.setColor(sf::Color::White);
		}


		if ((abs(fluctuation_x) <= 64 && fluctuation_x < 0) && (abs(fluctuation_y) <= 64 && fluctuation_y > 0))
		{
			menu3.setColor(sf::Color::Red); menuNumb = 3;
		}
		else
		{
			menu3.setColor(sf::Color::White);
		}

		if ((abs(fluctuation_x) <= 64 && fluctuation_x > 0) && (abs(fluctuation_y) <= 64 && fluctuation_y > 0))
		{
			menu4.setColor(sf::Color::Red); menuNumb = 4;
		}
		else
		{
			menu4.setColor(sf::Color::White);
		}


		while (window->pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (Event.type == sf::Event::MouseButtonPressed)
			{

				if (menuNumb != 0)
				{
					std::cout << "succes" << std::endl;
					isMenu = false;
					choise = menuNumb;
				}
				else
				{
					std::cout << "unsucces" << std::endl;
					isMenu = false;
					choise = 0;
				}
			}
			//Key pressed

		}
		//system("cls");
		window->draw(menu1);
		window->draw(menu2);
		window->draw(menu3);
		window->draw(menu4);
		window->display();
	}
	return choise;
}

int GameState::widget_up(sf::RenderWindow* window)
{
	int choise;
	sf::Vector2i vec = sf::Mouse::getPosition(*window);
	sf::Texture widget_buy;
	if(!widget_buy.loadFromFile("data/widget/widget_lvlup.jpg"))
	{
		std::cout << "Widget lvlup doesn't load" << std::endl;
	//	exit(0);
	}
	sf::Sprite menu1(widget_buy);
	menu1.setTextureRect(sf::IntRect(0, 0, 64, 64));

	sf::Sprite menu2(widget_buy);
	menu2.setTextureRect(sf::IntRect(64, 0, 64, 64));

	menu1.setPosition(vec.x - 64, vec.y - 32);
	menu2.setPosition(vec.x, vec.y - 32);
	bool isMenu = 1;
	int menuNumb = 0;
	sf::Vector2i tmp;
	sf::Event Event;
	int fluctuation_x, fluctuation_y, fluctuation_x2, fluctuation_y2;
	while (isMenu)
	{
		menuNumb = 0;
		tmp = sf::Mouse::getPosition(*window);
		fluctuation_x = (int)(tmp.x - vec.x);
		fluctuation_y = (int)(tmp.y - vec.y - 32);
		std::cout << "x: " << tmp.x << " y: " << tmp.y;
		std::cout << "\nf1 x: " << fluctuation_x << " f1 y: " << fluctuation_y;
		if ((abs(fluctuation_x) <= 64 && fluctuation_x < 0) && (abs(fluctuation_y) <= 64 && fluctuation_y < 0))
		{
			menu1.setColor(sf::Color::Red); menuNumb = 1;
		}
		else
		{
			menu1.setColor(sf::Color::White);
		}


		if ((abs(fluctuation_x) <= 64 && fluctuation_x > 0) && (abs(fluctuation_y) <= 64 && fluctuation_y < 0))
		{
			menu2.setColor(sf::Color::Red); menuNumb = 2;
		}
		else
		{
			menu2.setColor(sf::Color::White);
		}
		while (window->pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (menuNumb != 0)
				{
					std::cout << "succes" << std::endl;
					isMenu = false;
					choise = menuNumb;
				}
				else
				{
					isMenu = false;
					choise = 0;
				}
			}
			//Key pressed

		}
		system("cls");
		window->draw(menu1);
		window->draw(menu2);
		window->display();
	}
	return choise + 4;
}

