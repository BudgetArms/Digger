#include "EmeraldComponent.h"

#include "Core/Utils.h"
#include "Components/SpriteComponent.h"

#include "../Components/HitboxComponent.h"
#include "../Components/PickupComponent.h"


using namespace Game::Entities;


EmeraldComponent::EmeraldComponent(bae::GameObject& owner) :
	bae::Component(owner)
{
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(8, 168, 40, 24), 1, 1);

	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

	m_Owner->AddComponent<Game::Components::PickupComponent>(*m_Owner, 100);

	m_Owner->SetWorldScale({ 3.f, 3.f });
}


