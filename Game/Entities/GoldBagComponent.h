#pragma once

#include <glm.hpp>

#include "Components/Component.h"


namespace Game::Entities
{
	class GoldBagComponent : public bae::Component
	{
	public:
		GoldBagComponent(bae::GameObject& owner);


	};

	enum class GoldBagAnimations
	{
		Idle,
		Tick1,
		Tick2,
		Falling,
		Crumble1,
		Crumble2,
		Rubble,
	};

}