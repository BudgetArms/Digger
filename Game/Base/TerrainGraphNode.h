#pragma once

#include "Graphs/GraphNode.h"

#include "TerrainTypes.h"


namespace Game::AI
{
	class TerrainGraphNode : public bae::Graphs::GraphNode
	{
	public:
		TerrainGraphNode(const glm::vec2& pos) :
			bae::Graphs::GraphNode(pos),
			m_Terrain{ TerrainType::Ground }
		{
		}

		TerrainGraphNode(const TerrainGraphNode& other) :
			bae::Graphs::GraphNode(other),
			m_Terrain{ other.m_Terrain }
		{
		}

		virtual ~TerrainGraphNode() = default;

		TerrainType GetTerrainType() const { return m_Terrain; }
		void SetTerrainType(TerrainType terrain) { m_Terrain = terrain; }


	protected:
		TerrainType m_Terrain;


	};
}


