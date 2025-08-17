#pragma once

#include "../States/DiggerState.h"


namespace Game::States
{
	class DiggerWinState : public Game::States::DiggerState
	{
	public:
		void OnEnter(bae::GameObject& owner) override;
		void OnExit() override;

		void Update() override;


	};

}

