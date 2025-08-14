#include "HealthComponent.h"

#include "Core/HelperFunctions.h"


using namespace Game::Components;


HealthComponent::HealthComponent(bae::GameObject& owner, float maxHealth) :
	bae::Component(owner),
	bae::Subject(owner),
	m_Health{ maxHealth },
	m_MaxHealth{ maxHealth }
{
	if (m_Health < 0.f)
		throw std::runtime_error(GetFunctionName() + std::string("Health is negative"));

}


void HealthComponent::Damage(float damage)
{
	if (m_bIsInvincible)
		return;

	m_Health -= damage;

	if (m_Health <= 0)
	{
		NotifyObservers(bae::EventType::PLAYER_DIED);
		return;
	}

	NotifyObservers(bae::EventType::PLAYER_HEALTH_CHANGE);
}

bool HealthComponent::IsDead() const
{
	if (m_bIsInvincible)
		return false;

	if (m_Health <= 0.f)
		return true;

	return false;
}

void HealthComponent::SetHealth(float health)
{
	if (health < 0.f)
		return;

	if (m_Health == health)
		return;

	m_Health = health;
	NotifyObservers(bae::EventType::PLAYER_HEALTH_CHANGE);
}

void HealthComponent::SetMaxHealth(float maxHealth)
{
	if (maxHealth <= 0.f)
		return;

	if (m_MaxHealth == maxHealth)
		return;

	m_MaxHealth = maxHealth;
}


