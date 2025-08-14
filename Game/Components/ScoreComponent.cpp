#include "ScoreComponent.h"


using namespace Game::Components;


ScoreComponent::ScoreComponent(bae::GameObject& owner) :
	bae::Component(owner),
	bae::Subject(owner),
	m_Score{}
{
}


void ScoreComponent::SetScore(int score)
{
	if (score < 0)
		return;

	m_Score = score;
	NotifyObservers(bae::EventType::PLAYER_SCORE_CHANGE);
}

void ScoreComponent::AddScore(int score)
{
	m_Score += score;
	NotifyObservers(bae::EventType::PLAYER_SCORE_CHANGE);
};

void ScoreComponent::SubtractScore(int score)
{
	m_Score -= score;
	NotifyObservers(bae::EventType::PLAYER_SCORE_CHANGE);
};


