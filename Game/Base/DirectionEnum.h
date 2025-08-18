#pragma once

#include <glm.hpp>


namespace Game
{
	enum class Direction
	{
		Left,
		Right,
		Up,
		Down,
		Nothing // for moveCommand
	};

	constexpr glm::vec2 DirectionToVec(Direction direction)
	{
		switch (direction)
		{
			case Game::Direction::Left:
				return { -1, 0 };
				break;
			case Game::Direction::Right:
				return { 1, 0 };
				break;
			case Game::Direction::Up:
				return { 0, -1 };
				break;
			case Game::Direction::Down:
				return { 0, 1 };
				break;
			case Game::Direction::Nothing:
				return { 0, 0 };
				break;
		}

		return { 1, 1 };
	}


}