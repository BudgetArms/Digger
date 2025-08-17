#include "DiggerComponent.h"

#include <SDL_rect.h>

#include "Core/Renderer.h"
#include "Managers/ResourceManager.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Managers/InputManager.h"
#include "Core/ServiceLocator.h"
#include "Core/Utils.h"
#include "Wrappers/Keyboard.h"
#include "Wrappers/Controller.h"

#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/ScoreComponent.h"
#include "../States/DiggerNormalState.h"
#include "../Commands/TestSoundCommands.h"
#include "../Commands/SkipLevelCommand.h"
#include "../States/DiggerDeathState.h"


using namespace Game::Entities;
namespace bu = bae::Utils;


DiggerComponent::DiggerComponent(bae::GameObject& owner) :
	bae::Component(owner),
	m_LivesTexture{ std::make_unique<bae::Texture2D>("Resources/Textures/SpriteSheet.png") },
	m_TextTexture{ std::make_unique<bae::Text2D>(" ") }
{
	m_Owner->AddComponent<Game::Components::HealthComponent>(*m_Owner, 100.f);
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(0, 0, 584, 128), 12, 48, glm::ivec2{ 8, 8 });

	m_Owner->AddComponent<Game::Components::ScoreComponent>(*m_Owner);
	auto pScoreComp = m_Owner->GetComponent<Game::Components::ScoreComponent>();

	pScoreComp->AddScore(5);

	m_TextTexture->SetText(std::to_string(pScoreComp->GetScore()));
	m_TextTexture->m_Position = { 100, 20 };


	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

	m_Owner->SetWorldScale({ 3.f, 3.f });

	m_State = std::make_unique<Game::States::DiggerNormalState>();
	m_State->OnEnter(owner);

	//*

	auto& im = bae::InputManager::GetInstance();
	im.ClearCommands();

	bae::SoundEventData eventData
	{
		.Type = bae::SoundEventType::StopAll
	};

	bae::ServiceLocator::GetAudioQueue().SendSoundEvent(eventData);

	auto& keyboard = im.GetKeyboard();

	auto soundCommand = std::make_unique<Game::Sounds::TestSoundCommand>(Game::Sounds::TestSoundEvents::ToggleMuteAll);
	keyboard.AddKeyboardCommands(std::move(soundCommand), SDLK_F2, bae::InputManager::ButtonState::Down);

	auto skipCommand = std::make_unique<Game::Commands::SkipLevelCommand>();
	keyboard.AddKeyboardCommands(std::move(skipCommand), SDLK_F1, bae::InputManager::ButtonState::Down);

	//*/


}


void DiggerComponent::Update()
{
	auto pScoreComp = m_Owner->GetComponent<Game::Components::ScoreComponent>();

	m_TextTexture->SetText(std::to_string(pScoreComp->GetScore()));
	m_TextTexture->Update();

	if (m_State)
		m_State->Update();
}

void DiggerComponent::Render() const
{
	const int offset{ 4 };
	for (int i{}; i < m_Lives; ++i)
	{
		bae::Renderer::GetInstance().RenderTexture(*m_LivesTexture.get(), false, m_LiveSrcRect,
			SDL_Rect(static_cast<int>(m_LivesStartPosition.x + i * (m_LiveSrcRect.w + offset) * m_Owner->GetWorldScale().x),
				static_cast<int>(m_LivesStartPosition.y), static_cast<int>(m_LiveSrcRect.w), static_cast<int>(m_LiveSrcRect.h)),
			0.f, m_Owner->GetWorldScale());

	}


	m_TextTexture->Render();

}

void Game::Entities::DiggerComponent::SetState(std::unique_ptr<Game::States::DiggerState> newState)
//void Game::Entities::DiggerComponent::SetState(std::unique_ptr<Game::States::DiggerState>)
{
	if (m_State)
		m_State->OnExit();

	m_State = std::move(newState);

	if (m_State)
		m_State->OnEnter(*m_Owner);


}

void Game::Entities::DiggerComponent::PlayerDead()
{
	if (m_Dead)
		return;
	m_Lives--;

	m_Dead = true;
	if (m_Owner->GetComponent<Game::Components::HealthComponent>()->IsDead())
		SetState(std::make_unique <Game::States::DiggerDeathState>());

}


