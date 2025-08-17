#pragma once

#include "Components/Component.h"


namespace Game::Entities
{
	class BonusComponent : public bae::Component
	{
	public:
		BonusComponent(bae::GameObject& owner, float modeTime, float score);


	private:
		const float m_ModeTime;
		const float m_Score;


	};
}


