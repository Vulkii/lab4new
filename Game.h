#pragma once
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
#include <SFML/Graphics.hpp>
#include "StateSystem.h"
#include "SystemMouse.h"
#include "GameState.h"
#include "level.h"
#include "DamageSystem.h"
#include "MoveSystem.h"
//#include "GameState.h"


using namespace sf;

/*!
\brief Game namespace
*/
namespace Game_def {

    /*!
\brief A class that implements the application program*/
    class Game : sf::NonCopyable {
    public:

        /*!
        \brief An empty constructor that loads all systems and the map itself.

        Actually it construct the entire game
        */
        Game();

        /*!
\brief Starts the application program*/
        void run();


    private:
        bool pause;
        bool error;
        void update(Time frameTime);
        void processEvent();
        void draw();
        Texture textureMenadger;
        int score;
        RenderWindow window;
        StateManager manager;
        GameState gState;
        DamageSystem dSys;
        MoveSystem mSys;
    };
}
#endif