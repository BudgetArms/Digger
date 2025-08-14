#pragma once

#include "Components/Component.h"
#include "Core/Subject.h"


namespace Game::Components
{
	class ScoreComponent final : public bae::Component, bae::Subject
	{
	public:
		ScoreComponent(bae::GameObject& owner);


		int GetScore() const { return m_Score; };
		void SetScore(int score);
		void AddScore(int score);
		void SubtractScore(int score);


	private:
		int m_Score{};


	};
}


