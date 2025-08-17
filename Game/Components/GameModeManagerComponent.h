#pragma once

#include "Components/Component.h"
#include "../Base/GameModeManager.h"


namespace Game::Components
{
	class GameModeManagerComponent : public bae::Component
	{
	public:
		GameModeManagerComponent(bae::GameObject& owner) :
			bae::Component(owner)
		{
			Game::GameMode::GameModeManager::GetInstance();
		}

		void Update() override
		{
			Game::GameMode::GameModeManager::GetInstance().Update();
		}


	};
}


