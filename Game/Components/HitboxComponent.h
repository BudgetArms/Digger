#pragma once

#include <SDL_rect.h>

#include "Components/Component.h"


namespace Game::Components
{
	class HitboxComponent : public bae::Component
	{
	public:
		HitboxComponent(bae::GameObject& owner, int width, int height, bool scaleWithOwner = true);


		void Update() override;
		void Render() const override;

		SDL_Rect GetHitbox() const { return m_Hitbox; }


		bool m_bIsActive{ true };
		bool m_bRenderHitbox{ false };


	private:
		const int m_Width;
		const int m_Height;
		SDL_Rect m_Hitbox;
		bool m_bScaleWithOwner;


	};
}


