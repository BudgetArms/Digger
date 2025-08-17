#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <filesystem>

#include <glm.hpp>
#include <nlohmann/json.hpp>

#include "Singletons/Singleton.h"
#include "Core/Scene.h"

#include "../Base/Items.h"
#include "../Base/Level.h"
#include "../Components/GridComponent.h"


namespace bae
{
	class GameObject;
	//class GridComponent;
	class SpriteComponent;
}
namespace Game::Components
{
	class EntityManagerComponent;
}

namespace Game::Managers
{
	class LevelManager final : public bae::Singleton<LevelManager>
	{
	public:
		void LoadLevel(const std::filesystem::path& filePath);
		void LoadLevelsFromDirectory(const std::filesystem::path& folderPath);

		void SetScene(bae::Scene& scene) { m_pScene = &scene; }

		// Level management
		Game::Level::Level* GetCurrentLevel() const { return m_pCurrentLevel; }
		int GetCurrentLevelNumber() const { return m_CurrentLevelNumber; }

		bool SetCurrentLevel(int levelNumber);
		Game::Level::Level* GetLevel(int levelNumber) const;

		// Scene integration
		void SpawnLevel();
		void ClearScene();

		bool IsLevelComplete() const;
		void ResetLevel();
		void ReloadLevel();

		int GetNrLevels() const { return static_cast<int>(m_Levels.size()); }
		bool HasLevel(int levelNumber) const;

		int GetTotalNobbins() const;


		bae::GameObject* GetPlayer() const { return m_pPlayer; }
		Game::Components::GridComponent* GetGridComponent() const { return m_pGridComponent; }


	private:
		friend class bae::Singleton<LevelManager>;
		LevelManager();
		~LevelManager();


		glm::vec2 GridToWorld(const Game::Level::GridPosition& gridPos) const;

		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateGrid(const Game::Level::Grid& grid) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreatePlayer(const Game::Level::GridPosition& pos) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateEmerald(const Game::Level::Emerald& emerald) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateGoldBag(const Game::Level::GoldBag& goldBag) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateBonus(const Game::Level::Bonus& bonus) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateNobbinSpawner(const Game::Level::NobbinSpawner& spawner) const;


		std::unordered_map<int, std::unique_ptr<Game::Level::Level>> m_Levels{};
		bae::Scene* m_pScene{};
		Game::Level::Level* m_pCurrentLevel{};
		int m_CurrentLevelNumber{};

		Game::Components::GridComponent* m_pGridComponent{};
		Game::Components::EntityManagerComponent* m_pEntityManagerCompenent{};
		bae::SpriteComponent* m_pDugGroundComponent{};
		bae::GameObject* m_pPlayer{};

		int m_EmeraldsCollected{};
		int m_NobbinsKilled{};


	};
}


