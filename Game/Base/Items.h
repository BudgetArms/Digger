#pragma once

#include <glm.hpp>


namespace Game::Level
{
	struct GridPosition
	{
		int column, row;
	};

	struct Grid
	{
		int columns;
		int rows;
		glm::ivec2 cellSize;
		bool bIsDirectionalGraph;
		bool bIsConnectedDiagonally;
		float costStraight;
		float costDiagonally;
	};

	struct Bonus
	{
		float bonusModeTime;
		float bonusModeScore;
	};

	struct NobbinSpawner
	{
		GridPosition position;
		float spawnDelay;
		int maxNobbins;
		int totalToSpawn;

		Bonus bonus;
	};

	struct Emerald
	{
		GridPosition position;
	};

	struct GoldBag
	{
		GridPosition position;

	};


}


