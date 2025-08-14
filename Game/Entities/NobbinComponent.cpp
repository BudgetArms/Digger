#include "NobbinComponent.h"

#include "Core/Utils.h"
#include "Components/SpriteComponent.h"

#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/AIComponent.h"


using namespace Game::Entities;
namespace bu = bae::Utils;


NobbinComponent::NobbinComponent(bae::GameObject& owner) :
	bae::Component(owner)
{
	m_Owner->AddComponent<Game::Components::HealthComponent>(*m_Owner, 100.f);
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(0, 136, 584, 24), 12, 12, glm::ivec2{ 8, 0 });

	m_Owner->AddComponent<Game::Components::AIComponent>(*m_Owner);

	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

}


void NobbinComponent::Update()
{

}

void NobbinComponent::Render() const
{
	//const auto& pos = m_Owner->GetWorldLocation();
	//const auto& scale = m_Owner->GetWorldScale();

	//bu::FillEllipse({ pos.x, pos.y }, static_cast<int>(2 * scale.x), static_cast<int>(2 * scale.y), { bu::Color::Green, 0.75f });


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


