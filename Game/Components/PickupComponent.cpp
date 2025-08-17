#include "PickupComponent.h"

#include <iostream>

#include "../Components/ScoreComponent.h"


using namespace Game::Components;


PickupComponent::PickupComponent(bae::GameObject& owner, int scoreOnPickup) :
	bae::Component(owner),
	m_ScoreOnPickup{ scoreOnPickup }
{
}

void PickupComponent::Interact(bae::GameObject& player)
{
	auto scoreComp = player.GetComponent<Game::Components::ScoreComponent>();
	scoreComp->AddScore(m_ScoreOnPickup);
	m_Owner->Destroy();
}


