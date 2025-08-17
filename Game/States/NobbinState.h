#pragma once

#include "Core/State.h"


namespace Game::States
{
	class NobbinState : public bae::State
	{
	public:
		void OnEnter() = 0;
		void OnExit() = 0;

		void Update() = 0;

	};
}


