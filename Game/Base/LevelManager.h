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

namespace Game::Level
{
	struct Level;

	//struct LevelState
	//{
		//std::vector<
	//};

	class LevelManager final : public bae::Singleton<LevelManager>
	{
	public:
		void LoadLevel(const std::filesystem::path& filePath);
		void LoadLevelsFromDirectory(const std::filesystem::path& folderPath);

		// Level management
		Level* GetCurrentLevel() const { return m_pCurrentLevel; }
		int GetCurrentLevelNumber() const { return m_CurrentLevelNumber; }

		bool SetCurrentLevel(int levelNumber);
		Level* GetLevel(int levelNumber) const;

		// Scene integration
		void SpawnLevelInScene(bae::Scene& scene);
		void ClearScene(bae::Scene& scene);

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


		glm::vec2 GridToWorld(const GridPosition& gridPos) const;

		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateEntityManager(bae::Scene& scene) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateGrid(const Grid& grid) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreatePlayer(const GridPosition& pos) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateEmerald(const Emerald& emerald) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateGoldBag(const GoldBag& goldBag) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateBonus(const Bonus& bonus) const;
		std::shared_ptr<bae::GameObject> [[nodiscard]] CreateNobbinSpawner(const NobbinSpawner& spawner, bae::Scene& scene) const;


		std::unordered_map<int, std::unique_ptr<Level>> m_Levels{};
		bae::Scene* m_pScene{};
		Level* m_pCurrentLevel{};
		int m_CurrentLevelNumber{};

		Game::Components::GridComponent* m_pGridComponent{};
		Game::Components::EntityManagerComponent* m_pEntityManagerCompenent{};
		bae::SpriteComponent* m_pDugGroundComponent{};
		bae::GameObject* m_pPlayer{};

		int m_EmeraldsCollected{};
		int m_NobbinsKilled{};


	};
}


