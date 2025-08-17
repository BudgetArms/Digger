#include "AIComponent.h"

#include "Core/HelperFunctions.h"
#include "Graphs/AStar.h"
#include "Graphs/Graph.h"
#include "Graphs/HeuristicFunctions.h"
#include "Singletons/GameTime.h"

#include "../Base/TerrainGridGraph.h"


using namespace Game::Components;


AIComponent::AIComponent(bae::GameObject& owner) :
	bae::Component(owner),
	m_TerrainGridGraph{}
{
}


void AIComponent::Update()
{
	if (!m_bHasTarget)
		return;

	if (m_bNeedsUpdate)
	{
		m_bNeedsUpdate = false;
		UpdatePath();
	}

	if (m_CurrentIndex == 2 && std::holds_alternative<bae::GameObject*>(m_Target))
		UpdatePath();

	if (m_CurrentIndex >= m_Path.size())
	{
		UpdatePath();
		return;
	}

	bae::Graphs::GraphNode* targetNode = m_Path[m_CurrentIndex];
	glm::vec2 targetPos = targetNode->GetPosition();

	glm::vec2 position = m_Owner->GetWorldLocation();
	glm::vec2 dir = targetPos - position;
	const float distance = glm::length(dir);


	if (distance < 1.f)
	{
		++m_CurrentIndex;
		return;
	}

	dir /= distance;
	position += dir * m_Speed * bae::GameTime::GetInstance().GetDeltaTime();

	m_Owner->SetWorldLocation(position);


}

void AIComponent::Render() const
{
	bae::Utils::FillCircle({ 200, 200 }, 10, bae::Utils::Color::Blue);
	//if (m_TerrainGridGraph)
		//m_TerrainGridGraph->Render();

}



void AIComponent::SetPath(const glm::vec2& position)
{
	if (!m_TerrainGridGraph)
		return;

	m_Target = position;
	m_bNeedsUpdate = true;
	m_bHasTarget = true;
}

void AIComponent::SetPath(bae::GameObject* target)
{
	if (!m_TerrainGridGraph)
		return;

	m_Target = target;
	m_bNeedsUpdate = true;
	m_bHasTarget = true;
}


void AIComponent::UpdatePath()
{
	if (!m_TerrainGridGraph)
		return;

	const glm::vec2 startPos = m_Owner->GetWorldLocation();

	bae::Graphs::GraphNode* pStartNode = m_TerrainGridGraph->GetNodeAtPosition(startPos);
	bae::Graphs::GraphNode* pEndNode{};

	if (auto targetPos = std::get_if<glm::vec2>(&m_Target))
	{
		pEndNode = m_TerrainGridGraph->GetNodeAtPosition(*targetPos);
	}
	else if (auto target = std::get_if<bae::GameObject*>(&m_Target))
	{
		if (*target)
			pEndNode = m_TerrainGridGraph->GetNodeAtPosition((*target)->GetWorldLocation());
	}


	if (!pStartNode || !pEndNode)
	{
		std::cout << GetFunctionName() << " Start- or EndNode is invalid" << '\n';
		return;
	}

	auto pathFinder = bae::Graphs::AStar(m_TerrainGridGraph, bae::Graphs::HeuristicFunctions::Chebyshev);
	m_Path = pathFinder.FindPath(pStartNode, pEndNode);
	m_CurrentIndex = 0;

}


