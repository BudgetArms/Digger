#pragma once

#include "Commands/GameActorCommand.h"
#include "Core/GameObject.h"
#include "Components/TransformComponent.h"
#include "Singletons/GameTime.h"


namespace Game::Commands
{
	class TestMoveCommand final : public bae::GameActorCommand
	{
	public:
		TestMoveCommand(bae::GameObject& actor, const glm::vec2& direction, float speed = 100.f) :
			bae::GameActorCommand(actor),
			m_Direction{ direction },
			m_Speed{ speed }
		{
			if (glm::length(direction) != 0)
				m_Direction /= glm::length(direction);
		};


		float GetSpeed() const { return m_Speed; }
		void SetSpeed(float speed) { m_Speed = speed; }

		virtual void Execute() override
		{
			auto* transform = GetActor()->GetComponent<bae::TransformComponent>();
			if (!transform)
				return;

			transform->AddLocation({ m_Speed * m_Direction * bae::GameTime::GetInstance().GetDeltaTime() });
		}


	private:
		glm::vec2 m_Direction;
		float m_Speed;


	};
}


