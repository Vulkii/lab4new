//
// pch.h
// Header for standard system include files.
//

#pragma once
#include "gtest/gtest.h"
#include "../ConsoleApplication1/EntityManager.h"
#include "../ConsoleApplication1/EntityManager.cpp"

#include "../ConsoleApplication1/EnemyWave.h"
#include "../ConsoleApplication1/EnemyWave.cpp"

#include "../ConsoleApplication1/Tile.h"
#include "../ConsoleApplication1/Tile.cpp"

#include "../ConsoleApplication1/Trap.h"
#include "../ConsoleApplication1/Trap.cpp"

#include "../ConsoleApplication1/Castle.h"
#include "../ConsoleApplication1/Castle.cpp"

#include "../ConsoleApplication1/Lier.h"
#include "../ConsoleApplication1/Lier.cpp"

#include "../ConsoleApplication1/Effect.h"
#include "../ConsoleApplication1/Effect.cpp"

#include "../ConsoleApplication1/Enemy.h"
#include "../ConsoleApplication1/Enemy.cpp"

#include "../ConsoleApplication1/Movesystem.h"
#include "../ConsoleApplication1/Movesystem.cpp"

//#include "../../MoveSystem.h"


class TestSituation : ::testing::Environment
{
	void  SetUp()
	{
		std::cout << "I'm here in set up" << std::endl;
	}

	void TearDown()
	{
		std::cout << "I'm here in tear down" << std::endl;
	}
};
int clear_boy();