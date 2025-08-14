#include "HitboxComponent.h"

#include "Core/Utils.h"


using namespace Game::Components;


HitboxComponent::HitboxComponent(bae::GameObject& owner, int width, int height, bool scaleWithOwner) :
	bae::Component(owner),
	m_Width{ width },
	m_Height{ height },
	m_Hitbox{ 0, 0, width, height },
	m_bScaleWithOwner{ scaleWithOwner }
{
	m_Hitbox.x = static_cast<int>(m_Owner->GetWorldLocation().x - m_Hitbox.w / 2.f);
	m_Hitbox.y = static_cast<int>(m_Owner->GetWorldLocation().y - m_Hitbox.h / 2.f);

}

void HitboxComponent::Update()
{
	if (m_bScaleWithOwner)
	{
		m_Hitbox.w = static_cast<int>(m_Owner->GetWorldScale().x * m_Width);
		m_Hitbox.h = static_cast<int>(m_Owner->GetWorldScale().y * m_Height);
	}

	m_Hitbox.x = static_cast<int>(m_Owner->GetWorldLocation().x - m_Hitbox.w / 2.f);
	m_Hitbox.y = static_cast<int>(m_Owner->GetWorldLocation().y - m_Hitbox.h / 2.f);
}

void HitboxComponent::Render() const
{
	if (m_bRenderHitbox)
		bae::Utils::DrawRect(m_Hitbox, bae::Utils::Color::Magenta);

}


