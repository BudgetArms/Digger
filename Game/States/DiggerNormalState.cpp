#include "DiggerNormalState.h"

//#include <Windows.h>
//#include <Xinput.h>

#include "Core/GameObject.h"
#include "Managers/InputManager.h"
#include "Wrappers/Controller.h"
#include "Wrappers/Keyboard.h"

#include "../Commands/MoveCommand.h"
#include "../Commands/TestSoundCommands.h"
#include "../Base/DirectionEnum.h"



using namespace Game::States;


void DiggerNormalState::OnEnter(bae::GameObject& owner)
{
	m_Owner = &owner;

	//*
	bae::InputManager::GetInstance().AddController(0);
	auto* myController = bae::InputManager::GetInstance().GetController(1);
	auto& keyboard = bae::InputManager::GetInstance().GetKeyboard();

	auto realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*m_Owner, Game::Direction::Up);
	myController->AddControllerCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_UP, bae::InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*m_Owner, Game::Direction::Up);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_w, bae::InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*m_Owner, Game::Direction::Down);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_s, bae::InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*m_Owner, Game::Direction::Left);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_a, bae::InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*m_Owner, Game::Direction::Right);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_d, bae::InputManager::ButtonState::Pressed);
	//*/



	// Play
	//namespace gs = Game::Sounds;
	auto soundPlayCommands = std::make_unique<Game::Sounds::TestPlaySoundCommand>(Game::Sounds::GetSoundId(Game::Sounds::SoundEvents::PlayerDeathLong));
	keyboard.AddKeyboardCommands(std::move(soundPlayCommands), SDLK_1, bae::InputManager::ButtonState::Down);


}

void DiggerNormalState::OnExit()
{
}


void DiggerNormalState::Update()
{
}
