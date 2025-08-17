#pragma once

#include "Components/Component.h"

#include "../Base/EntityManager.h"


namespace Game::Components
{
	class EntityManagerComponent : public bae::Component
	{
	public:
		EntityManagerComponent(bae::GameObject& owner) :
			bae::Component(owner)
		{
			Game::Managers::EntityManager::GetInstance();
		}

		void LateUpdate() override
		{
			Game::Managers::EntityManager::GetInstance().LateUpdate();
		}


	};
}


