#include "CoOpMode.h"

#include "Core/ServiceLocator.h"
#include "Managers/InputManager.h"

#include "../Base/LevelManager.h"
#include "../Base/SoundEvents.h"


using namespace Game::GameMode;


void CoOpMode::OnEnter()
{
	bool bSucceeded = Game::Managers::LevelManager::GetInstance().SetCurrentLevel(1);
	if (!bSucceeded)
		return;

	Game::Managers::LevelManager::GetInstance().SpawnLevel();

}

void CoOpMode::OnExit()
{
	Game::Managers::LevelManager::GetInstance().ClearScene();


	bae::SoundEventData eventData
	{
		.Type = bae::SoundEventType::StopAll,
	};


	bae::ServiceLocator::GetAudioQueue().SendSoundEvent(eventData);
	bae::InputManager::GetInstance().ClearCommands();

}


