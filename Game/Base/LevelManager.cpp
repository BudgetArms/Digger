#include "LevelManager.h"

#include <fstream>
#include <memory>

#include "Core/GameObject.h"
#include "Core/HelperFunctions.h"

#include "../Base/Level.h"
#include "../Base/EntityManager.h"
#include "../Components/GridComponent.h"
#include "../Entities/BonusComponent.h"
#include "../Entities/DiggerComponent.h"
#include "../Entities/EmeraldComponent.h"
#include "../Entities/GoldBagComponent.h"
#include "../Entities/NobbinComponent.h"
#include "../Entities/NobbinSpawnerComponent.h"


using namespace Game::Managers;
using njson = nlohmann::json;
namespace fs = std::filesystem;


LevelManager::LevelManager() :
	m_Levels{},
	m_pGridComponent{}
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadLevel(const fs::path& filePath)
{
	if (!fs::exists(filePath))
	{
		std::cout << GetFunctionName() << " Couldn't find file: " << filePath << '\n';
		return;
	}

	std::ifstream file{ filePath, std::ios::binary };
	if (!file.is_open())
	{
		std::cout << GetFunctionName() << " Couldn't open file: " << filePath << '\n';
		return;
	}

	njson json;
	std::unique_ptr<Game::Level::Level> uLevel;

	try
	{
		file >> json;
		uLevel = std::make_unique<Game::Level::Level>(json.get<Game::Level::Level>());
	}
	catch (const std::exception& e)
	{
		std::cout << GetFunctionName() << " json couldn't be loaded or couldn't parse file, file: " << filePath << '\n';
		std::cout << GetFunctionName() << " error: " << e.what() << '\n';
	}


	if (!uLevel)
	{
		std::cout << GetFunctionName() << " failed to convert json to Level data, file: " << filePath << '\n';
		return;
	}

	int levelNumber = uLevel->levelNumber;
	if (m_Levels.find(levelNumber) != m_Levels.end())
	{
		std::cout << GetFunctionName() << " WARNING: Level with levelNumber: " << levelNumber << " is already loaded" << '\n';
		return;
	}

	m_Levels[levelNumber] = std::move(uLevel);
}

void LevelManager::LoadLevelsFromDirectory(const fs::path& folderPath)
{
	if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
	{
		std::cout << GetFunctionName() << " Couldn't find folder: " << folderPath << '\n';
		return;
	}

	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		if (!entry.exists() || entry.path().extension() != ".json")
			continue;

		std::cout << GetFunctionName() << " found file: " << entry << '\n';
		LoadLevel(entry.path());
	}

}


bool LevelManager::SetCurrentLevel(int levelNumber)
{
	auto levelIt = m_Levels.find(levelNumber);
	if (levelIt == m_Levels.end())
		return false;

	m_CurrentLevelNumber = levelNumber;
	m_pCurrentLevel = levelIt->second.get();

	return true;

}

Game::Level::Level* LevelManager::GetLevel(int levelNumber) const
{
	auto levelIt = m_Levels.find(levelNumber);
	if (levelIt == m_Levels.end())
		return nullptr;

	return levelIt->second.get();
}


void LevelManager::SpawnLevel()
{
	if (!m_pCurrentLevel)
		return;

	ClearScene();


	auto uGrid = CreateGrid(m_pCurrentLevel->grid);
	m_pGridComponent = uGrid->GetComponent<Game::Components::GridComponent>();
	m_pScene->Add(uGrid);


	auto player = CreatePlayer(m_pCurrentLevel->playerStart);
	m_pScene->Add(player);
	m_pPlayer = player.get();


	for (const Game::Level::NobbinSpawner& nobbinSpawner : m_pCurrentLevel->nobbinSpawners)
	{
		auto uNobbinSpawner = CreateNobbinSpawner(nobbinSpawner);
		m_pScene->Add(uNobbinSpawner);
	}

	for (const Game::Level::Emerald& emerald : m_pCurrentLevel->emeralds)
	{
		auto uEmerald = CreateEmerald(emerald);
		m_pScene->Add(uEmerald);
	}

	for (const Game::Level::GoldBag& goldBag : m_pCurrentLevel->goldBags)
	{
		auto uGoldBag = CreateGoldBag(goldBag);
		m_pScene->Add(uGoldBag);
	}


	std::cout << "Spawned level " << m_CurrentLevelNumber << " in scene " << m_pScene->GetName() << '\n';

}

void LevelManager::ClearScene()
{
	m_pScene->RemoveAll();
}


bool LevelManager::IsLevelComplete() const
{
	if (!m_pCurrentLevel)
		return false;

	const bool collectedAllEmeralds
	{
		!m_pCurrentLevel->bMustCollectAllEmeralds ||
		m_EmeraldsCollected >= static_cast<int>(m_pCurrentLevel->emeralds.size())
	};

	const bool killedAllNobbins
	{
		!m_pCurrentLevel->bCanKillAllNobbins ||
		m_NobbinsKilled >= GetTotalNobbins()
	};


	return collectedAllEmeralds || killedAllNobbins;
}

void LevelManager::ResetLevel()
{
	// clear scene and load level
	SpawnLevel();
}

void LevelManager::ReloadLevel()
{
	EntityManager::GetInstance().RemoveAllNobbins();
	EntityManager::GetInstance().RemoveAllPlayers();


	for (const Game::Level::NobbinSpawner& nobbinSpawner : m_pCurrentLevel->nobbinSpawners)
	{
		auto uNobbinSpawner = CreateNobbinSpawner(nobbinSpawner);
		m_pScene->Add(uNobbinSpawner);
	}

	auto player = CreatePlayer(m_pCurrentLevel->playerStart);
	m_pScene->Add(player);
	m_pPlayer = player.get();

}

void Game::Managers::LevelManager::SkipLevel()
{
	m_CurrentLevelNumber++;
	ResetLevel();
}

bool LevelManager::HasLevel(int levelNumber) const
{
	auto levelIt = m_Levels.find(levelNumber);
	return levelIt != m_Levels.end();
}

int LevelManager::GetTotalNobbins() const
{
	if (!m_pCurrentLevel)
		return 0;

	int totalNobbinsToSpawn = 0;
	for (const auto& spawner : m_pCurrentLevel->nobbinSpawners)
		if (spawner.totalToSpawn > 0)
			totalNobbinsToSpawn += spawner.totalToSpawn;


	return totalNobbinsToSpawn;
}

void LevelManager::ClearAIGrid()
{
	auto test = m_pGridComponent->GetTerrainGridGraph();
	test->Clear();

}



glm::vec2 LevelManager::GridToWorld(const Game::Level::GridPosition& gridPos) const
{
	if (!m_pGridComponent)
		std::abort();

	return m_pGridComponent->GridToWorld({ gridPos.column, gridPos.row });
}

std::shared_ptr<bae::GameObject> LevelManager::CreateGrid(const Game::Level::Grid& grid) const
{
	auto uGrid = std::make_shared<bae::GameObject>("Grid");
	uGrid->SetWorldLocation({ 0, 54 }); // yep, magic numbers

	uGrid->AddComponent<Game::Components::GridComponent>(*uGrid, grid.columns, grid.rows,
		grid.cellSize, grid.bIsDirectionalGraph, grid.bIsConnectedDiagonally, grid.costStraight,
		grid.costDiagonally);

	return uGrid;
}

std::shared_ptr<bae::GameObject> LevelManager::CreatePlayer(const Game::Level::GridPosition& pos) const
{
	auto player = std::make_shared<bae::GameObject>("Digger");
	player->AddComponent<Game::Entities::DiggerComponent>(*player);
	player->SetWorldLocation(GridToWorld(pos));

	return player;
}

std::shared_ptr<bae::GameObject> LevelManager::CreateEmerald(const Game::Level::Emerald& emerald) const
{
	auto uEmerald = std::make_shared<bae::GameObject>("Emerald");
	uEmerald->AddComponent<Game::Entities::EmeraldComponent>(*uEmerald);
	uEmerald->SetWorldLocation(GridToWorld(emerald.position));

	return uEmerald;
}

std::shared_ptr<bae::GameObject> LevelManager::CreateGoldBag(const Game::Level::GoldBag& goldBag) const
{
	auto uGoldBag = std::make_shared<bae::GameObject>("GoldBag");
	uGoldBag->AddComponent<Game::Entities::GoldBagComponent>(*uGoldBag);
	uGoldBag->SetWorldLocation(GridToWorld(goldBag.position));

	return uGoldBag;
}

std::shared_ptr<bae::GameObject> LevelManager::CreateBonus(const Game::Level::Bonus& bonus) const
{
	auto uBonus = std::make_shared<bae::GameObject>("Bonus");
	uBonus->AddComponent<Game::Entities::BonusComponent>(*uBonus, bonus.bonusModeScore, bonus.bonusModeTime);

	return uBonus;
}

std::shared_ptr<bae::GameObject> LevelManager::CreateNobbinSpawner(const Game::Level::NobbinSpawner& spawner) const
{
	auto nobbinSpawner = std::make_shared<bae::GameObject>("NobbinSpawner");
	nobbinSpawner->AddComponent<Game::Entities::NobbinSpawnerComponent>(*nobbinSpawner, *m_pScene, spawner.spawnDelay,
		spawner.maxNobbins, spawner.totalToSpawn, spawner.bonus.bonusModeScore, spawner.bonus.bonusModeTime);
	nobbinSpawner->SetWorldLocation(GridToWorld(spawner.position));

	return nobbinSpawner;
}


