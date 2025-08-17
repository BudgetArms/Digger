#include "DiggerDeathState.h"

#include <SDL_keycode.h>

#include "Singletons/GameTime.h"
#include "Core/GameObject.h"
#include "Core/ServiceLocator.h"
#include "Wrappers/Keyboard.h"
#include "Managers/InputManager.h"

#include "../Base/EntityManager.h"
#include "../Entities/DiggerComponent.h"
#include "../Commands/TestSoundCommands.h"
#include "../Commands/SkipLevelCommand.h"
#include "../Base/SoundEvents.h"


using namespace Game::States;


void DiggerDeathState::OnEnter(bae::GameObject& owner)
{
	m_Owner = &owner;

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

	//auto& lm = Game::Managers::LevelManager::GetInstance();
	auto& em = Game::Managers::EntityManager::GetInstance();
	em.RemoveAllNobbins();

	bae::SoundEventData eventData2
	{
		.Type = bae::SoundEventType::Play,
		.SoundID = Game::Sounds::GetSoundId(Game::Sounds::SoundEvents::PlayerDeathLong),
	};


	auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
	soundSystem.Play(eventData2.SoundID, 1.f);


	//bae::ServiceLocator::GetAudioQueue().SendSoundEvent(eventData2);


}


void DiggerDeathState::OnExit()
{


}


void DiggerDeathState::Update()
{
	m_ElapsedSec += bae::GameTime::GetInstance().GetDeltaTime();
	if (m_DeathTime < m_ElapsedSec)
	{

		auto& lm = Game::Managers::LevelManager::GetInstance();
		lm.SpawnLevel();

		//auto playerComp = m_Owner->GetComponent<Game::Entities::DiggerComponent>();
		//playerComp->SetState(std::make_unique<Game)
	}

}
