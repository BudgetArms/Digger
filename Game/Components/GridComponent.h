#pragma once

#include <memory>

#include "Components/Component.h"
#include "../Base/TerrainGridGraph.h"


namespace Game::Components
{
	class GridComponent : public bae::Component
	{
	public:
		GridComponent(bae::GameObject& owner, int columns, int rows, const glm::ivec2& cellSize,
			bool isDirectionalGraph, bool isConnectedDiagonally, float costStraight = 1.f, float costDiagonally = 1.5f);

		virtual void Render() const override;

		Game::AI::TerrainGridGraph* GetTerrainGridGraph() { return m_TerrainGridGraph.get(); };
		glm::vec2 GridToWorld(glm::ivec2 gridPos) const;


	private:
		std::unique_ptr<Game::AI::TerrainGridGraph> m_TerrainGridGraph;

		int m_WindowWidth;
		int m_WindowHeight;


	};
}


