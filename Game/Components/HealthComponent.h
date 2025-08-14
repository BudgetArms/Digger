#pragma once

#include "Components/Component.h"
#include "Core/Subject.h"


namespace Game::Components
{
	class HealthComponent : public bae::Component, public bae::Subject
	{
	public:
		explicit HealthComponent(bae::GameObject& owner, float maxHealth);
		~HealthComponent() = default;


		void Damage(float damage);

		bool IsDead() const;

		float GetHealth() const { return m_Health; };
		void SetHealth(float health);

		float GetMaxHealth() const { return m_MaxHealth; };
		void SetMaxHealth(float health);


		bool m_bIsInvincible{ false };


	private:
		float m_Health;
		float m_MaxHealth;


	};
}


