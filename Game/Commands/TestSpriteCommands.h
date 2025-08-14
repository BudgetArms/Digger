#pragma once

#include <iostream>

#include "Commands/GameActorCommand.h"
#include "Components/SpriteComponent.h"


namespace Game::Commands
{
	enum class TestSpriteAction
	{
		NextSprite,
		PreviousSprite,
	};

	class TestSpriteCommand final : public bae::GameActorCommand
	{
	public:
		TestSpriteCommand(bae::GameObject& actor, TestSpriteAction spriteAction) :
			bae::GameActorCommand(actor),
			m_SpriteAction{ spriteAction }
		{
		};


		virtual void Execute() override
		{
			auto* spriteComponent = GetActor()->GetComponent<bae::SpriteComponent>();
			if (!spriteComponent)
				return;

			switch (m_SpriteAction)
			{
				case TestSpriteAction::NextSprite:
					spriteComponent->NextSprite();
					break;
				case TestSpriteAction::PreviousSprite:
					spriteComponent->PreviousSprite();
					break;
			}
		}


	private:
		TestSpriteAction m_SpriteAction;


	};
}


