#include "GridComponent.h"

#include <SDL.h>

#include "Core/Renderer.h"
#include "Components/SpriteComponent.h"
#include "Core/Utils.h"
#include "Graphs/GraphConnection.h"
#include "Graphs/AStar.h"



using namespace Game;
namespace bu = bae::Utils;

// 63 pixels circle spawn

GridComponent::GridComponent(bae::GameObject& owner, int columns, int rows, const glm::ivec2& cellSize, bool isDirectionalGraph,
	bool isConnectedDiagnally, float costStraight, float costDiagonally) :
	bae::Component(owner),
	m_TerrainGridGraph{ }
{
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(0, 296, 384, 4), 8, 8, glm::ivec2{ 8, 0 });

	m_Owner->GetComponent<bae::SpriteComponent>()->m_bIsCenteredAtPosition = false;

	//SDL_Rect(0, 296, 384, 24), 8, 8, glm::ivec2{ 8, 0 });


	SDL_GetWindowSize(bae::Renderer::GetInstance().GetSDLWindow(), &m_WindowWidth, &m_WindowHeight);

	// for spritesheet
	m_Owner->SetWorldScale({ 3.f, 3.f });


	m_Owner->AddLocation({ 30, 9, 0 });

	m_TerrainGridGraph = std::make_unique<AI::TerrainGridGraph>(
		glm::vec2{ m_Owner->GetWorldLocation().x, m_Owner->GetWorldLocation().y },
		columns, rows, cellSize, isDirectionalGraph, isConnectedDiagnally, costStraight, costDiagonally);

	m_TerrainGridGraph->SetNodeTerrainType(5, Game::AI::TerrainType::Ground);
	m_TerrainGridGraph->m_bRenderConnections = true;
	m_TerrainGridGraph->m_bRenderNodes = true;


	m_Owner->AddLocation({ -30, -9.f, 0 });

}


void Game::GridComponent::Render() const
{

	const int widthSprite{ static_cast<int>(m_Owner->GetWorldScale().x * 20.f) };
	const int heightSprite{ static_cast<int>(m_Owner->GetWorldScale().y * 4.f) };


	for (int i{}; i < m_WindowWidth; i += widthSprite)
	{
		m_Owner->AddLocation({ i, 0, 0 });

		for (int j{}; j < m_WindowHeight; j += heightSprite)
		{
			m_Owner->AddLocation({ 0, j, 0 });
			m_Owner->GetComponent<bae::SpriteComponent>()->Render();
			m_Owner->AddLocation({ 0, -j, 0 });
		}

		m_Owner->AddLocation({ -i, 0, 0 });
	}


	/*
		for (int i{}; i < 640; +i)
			m_Owner->GetComponent<bae::SpriteComponent>()->Render();
	*/


	for (auto pNode : m_TerrainGridGraph->GetAllNodes())
		pNode->Render();


	m_TerrainGridGraph->Render();

}

void Game::GridComponent::Update()
{



}




