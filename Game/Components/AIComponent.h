#pragma once

#include <variant>

#include <glm.hpp>

#include "Components/Component.h"
#include "Graphs/GraphNode.h"
#include "Core/GameObject.h"


namespace Game::AI
{
	class TerrainGridGraph;
}

namespace Game::Components
{
	class AIComponent : public bae::Component
	{
	public:
		AIComponent(bae::GameObject& owner);
		~AIComponent() = default;


		void Update();
		void Render() const;

		void SetPath(const glm::vec2& position);
		void SetPath(bae::GameObject* target);


		Game::AI::TerrainGridGraph* m_TerrainGridGraph;

		float m_Speed;


	private:
		void UpdatePath();


		std::vector<bae::Graphs::GraphNode*> m_Path{};
		std::variant<glm::vec2, bae::GameObject*> m_Target{};

		int m_CurrentIndex{};

		bool m_bNeedsUpdate{};
		bool m_bHasTarget{};


	};
}


