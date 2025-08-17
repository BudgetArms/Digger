#include "EntityManager.h"

#include <iostream>

#include "Core/Utils.h"

#include "../Base/LevelManager.h"
#include "../Components/HitboxComponent.h"
#include "../Components/PickupComponent.h"
#include "../Entities/BonusComponent.h"
#include "../Entities/DiggerComponent.h"
#include "../Entities/NobbinComponent.h"
#include "../Components/HealthComponent.h"


using namespace Game::Managers;


EntityManager::EntityManager()
{

}


void EntityManager::LateUpdate()
{
	HandleCollisions();
	HandleEvents();
}


void EntityManager::Render() const
{
	bae::Utils::DrawCircle({ 100, 100 }, 100, bae::Utils::Color::Black);
	for (auto rect : m_Holes)
		bae::Utils::FillRect(rect, bae::Utils::Color::Black);
}

void EntityManager::Notify(bae::EventType event, bae::Subject* subject)
{
	m_SubjectEvents.insert(std::pair(event, subject));

}

void EntityManager::RemoveAllPlayers()
{

	for (auto& uObject : m_CurrentScene->GetObjects())
	{
		if (!uObject)
			continue;

		if (uObject->HasComponent<Game::Entities::DiggerComponent>())
			uObject->Destroy();

	}

}

void EntityManager::RemoveAllNobbins()
{

	for (auto& uObject : m_CurrentScene->GetObjects())
	{
		if (!uObject)
			continue;

		if (uObject->HasComponent<Game::Entities::NobbinComponent>())
			uObject->Destroy();

	}

}


void EntityManager::HandleEvents()
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
				Game::Managers::LevelManager::GetInstance().ReloadLevel();

			}
			break;
			default:
				break;
		}


	}

	m_SubjectEvents.clear();

}

void EntityManager::HandleCollisions()
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
		auto playerHitbox = uPlayer->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

		// Enemies
		for (auto& uEnemy : uEnemies)
		{
			auto enemyHitbox = uEnemy->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(playerHitbox, enemyHitbox))
			{
				if (auto playerHealthComp = uPlayer->GetComponent<Game::Components::HealthComponent>())
					playerHealthComp->Damage(1);
			}

		}

		// Collectibles
		for (auto& uCollectible : uCollectibles)
		{
			auto collectibleHitbox = uCollectible->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(playerHitbox, collectibleHitbox))
			{
				uCollectible->GetComponent<Game::Components::PickupComponent>()->Interact(*uPlayer.get());

			}
		}

	}



	for (auto& uEnemy : uEnemies)
	{
		auto enemyHitbox = uEnemy->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

		// Collectibles
		for (auto& uCollectible : uCollectibles)
		{
			auto collectibleHitbox = uCollectible->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(enemyHitbox, collectibleHitbox))
			{


			}
		}

		// Projectile
		for (auto& uProjectile : uProjectiles)
		{
			auto projectileHitbox = uProjectile->GetComponent<Game::Components::HitboxComponent>()->GetHitbox();

			if (bae::Utils::IsOverlapping(enemyHitbox, projectileHitbox))
			{
				if (auto enemyHealthComp = uEnemy->GetComponent<Game::Components::HealthComponent>())
					enemyHealthComp->Damage(1);
			}
		}


	}



}


