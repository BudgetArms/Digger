#pragma once

#include "../States/DiggerState.h"
#include "Core/GameObject.h"


namespace Game::States
{
	class DiggerDeathState : public Game::States::DiggerState
	{
	public:
		void OnEnter(bae::GameObject& owner);
		void OnExit() override;

		void Update() override;

	private:
		float m_ElapsedSec{};
		float m_DeathTime{ 2.f };


	};

}