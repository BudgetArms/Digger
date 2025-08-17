#include "VersusMode.h"

#include "Core/ServiceLocator.h"
#include "Managers/InputManager.h"

#include "../Base/LevelManager.h"
#include "../Base/SoundEvents.h"


using namespace Game::GameMode;


void VersusMode::OnEnter()
{
	bool bSucceeded = Game::Managers::LevelManager::GetInstance().SetCurrentLevel(2);
	if (!bSucceeded)
		return;


}

void VersusMode::OnExit()
{
	Game::Managers::LevelManager::GetInstance().ClearScene();


	bae::SoundEventData eventData
	{
		.Type = bae::SoundEventType::StopAll,
	};


	bae::ServiceLocator::GetAudioQueue().SendSoundEvent(eventData);
	bae::InputManager::GetInstance().ClearCommands();

}


