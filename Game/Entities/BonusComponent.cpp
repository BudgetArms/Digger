#include "BonusComponent.h"

#include "Core/Utils.h"
#include "Components/SpriteComponent.h"

#include "../Components/HitboxComponent.h"


using namespace Game::Entities;


BonusComponent::BonusComponent(bae::GameObject& owner, float modeTime, float score) :
	bae::Component(owner),
	m_ModeTime{ modeTime },
	m_Score{ score }
{
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(392, 168, 40, 24), 1, 1);

	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

	m_Owner->SetWorldScale({ 3.f, 3.f });
}


