#pragma once

#include <glm.hpp>

#include "Components/Component.h"
#include "Graphs/GraphNode.h"


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


		Game::AI::TerrainGridGraph* m_TerrainGridGraph;


	private:
		std::vector<bae::Graphs::GraphNode*> m_Path;

		int m_CurrentIndex{};


	};
}


