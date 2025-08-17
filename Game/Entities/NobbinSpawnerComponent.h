#pragma once

#include "Components/Component.h"
#include "Core/Scene.h"


namespace Game::Entities
{
	class NobbinSpawnerComponent : public bae::Component
	{
	public:
		NobbinSpawnerComponent(bae::GameObject& owner, bae::Scene& scene, float spawnDelay,
			int maxNobbinAtOnce, int totalNobbinsToSpawn, float bonusModeTime, float bonusModeScore);

		void LateUpdate() override;


	private:
		void SpawnNobbin();
		void SpawnBonus();


		bae::Scene* m_Scene;

		const float m_SpawnDelay;
		float m_ElapsedSec;

		int m_NrSpawnedNobbins;
		const int m_MaxNobbinsAtOnce;
		const int m_TotalNobbinsToSpawn;

		float m_BonusModeTime;
		float m_BonusModeScore;


	};
}


