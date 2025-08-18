#pragma once

#include <glm.hpp>

#include "Components/Component.h"

#include "../Base/TerrainGridGraph.h"
#include "../Base/DirectionEnum.h"


namespace Game::Components
{
	class MoveComponent : public bae::Component
	{
	public:
		MoveComponent(bae::GameObject& owner, float speed);

		void Update() override;


		float GetSpeed() const { return m_Speed; }
		void SetSpeed(float speed) { m_Speed = speed; }
		void MoveInDirection(Game::Direction direction);


		float m_GridTolerance{ 1.f };


	private:
		bool IsAtGridPosition();



		float m_Speed;

		Game::AI::TerrainGridGraph* m_TerrainGridGraph;

		Game::Direction m_PreviousDirection{ Game::Direction::Nothing };

		glm::vec2 m_GridPosition;
		glm::ivec2 m_GridCellSize;
		int m_Columns;
		int m_Rows;

		bool m_bMoved{ false };


	};
}


