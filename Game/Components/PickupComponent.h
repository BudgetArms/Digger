#pragma once

#include "Components/Component.h"


namespace Game::Components
{
	class PickupComponent : public bae::Component
	{
	public:
		PickupComponent(bae::GameObject& owner, int scoreOnPickup);


		int GetScoreOnPickup() const { return m_ScoreOnPickup; }

		void Interact() {};


	private:
		const int m_ScoreOnPickup;


	};
}


