#include "MoveComponent.h"

#include "Singletons/GameTime.h"

#include "../Base/LevelManager.h"
#include "../Base/DirectionEnum.h"


using namespace Game::Components;


MoveComponent::MoveComponent(bae::GameObject& owner, float speed) :
	bae::Component(owner),
	m_Speed{ speed }
{
	auto gridComp = Game::Managers::LevelManager::GetInstance().GetGridComponent();
	m_TerrainGridGraph = gridComp->GetTerrainGridGraph();
	m_GridPosition = m_TerrainGridGraph->GetOffsetPosition();
	m_GridCellSize = m_TerrainGridGraph->GetCellSize();
	m_Columns = m_TerrainGridGraph->GetColumns();
	m_Rows = m_TerrainGridGraph->GetRows();
}

void MoveComponent::Update()
{
	m_bMoved = false;

}

void MoveComponent::MoveInDirection(Game::Direction direction)
{
	if (m_bMoved)
		return;
	m_bMoved = true;


	const auto& position = m_Owner->GetWorldLocation();
	const glm::ivec2 gridRowColum = m_TerrainGridGraph->GetRowAndColumn(position);


	// going left/right
	if (m_PreviousDirection == Game::Direction::Left || m_PreviousDirection == Game::Direction::Right)
	{
		if (direction == Game::Direction::Left || direction == Game::Direction::Right)
			if (m_PreviousDirection != direction)
				m_PreviousDirection = direction;

	}
	// going up/down
	else if (m_PreviousDirection == Game::Direction::Up || m_PreviousDirection == Game::Direction::Down)
	{
		if (direction == Game::Direction::Up || direction == Game::Direction::Down)
			if (m_PreviousDirection != direction)
				m_PreviousDirection = direction;

	}


	if (IsAtGridPosition())
	{
		m_PreviousDirection = Game::Direction::Nothing;

		// on left edge
		if ((gridRowColum.y == 0) && (direction == Game::Direction::Left))
			return;

		// on top edge
		if ((gridRowColum.x == 0) && (direction == Game::Direction::Up))
			return;

		// on right edge
		if ((gridRowColum.y == m_Columns - 1) && (direction == Game::Direction::Right))
			return;

		// on bottom edge
		if ((gridRowColum.x == m_Rows - 1) && (direction == Game::Direction::Down))
			return;

		m_PreviousDirection = direction;
	}


	m_Owner->AddLocation({ m_Speed * Game::DirectionToVec(m_PreviousDirection) * bae::GameTime::GetInstance().GetDeltaTime() });

}

bool MoveComponent::IsAtGridPosition()
{
	const auto& position = m_Owner->GetWorldLocation();
	const glm::ivec2 gridRowColum = m_TerrainGridGraph->GetRowAndColumn(position);

	const glm::vec2 gridPos = m_TerrainGridGraph->GetPosition(gridRowColum.y, gridRowColum.x);

	SDL_Point sdlPos
	{
		static_cast<int>(position.x),
		static_cast<int>(position.y)
	};

	SDL_Rect gridCloseRect
	{
		static_cast<int>(gridPos.x - m_GridTolerance),
		static_cast<int>(gridPos.y - m_GridTolerance),
		static_cast<int>(2 * m_GridTolerance),
		static_cast<int>(2 * m_GridTolerance)
	};

	return SDL_PointInRect(&sdlPos, &gridCloseRect);
}


