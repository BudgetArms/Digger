#pragma once

#include "Components/Component.h"


namespace Game::Entities
{
	class NobbinComponent : public bae::Component
	{
	public:
		NobbinComponent(bae::GameObject& owner);


		void Update() override;
		void Render() const override;


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


