#include "DiggerComponent.h"

#include <SDL_rect.h>

#include "Core/Renderer.h"
#include "Managers/ResourceManager.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Core/Utils.h"

#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/ScoreComponent.h"


using namespace Game::Entities;
namespace bu = bae::Utils;


DiggerComponent::DiggerComponent(bae::GameObject& owner) :
	bae::Component(owner),
	m_LivesTexture{ std::make_unique<bae::Texture2D>("Resources/Textures/SpriteSheet.png") },
	m_TextTexture{ std::make_unique<bae::Text2D>(" ") }
{
	m_Owner->AddComponent<Game::Components::HealthComponent>(*m_Owner, 100.f);
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(0, 0, 584, 128), 12, 48, glm::ivec2{ 8, 8 });

	m_Owner->AddComponent<Game::Components::ScoreComponent>(*m_Owner);
	auto pScoreComp = m_Owner->GetComponent<Game::Components::ScoreComponent>();

	pScoreComp->AddScore(5);

	m_TextTexture->SetText(std::to_string(pScoreComp->GetScore()));
	m_TextTexture->m_Position = { 100, 20 };


	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

	m_Owner->SetWorldScale({ 3.f, 3.f });
}


void DiggerComponent::Update()
{
	auto pScoreComp = m_Owner->GetComponent<Game::Components::ScoreComponent>();

	m_TextTexture->SetText(std::to_string(pScoreComp->GetScore()));
	m_TextTexture->Update();
}

void DiggerComponent::Render() const
{
	const int offset{ 4 };
	for (int i{}; i < m_Lives; ++i)
	{
		bae::Renderer::GetInstance().RenderTexture(*m_LivesTexture.get(), false, m_LiveSrcRect,
			SDL_Rect(static_cast<int>(m_LivesStartPosition.x + i * (m_LiveSrcRect.w + offset) * m_Owner->GetWorldScale().x),
				static_cast<int>(m_LivesStartPosition.y), static_cast<int>(m_LiveSrcRect.w), static_cast<int>(m_LiveSrcRect.h)),
			0.f, m_Owner->GetWorldScale());

	}



	m_TextTexture->Render();

	//if (auto* pSpriteComp = m_Owner->GetComponent<bae::SpriteComponent>())
	{
		//pSpriteComp->Render();

		/*
		m_Owner->AddLocation({ 200, 0, 0 });
		pSpriteComp->NextSprite();

		pSpriteComp->Render();
		m_Owner->AddLocation({ -200, 0, 0 });
		pSpriteComp->PreviousSprite();
		*/


	}
}


