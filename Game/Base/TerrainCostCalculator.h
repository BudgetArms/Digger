#pragma once

#include "Graphs/ConnectionCostCalculator.h"

#include "TerrainGraphNode.h"


namespace Game::AI
{
	class TestCostCalculator : public bae::Graphs::ConnectionCostCalculator
	{
	public:
		TestCostCalculator() = default;
		~TestCostCalculator() = default;

		virtual float CalculateConnectionCost(const bae::Graphs::Graph* const pGraph, int fromNodeId, int toNodeId) const override
		{
			TerrainGraphNode* fromNode = static_cast<TerrainGraphNode*>(pGraph->GetNode(fromNodeId));
			TerrainGraphNode* toNode = static_cast<TerrainGraphNode*>(pGraph->GetNode(toNodeId));

			int maxCost = std::max(static_cast<int>(fromNode->GetTerrainType()), static_cast<int>(toNode->GetTerrainType()));
			return static_cast<float>(maxCost);
		}


	};
}


