#pragma once

#include "Core/GameObject.h"

#include "../States/DiggerState.h"


namespace Game::States
{
	class DiggerNormalState : public Game::States::DiggerState
	{
	public:
		void OnEnter(bae::GameObject& owner) override;
		void OnExit() override;

		void Update() override;


	};
}

