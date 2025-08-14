#pragma once

#include "Components/Component.h"
#include "Core/Scene.h"


namespace Game::Components
{
	class EntityManagerComponent : public bae::Component
	{
	public:
		EntityManagerComponent(bae::GameObject& owner, bae::Scene* currentScene);


		void LateUpdate() override;


	private:
		void HandleCollisions();


		bae::Scene* m_CurrentScene;


	};
}


