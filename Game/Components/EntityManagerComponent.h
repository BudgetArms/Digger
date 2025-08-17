#pragma once

#include <unordered_map>

#include "Components/Component.h"
#include "Core/Observer.h"
#include "Core/Scene.h"
#include "Core/EventTypes.h"


namespace bae
{
	class Scene;
	class Subject;
}

namespace Game::Components
{
	class EntityManagerComponent : public bae::Component, public bae::Observer
	{
	public:
		EntityManagerComponent(bae::GameObject& owner, bae::Scene& currentScene);


		void LateUpdate() override;

		virtual void Notify(bae::EventType event, bae::Subject* subject) override;

		std::vector<bae::GameObject*> GetDiggers() { return m_Diggers; }

		void RemoveAllPlayers();
		void RemoveAllNobbins();


	private:
		void HandleEvents();
		void HandleCollisions();


		std::vector<bae::GameObject*> m_Nobbins;
		std::vector<bae::GameObject*> m_Diggers;

		bae::Scene* m_CurrentScene;
		std::unordered_map<bae::EventType, bae::Subject*> m_SubjectEvents; // I wanted to use ringbuffer, but no time


	};
}


