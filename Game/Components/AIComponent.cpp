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

/*/
AIComponent::~AIComponent()
{


}
//*/


void AIComponent::Update()
{
	if (m_CurrentIndex >= m_Path.size())
		return;

	bae::Graphs::GraphNode* targetNode = m_Path[m_CurrentIndex];
	glm::vec2 targetPos = targetNode->GetPosition();

	glm::vec2 pos = { m_Owner->GetWorldLocation().x, m_Owner->GetWorldLocation().y };
	glm::vec2 dir = targetPos - pos;
	float dist = glm::length(dir);

	if (dist < 0.1f)
	{
		++m_CurrentIndex;
		return;
	}

	dir /= dist;
	pos += dir * 100.f * bae::GameTime::GetInstance().GetDeltaTime();

	m_Owner->SetWorldLocation({ pos.x, pos.y, 0 });
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

	const glm::vec3 startPos = m_Owner->GetWorldLocation();

	bae::Graphs::GraphNode* pStartNode = m_TerrainGridGraph->GetNodeAtPosition({ startPos.x, startPos.y });
	bae::Graphs::GraphNode* pEndNode = m_TerrainGridGraph->GetNodeAtPosition(position);

	if (!pStartNode || !pEndNode)
	{
		std::cout << GetFunctionName() << " Start- or EndNode is invalid" << '\n';
		return;
	}

	auto pathFinder = bae::Graphs::AStar(m_TerrainGridGraph, bae::Graphs::HeuristicFunctions::Chebyshev);
	m_Path = pathFinder.FindPath(pStartNode, pEndNode);
	m_CurrentIndex = 0;



}


