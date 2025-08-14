#include "GoldBagComponent.h"

#include "Core/Utils.h"
#include "Components/SpriteComponent.h"

#include "../Components/HitboxComponent.h"


using namespace Game::Entities;


GoldBagComponent::GoldBagComponent(bae::GameObject& owner) :
	bae::Component(owner)
{
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(48, 168, 336, 24), 7, 7, glm::ivec2{ 8, 0 });

	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

}


