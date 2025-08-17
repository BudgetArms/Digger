#pragma once

#include <unordered_map>

#include "Components/Component.h"
#include "Core/Observer.h"
#include "Core/Scene.h"
#include "Core/EventTypes.h"
#include "Singletons/Singleton.h"


namespace bae
{
	class Scene;
	class Subject;
}

namespace Game::Managers
{
	class EntityManager : public bae::Singleton<EntityManager>, public bae::Observer
	{
	public:


		void LateUpdate();

		virtual void Notify(bae::EventType event, bae::Subject* subject) override;

		std::vector<bae::GameObject*> GetDiggers() { return m_Diggers; }

		void RemoveAllPlayers();
		void RemoveAllNobbins();


	private:
		friend bae::Singleton<EntityManager>;
		EntityManager();
		~EntityManager() = default;

		void HandleEvents();
		void HandleCollisions();


		std::vector<bae::GameObject*> m_Nobbins{};
		std::vector<bae::GameObject*> m_Diggers{};

		bae::Scene* m_CurrentScene{};
		std::unordered_map<bae::EventType, bae::Subject*> m_SubjectEvents{}; // I wanted to use ringbuffer, but no time


	};
}


