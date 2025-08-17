#include "GameModeManager.h"

#include <algorithm>
#include <ranges>
#include <iostream>

#include "../Base/LevelManager.h"


using namespace Game::GameMode;


void GameModeManager::Update()
{
	if (m_GameMode)
		m_GameMode->Update();
}


void GameModeManager::SetGameMode(std::unique_ptr<GameMode> uGameMode)
{
	if (m_GameMode)
		m_GameMode->OnExit();


	m_GameMode = std::move(uGameMode);

	Game::Managers::LevelManager::GetInstance().ClearScene();

	m_GameMode->OnEnter();

}


