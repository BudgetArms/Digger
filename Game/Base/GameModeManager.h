#pragma once

#include <memory>
#include <vector>

#include "Singletons/Singleton.h"
#include "Core/GameObject.h"

#include "../Base/GameMode.h"


namespace Game::GameMode
{
	class GameModeManager : public bae::Singleton<GameModeManager>
	{
	public:
		void Update();


		GameMode* GetGameMode() const { return m_GameMode.get(); }
		void SetGameMode(std::unique_ptr<GameMode> uGameMode);


	private:
		friend class bae::Singleton<GameModeManager>;
		GameModeManager() = default;
		~GameModeManager() = default;


		std::unique_ptr<GameMode> m_GameMode;


	};
}


