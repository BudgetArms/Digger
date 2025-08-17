#pragma once

#include "Core/GameObject.h"

/*
namespace bae
{
	class GameObject;
}
*/

namespace Game::States
{
	class DiggerState
	{
	public:
		virtual void OnEnter(bae::GameObject& owner) = 0;
		virtual void OnExit() = 0;

		virtual void Update() = 0;

		DiggerState() = default;
		virtual ~DiggerState() = default;
	protected:

		bae::GameObject* m_Owner{};


	};
}


