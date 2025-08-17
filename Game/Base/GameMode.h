#pragma once

#include "Core/State.h"


namespace Game::GameMode
{
	class GameMode : public bae::State
	{
	public:
		GameMode() = default;
		~GameMode() = default;


		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual void Update() = 0;


	};
}


