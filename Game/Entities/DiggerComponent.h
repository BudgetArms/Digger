#pragma once

#include <memory>

#include <glm.hpp>
#include <SDL_rect.h>

#include "Wrappers/Texture2D.h"
#include "Core/Text2D.h"
#include "Components/Component.h"


namespace Game::Entities
{
	class DiggerComponent : public bae::Component
	{
	public:
		DiggerComponent(bae::GameObject& owner);


		void Update() override;
		void Render() const override;


		bool m_BonusStage{ false };


	private:
		int m_Lives{ 3 };

		const glm::vec2 m_LivesStartPosition{ 240, 12 };
		const SDL_Rect m_LiveSrcRect{ 404, 204, 16, 12 };

		std::unique_ptr<bae::Texture2D> m_LivesTexture;
		std::unique_ptr<bae::Text2D> m_TextTexture;


	};


	enum class DiggerSpritesRed
	{
		RightOpen1 = 0,
		RightOpen2,
		RightOpen3,

		LeftOpen1,
		LeftOpen2,
		LeftOpen3,

		UpOpen1,
		UpOpen2,
		UpOpen3,

		DownOpen1,
		DownOpen2,
		DownOpen3,


		RightClosed1,
		RightClosed2,
		RightClosed3,

		LeftClosed1,
		LeftClosed2,
		LeftClosed3,

		UpClosed1,
		UpClosed2,
		UpClosed3,

		DownClosed1,
		DownClosed2,
		DownClosed3,
	};

	enum class DiggerSpritesGreen
	{
		RightOpen1 = 24,
		RightOpen2,
		RightOpen3,

		LeftOpen1,
		LeftOpen2,
		LeftOpen3,

		UpOpen1,
		UpOpen2,
		UpOpen3,

		DownOpen1,
		DownOpen2,
		DownOpen3,


		RightClosed1,
		RightClosed2,
		RightClosed3,

		LeftClosed1,
		LeftClosed2,
		LeftClosed3,

		UpClosed1,
		UpClosed2,
		UpClosed3,

		DownClosed1,
		DownClosed2,
		DownClosed3,
	};

}


