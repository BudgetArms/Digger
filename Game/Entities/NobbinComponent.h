#pragma once

#include "Components/Component.h"
#include "Components/SpriteComponent.h"


namespace Game::Entities
{
	class NobbinComponent : public bae::Component
	{
	public:
		NobbinComponent(bae::GameObject& owner);


		void Update() override;


		void ChangeSpeed(float speed);


	private:
		void SwitchAnimation();

		bae::GameObject* m_Player;
		bae::SpriteComponent* m_SpriteComp;


		float m_DelayMovingElapsedSec{};
		const float m_DelayStartMoving{ 2.f };

		float m_AnimationElapsedSec{};
		float m_AnimationDelay{ 0.2f };

		bool m_bStartedMoving{};


	};


	enum class NobbinSprites
	{
		LooksDownLeft,
		LooksDownRight,
		LooksUpRight,
		Death
	};

	enum class HobbinSprites
	{
		MovingRightAnim0 = 4,
		MovingRightAnim1,
		MovingRightAnim2,
		MovingRightAnim3,

		MovingLeftAnim0,
		MovingLeftAnim1,
		MovingLeftAnim2,
		MovingLeftAnim3,
	};


}


