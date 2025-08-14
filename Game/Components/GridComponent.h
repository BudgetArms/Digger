#pragma once

#include <memory>

#include "Components/Component.h"
#include "../Base/TerrainGridGraph.h"


namespace Game
{
	class GridComponent : public bae::Component
	{
	public:
		GridComponent(bae::GameObject& owner, int columns, int rows, const glm::ivec2& cellSize, bool isDirectionalGraph, bool isConnectedDiagonally, float costStraight = 1.f, float costDiagonally = 1.5f);

		virtual void Render() const override;
		virtual void Update() override;


		AI::TerrainGridGraph* GetTerrainGridGraph() { return m_TerrainGridGraph.get(); };


	private:
		std::unique_ptr<AI::TerrainGridGraph> m_TerrainGridGraph;

		int m_WindowWidth;
		int m_WindowHeight;


	};
}


