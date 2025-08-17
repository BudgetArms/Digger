#include "NobbinSpawnerComponent.h"

#include "Singletons/GameTime.h"

#include "../Entities/NobbinComponent.h"
#include "../Entities/BonusComponent.h"
#include "../Components/HitboxComponent.h"


using namespace Game::Entities;


NobbinSpawnerComponent::NobbinSpawnerComponent(bae::GameObject& owner, bae::Scene& scene, float spawnDelay,
	int maxNobbinAtOnce, int totalNobbinsToSpawn, float bonusModeTime, float bonusModeScore) :

	bae::Component(owner),
	m_Scene{ &scene },
	m_SpawnDelay{ spawnDelay },
	m_ElapsedSec{},
	m_NrSpawnedNobbins{},
	m_MaxNobbinsAtOnce{ maxNobbinAtOnce },
	m_TotalNobbinsToSpawn{ totalNobbinsToSpawn },
	m_BonusModeTime{ bonusModeTime },
	m_BonusModeScore{ bonusModeScore }
{
	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 30, 30, false);
	m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;
	spawnDelay;
}


void NobbinSpawnerComponent::LateUpdate()
{
	if (!m_Scene)
		return;

	if (m_NrSpawnedNobbins >= m_TotalNobbinsToSpawn)
		return;

	m_ElapsedSec += bae::GameTime::GetInstance().GetDeltaTime();

	if (m_ElapsedSec < m_SpawnDelay)
		return;


	m_ElapsedSec = 0.f;
	++m_NrSpawnedNobbins;

	SpawnNobbin();

	std::cout << "nrNobbins: " << m_NrSpawnedNobbins << '\n';

	// if last Nobbin spawn, spawn Bonus
	if (m_NrSpawnedNobbins == m_TotalNobbinsToSpawn)
		SpawnBonus();

}


void NobbinSpawnerComponent::SpawnNobbin()
{
	auto test = "Nobbin" + std::to_string(m_NrSpawnedNobbins);
	//auto nobbin = std::make_shared<bae::GameObject>("Nobbin");
	auto nobbin = std::make_shared<bae::GameObject>(test);
	nobbin->AddComponent<Game::Entities::NobbinComponent>(*nobbin);
	nobbin->SetWorldLocation(m_Owner->GetWorldLocation());

	m_Scene->Add(nobbin);
}

void NobbinSpawnerComponent::SpawnBonus()
{
	auto bonus = std::make_shared<bae::GameObject>("Bonus");
	bonus->AddComponent<Game::Entities::BonusComponent>(*bonus, m_BonusModeTime, m_BonusModeScore);
	bonus->SetWorldLocation(m_Owner->GetWorldLocation());

	m_Scene->Add(bonus);
}


