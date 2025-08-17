#pragma once

#include <memory>
#include <vector>

#include "Singletons/Singleton.h"
#include "Core/GameObject.h"


namespace Game::GameMode
{
	enum class GameMode
	{
		SinglePlayer,
		Co_Op,
		Versus
	};

	struct PlayerData
	{
		int playerId;
		int score;
		int lives;
		bool isActive;

		bae::GameObject* playerObject = nullptr;
	};


	class GameModeManager : public bae::Singleton<GameModeManager>
	{
	public:

		GameMode GetGameMode() const { return m_GameMode; }
		void SetGameMode(GameMode mode);

		void InitializePlayers();

		void AddPlayer(int playerId);
		void RemovePlayer(int playerId);

		PlayerData* GetPlayerData(int playerId);
		const std::vector<PlayerData>& GetAllPlayerData() const { return m_PlayersData; }

		bool ShouldRespawnPlayer(int playerId) const;
		bool IsGameOver() const;
		bool IsLevelCompolete() const;


		// for verus mode
		PlayerData* GetWinningPlayerData();
		bool HasPlayerWon() const;


	private:
		friend class bae::Singleton<GameModeManager>;
		GameModeManager() = default;
		~GameModeManager() = default;


		void ClearPlayers();


		GameMode m_GameMode;
		std::vector<PlayerData> m_PlayersData;


	};
}


