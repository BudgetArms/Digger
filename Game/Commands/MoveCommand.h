#pragma once

#include "Core/HelperFunctions.h"
#include "Core/GameObject.h"
#include "Commands/GameActorCommand.h"

#include "../Entities/DiggerComponent.h"
#include "../Components/MoveComponent.h"
#include "../Base/DirectionEnum.h"


namespace Game::Commands
{
	class MoveCommand : public bae::GameActorCommand
	{
	public:
		MoveCommand(bae::GameObject& actor, Game::Direction direction) :
			bae::GameActorCommand(actor),
			m_Direction{ direction },
			m_pMoveComp{}
		{
			m_pMoveComp = GetActor()->GetComponent<Game::Components::MoveComponent>();
		};


		void Execute() override
		{
			m_pMoveComp->MoveInDirection(m_Direction);
		}


	private:
		Game::Direction m_Direction;
		Game::Components::MoveComponent* m_pMoveComp;


	};
}


