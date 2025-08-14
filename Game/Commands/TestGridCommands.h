#pragma once

#include <iostream>

#include <SDL_mouse.h>

#include "Commands/GameActorCommand.h"
#include "../Components/AIComponent.h"


namespace Game::Commands
{

	class TestGridCommand final : public bae::GameActorCommand
	{
	public:
		TestGridCommand(bae::GameObject& actor) :
			bae::GameActorCommand(actor)
		{
		};


		virtual void Execute() override
		{

			auto aiComp = GetActor()->GetComponent<Game::Components::AIComponent>();
			if (!aiComp)
				return;

			int x;
			int y;

			SDL_GetMouseState(&x, &y);
			aiComp->SetPath({ x, y });

		}


	private:


	};
}



