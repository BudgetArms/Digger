#include "GameModeManager.h"

#include <algorithm>
#include <ranges>
#include <iostream>


using namespace Game::GameMode;


void GameModeManager::SetGameMode(GameMode gameMode)
{
	if (m_GameMode == gameMode)
		return;

	m_GameMode = gameMode;

	InitializePlayers();

	std::cout << "Set GameMode to: ";
	switch (m_GameMode)
	{
		case Game::GameMode::GameMode::SinglePlayer:
			std::cout << "SinglePlayer" << '\n';
			break;
		case Game::GameMode::GameMode::Co_Op:
			std::cout << "Co-Op" << '\n';
			break;
		case Game::GameMode::GameMode::Versus:
			std::cout << "Verus" << '\n';
			break;
	}


}

void GameModeManager::InitializePlayers()
{
	ClearPlayers();

	AddPlayer(0);

	if (m_GameMode != GameMode::SinglePlayer)
		AddPlayer(1);

}

void GameModeManager::AddPlayer(int playerId)
{
	if (GetPlayerData(playerId) != nullptr)
		return;


	// needs to be linked to levelmanager somehow
	PlayerData playerData =
	{
		.playerId = playerId,
		.score = 0,
		.lives = 4,
		.isActive = true
	};

	m_PlayersData.push_back(playerData);

}

void GameModeManager::RemovePlayer(int playerId)
{
	if (GetPlayerData(playerId) == nullptr)
		return;

	auto playerDataIt = std::find_if(m_PlayersData.begin(), m_PlayersData.end(),
		[playerId](const PlayerData& playerData)
		{
			return playerData.playerId == playerId;
		});

	if (playerDataIt == m_PlayersData.end())
		return;

	m_PlayersData.erase(playerDataIt);
	std::cout << "removed player from gameMode" << '\n';
}

PlayerData* GameModeManager::GetPlayerData(int playerId)
{

	auto playerDataIt = std::find_if(m_PlayersData.begin(), m_PlayersData.end(),
		[&playerId](const PlayerData& playerData)
		{
			return playerData.playerId == playerId;
		});

	if (playerDataIt == m_PlayersData.end())
		return nullptr;

	return &(*playerDataIt);
}

bool GameModeManager::ShouldRespawnPlayer(int playerId) const
{
	playerId;
	return false;
}

bool GameModeManager::IsGameOver() const
{
	return false;
}

bool GameModeManager::IsLevelCompolete() const
{
	return false;
}

PlayerData* GameModeManager::GetWinningPlayerData()
{
	if (m_GameMode != GameMode::Versus)
		return nullptr;

	PlayerData* winner = nullptr;
	int maxScore = -1;

	for (auto& playerData : m_PlayersData)
	{
		if (playerData.isActive && playerData.score > maxScore)
		{
			maxScore = playerData.score;
			winner = &playerData;
		}
	}

	return winner;
}

bool GameModeManager::HasPlayerWon() const
{
	if (m_GameMode != GameMode::Versus)
		return false;


	// if the player is still alive or something or got all emeralds
	return 1;

}


void GameModeManager::ClearPlayers()
{
	m_PlayersData.clear();
}


