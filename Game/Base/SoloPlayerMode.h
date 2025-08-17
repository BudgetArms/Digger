#pragma once

#include "../Base/GameMode.h"


namespace Game::GameMode
{
	class SoloPlayerMode : public Game::GameMode::GameMode
	{
	public:
		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual void Update() override {};


	};
}

