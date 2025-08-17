#include "EntityManagerComponent.h"

#include <iostream>

#include "Core/Utils.h"

#include "../Base/LevelManager.h"
#include "../Components/HitboxComponent.h"
#include "../Components/PickupComponent.h"
#include "../Entities/BonusComponent.h"
#include "../Entities/DiggerComponent.h"
#include "../Entities/NobbinComponent.h"
#include "../Components/HealthComponent.h"


using namespace Game::Components;


EntityManagerComponent::EntityManagerComponent(bae::GameObject& owner, bae::Scene& currentScene) :
	bae::Component(owner),
	m_CurrentScene{ &currentScene },
	m_SubjectEvents{}
{
}


void EntityManagerComponent::LateUpdate()
{


	HandleCollisions();
	HandleEvents();
}

void EntityManagerComponent::Notify(bae::EventType event, bae::Subject* subject)
{
	m_SubjectEvents.insert(std::pair(event, subject));

}

void EntityManagerComponent::RemoveAllPlayers()
{

	for (auto& uObject : m_CurrentScene->GetObjects())
	{
		if (!uObject)
			continue;

		if (uObject->HasComponent<Game::Entities::DiggerComponent>())
			uObject->Destroy();

	}

}

void EntityManagerComponent::RemoveAllNobbins()
{

	for (auto& uObject : m_CurrentScene->GetObjects())
	{
		if (!uObject)
			continue;

		if (uObject->HasComponent<Game::Entities::NobbinComponent>())
			uObject->Destroy();

	}

}


void EntityManagerComponent::HandleEvents()
{
	for (auto& [eventType, pSubject] : m_SubjectEvents)
	{
		switch (eventType)
		{
			case bae::EventType::LEVEL_STARTED:
				break;
			case bae::EventType::LEVEL_WON:
				break;
			case bae::EventType::LEVEL_LOST:
				break;
			case bae::EventType::PLAYER_HEALTH_CHANGE:
				break;
			case bae::EventType::PLAYER_SCORE_CHANGE:
				break;
			case bae::EventType::PLAYER_DIED:
			{
				RemoveAllNobbins();
				RemoveAllPlayers();
				Game::Level::LevelManager::GetInstance().ReloadLevel();

			}
			break;
			default:
				break;
		}


	}

	m_SubjectEvents.clear();

}

void EntityManagerComponent::HandleCollisions()
{
	if (!m_CurrentScene)
		return;

	std::vector<std::shared_ptr<bae::GameObject>> uPlayers;
	std::vector<std::shared_ptr<bae::GameObject>> uEnemies;
	std::vector<std::shared_ptr<bae::GameObject>> uCollectibles;
	std::vector<std::shared_ptr<bae::GameObject>> uProjectiles;


	for (auto& uObject : m_CurrentScene->GetObjects())
	{
		if (!uObject)
			continue;

		if (!uObject->HasComponent<Game::Components::HitboxComponent>())
			continue;

		if (uObject->HasComponent<Game::Entities::DiggerComponent>())
			uPlayers.push_back(uObject);
		else if (uObject->HasComponent<Game::Entities::NobbinComponent>())
			uEnemies.push_back(uObject);
		else if (uObject->HasComponent<Game::Components::PickupComponent>())
			uCollectibles.push_back(uObject);

	}

	// Handle Player Collisions
	for (auto& uPlayer : uPlayers)
	{
		auto playerHitbox = uPlayer->GetComponent<HitboxComponent>()->GetHitbox();

		// Enemies
		for (auto& uEnemy : uEnemies)
		{
			auto enemyHitbox = uEnemy->GetComponent<HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(playerHitbox, enemyHitbox))
			{
				if (auto playerHealthComp = uPlayer->GetComponent<Game::Components::HealthComponent>())
					playerHealthComp->Damage(1);
			}

		}

		// Collectibles
		for (auto& uCollectible : uCollectibles)
		{
			auto collectibleHitbox = uCollectible->GetComponent<HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(playerHitbox, collectibleHitbox))
			{

			}
		}

	}



	for (auto& uEnemy : uEnemies)
	{
		auto enemyHitbox = uEnemy->GetComponent<HitboxComponent>()->GetHitbox();

		// Collectibles
		for (auto& uCollectible : uCollectibles)
		{
			auto collectibleHitbox = uCollectible->GetComponent<HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(enemyHitbox, collectibleHitbox))
			{


			}
		}

		// Projectile
		for (auto& uProjectile : uProjectiles)
		{
			auto projectileHitbox = uProjectile->GetComponent<HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(enemyHitbox, projectileHitbox))
			{
				if (auto enemyHealthComp = uEnemy->GetComponent<Game::Components::HealthComponent>())
					enemyHealthComp->Damage(1);
			}
		}


	}



}


