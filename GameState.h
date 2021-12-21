#pragma once
#ifndef __GAMESTATE_H_INCLUDED__
#define __GAMESTATE_H_INCLUDED__
#include "level.h"
#include "State.h"
#include "EntityManager.h"
#include "System.h"


class GameState:public State {
public:


    virtual bool handleEvent(const sf::Event& event) ;

 
    virtual bool update(sf::Time dt) ;
    GameState(sf::RenderWindow* window);
    void draw();
    const Level& getLevel()const;
    void addSystem(System*, int);
    EntityManager* getEManager() { return &eManager; }
    Level* getLevel() { return  &level; }
private: 


    int widget_buy(sf::RenderWindow*, bool trap = false);

 
    int widget_up(sf::RenderWindow*);
    void setEManager(Level* lvl);
    sf::RenderWindow* window;
    Level level;
    EntityManager eManager;
};
#endif