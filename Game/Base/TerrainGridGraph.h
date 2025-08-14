#pragma once

#include "Graphs/GridGraph.h"

#include "TerrainTypes.h"


namespace Game::AI
{
	class TerrainGridGraph : public bae::Graphs::GridGraph
	{
	public:
		TerrainGridGraph(const glm::vec2& position, int columns, int rows, const glm::ivec2& cellSize,
			bool isDirectionalGraph, bool isConnectedDiagonally, float costStraight = 1.f,
			float costDiagonally = 1.5f);

		void SetNodeTerrainType(int nodeId, TerrainType type) const;


	};
}


