#include "PickupComponent.h"


using namespace Game::Components;


PickupComponent::PickupComponent(bae::GameObject& owner, int scoreOnPickup) :
	bae::Component(owner),
	m_ScoreOnPickup{ scoreOnPickup }
{
}


