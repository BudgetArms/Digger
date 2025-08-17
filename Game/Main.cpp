#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


#include <memory>
#include <cassert>

#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <chrono>


#pragma region BudgetArmsEngine Includes


#include <glm.hpp>
#include <SDL.h>
#include <imgui.h>
#include <imgui_plot.h>

#ifdef STEAMWORKS_ENABLED
#pragma warning (push)
#pragma warning (disable: 4996)
#include <steam_api.h>
#pragma warning (pop)
#endif


#include "Core/BudgetEngine.h"
#include "Core/GameObject.h"
#include "Core/Renderer.h"
#include "Core/RingBuffer.h"
#include "Core/Scene.h"
#include "Core/ServiceLocator.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"

#include "Commands/Command.h"
#include "Commands/GameActorCommand.h"

#include "Components/Component.h"
#include "Components/FpsCounterComponent.h"
#include "Components/ImguiComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TrashTheCacheComponent.h"

#include "Managers/ResourceManager.h"
#include "Managers/SceneManager.h"

#include "Sounds/SoundSystem.h"
#include "Sounds/LoggingSoundSystem.h"
#include "Sounds/SdlSoundSystem.h"
#include "Sounds/SdlAudioClip.h"
#include "Sounds/LoggingAudioClip.h"
#include "Sounds/NullAudioClip.h"

#include "Wrappers/Controller.h"
#include "Wrappers/Keyboard.h"
#include "Wrappers/Mouse.h"


#ifdef STEAMWORKS_ENABLED

#include "Core/Achievement.h"
#include "Managers/SteamManager.h"
#include "Managers/AchievementManager.h"

#endif


#pragma endregion


// Game Includes
#include "Base/LevelManager.h"
#include "Base/GameModeManager.h"
#include "Base/SoundEvents.h"
#include "Base/TerrainGridGraph.h"
#include "Base/EntityManager.h"

#include "Commands/TestGridCommands.h"
#include "Commands/TestMoveCommands.h"
#include "Commands/TestSoundCommands.h"
#include "Commands/TestSpriteCommands.h"
#include "Commands/MoveCommand.h"

#include "Components/AIComponent.h"
#include "Components/EntityManagerComponent.h"
#include "Components/GameModeManagerComponent.h"
#include "Components/GridComponent.h"
#include "Components/HitboxComponent.h"


#include "Entities/BonusComponent.h"
#include "Entities/DiggerComponent.h"
#include "Entities/EmeraldComponent.h"
#include "Entities/GoldBagComponent.h"
#include "Entities/NobbinComponent.h"



namespace fs = std::filesystem;
using namespace bae;

void Start();
void LoadSounds();
void LoadStartScene();
void LoadDefaultScene();
void LoadFpsCounterScene();
void LoadTestSoundCommands();
void LoadLevel();



int main(int, char* [])
{
	//thx myself for dying to find this
#ifdef WIN32
	if (AllocConsole())
	{
		FILE* pEmpty;
		freopen_s(&pEmpty, "CONOUT$", "w", stdout);
		freopen_s(&pEmpty, "CONOUT$", "w", stderr);
	}
#endif


	bae::Utils::Window window{ "Digger", "./Resources/", 960, 612, false };


#if __EMSCRIPTEN__
	window.resourceFolder = "";
#else

	if (!fs::exists(window.resourceFolder))
		window.resourceFolder = "../Resources/";

	if (!fs::exists(window.resourceFolder))
	{
		std::cout << "Resouces Folder Not Found" << '\n';
		assert("Resouces Folder Not Found");
		exit(-1);
	}

#ifdef STEAMWORKS_ENABLED
	SteamManager::GetInstance().Initialize();

#endif

#endif


	BudgetEngine engine(window);
	engine.Run(Start);


#ifdef STEAMWORKS_ENABLED
	SteamManager::GetInstance().Shutdown();
#endif


	std::cout << "\n\n";


	return 0;
}


void Start()
{
	bae::ServiceLocator::RegisterAudioQueue<bae::SdlAudioClip>();
	//bae::ServiceLocator::RegisterAudioQueue<bae::LoggingAudioClip<bae::SdlAudioClip>>();

	bae::ServiceLocator::RegisterSoundSystem(std::make_unique<bae::SdlSoundSystem>());
	//bae::ServiceLocator::RegisterSoundSystem(std::make_unique<bae::LoggingSoundSystem>(std::make_unique<bae::SdlSoundSystem>()));


	LoadSounds();
	//LoadDefaultScene();
	//LoadStartScene();
	LoadFpsCounterScene();
	LoadTestSoundCommands();
	LoadLevel();

	/*/
	auto& scene = SceneManager::GetInstance().CreateScene("GridScene");
	auto gridObject = std::make_shared<GameObject>("Grid");
	gridObject->SetWorldLocation({ 0, 54 });
	//gridObject->AddComponent<Game::Components::GridComponent>(*gridObject, 15, 10, glm::ivec2{ 60, 54 }, false, false);
	gridObject->AddComponent<Game::Components::GridComponent>(*gridObject, 2, 2, glm::ivec2{ 60, 54 }, false, false);
	scene.Add(gridObject);
	//*/


}


void LoadSounds()
{
	namespace gs = Game::Sounds;

	auto& soundSystem = bae::ServiceLocator::GetSoundSystem();

	// Sound files not made yet
	gs::g_sSoundEvents =
	{
		{ gs::SoundEvents::GameplayMusic,       soundSystem.LoadSound("Resources/Sounds/GameplayMusic.wav") },
		//{ gs::SoundEvents::CollectedEmerald,    soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::GoldBagCountdown,    soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::GoldBagFalling,      soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::PlayerHit,           soundSystem->LoadSound("Resources/Sounds/.wav") },
		{ gs::SoundEvents::PlayerDeath,         soundSystem.LoadSound("Resources/Sounds/PlayerDeath.wav") },
		{ gs::SoundEvents::PlayerDeathLong,     soundSystem.LoadSound("Resources/Sounds/PlayerDeathLong.wav") },
		//{ gs::SoundEvents::BallTravelingSound,  soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::BallHitSound,        soundSystem->LoadSound("Resources/Sounds/.wav") },
	};

}


void LoadStartScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("GridScene");

	auto gridObject = std::make_shared<GameObject>("Grid");

	gridObject->SetWorldLocation({ 0, 54 });
	gridObject->AddComponent<Game::Components::GridComponent>(*gridObject, 15, 10, glm::ivec2{ 60, 54 }, false, false);
	auto pTerrainGridGraph = gridObject->GetComponent<Game::Components::GridComponent>()->GetTerrainGridGraph(); ////////////////////
	scene.Add(gridObject);

	auto entityManager = std::make_shared<GameObject>("EntityManager");
	entityManager->AddComponent<Game::Components::EntityManagerComponent>(*entityManager);
	scene.Add(entityManager);


	auto digger = std::make_shared<GameObject>("Digger");
	digger->AddComponent<Game::Entities::DiggerComponent>(*digger);
	digger->AddLocation({ 480, 576 });
	scene.Add(digger);

	auto nobbin = std::make_shared<GameObject>("Nobbin");
	nobbin->AddComponent<Game::Entities::NobbinComponent>(*nobbin);
	nobbin->AddLocation({ 816, 90 });
	scene.Add(nobbin);

	auto aiComp = nobbin->GetComponent<Game::Components::AIComponent>();
	aiComp->m_TerrainGridGraph = pTerrainGridGraph;



	auto emerald = std::make_shared<GameObject>("Emerald");
	emerald->AddComponent<Game::Entities::EmeraldComponent>(*emerald);
	emerald->AddLocation({ 300, 300 });
	scene.Add(emerald);

	auto goldBag = std::make_shared<GameObject>("GoldBag");
	goldBag->AddComponent<Game::Entities::GoldBagComponent>(*goldBag);
	goldBag->AddLocation({ 400, 300 });
	scene.Add(goldBag);

	auto bonus = std::make_shared<GameObject>("Bonus");
	bonus->AddComponent<Game::Entities::BonusComponent>(*bonus, 10.f, 1000.f);
	bonus->AddLocation({ 500, 300 });
	scene.Add(bonus);





	// Sprite Tests
	auto& keyboard = bae::InputManager::GetInstance().GetKeyboard();
	std::unique_ptr<Game::Commands::TestSpriteCommand> spriteCommand;

	// Digger
	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*digger, Game::Commands::TestSpriteAction::PreviousSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_t, bae::InputManager::ButtonState::Down);

	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*digger, Game::Commands::TestSpriteAction::NextSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_y, bae::InputManager::ButtonState::Down);


	// Nobbin
	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*nobbin, Game::Commands::TestSpriteAction::PreviousSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_g, bae::InputManager::ButtonState::Down);

	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*nobbin, Game::Commands::TestSpriteAction::NextSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_h, bae::InputManager::ButtonState::Down);


	// GoldBag
	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*goldBag, Game::Commands::TestSpriteAction::PreviousSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_v, bae::InputManager::ButtonState::Down);

	spriteCommand = std::make_unique<Game::Commands::TestSpriteCommand>(*goldBag, Game::Commands::TestSpriteAction::NextSprite);
	keyboard.AddKeyboardCommands(std::move(spriteCommand), SDLK_n, bae::InputManager::ButtonState::Down);



	InputManager::GetInstance().AddController(0);
	InputManager::GetInstance().AddController(1);

	auto* myController = InputManager::GetInstance().GetController(1);


	// move player 1 (controller)
	auto moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*digger, glm::vec2(0, 1), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_DOWN, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*digger, glm::vec2(0, -1), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_UP, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*digger, glm::vec2(-1, 0), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_LEFT, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*digger, glm::vec2(1, 0), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_RIGHT, InputManager::ButtonState::Pressed);


	// move player 2 (keyboard)
	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(0, -1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_w, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(0, 1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_s, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(-1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_a, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_d, InputManager::ButtonState::Pressed);



	auto& mouse = bae::InputManager::GetInstance().GetMouse();

	// TestGridCommand
	auto setPathCommand = std::make_unique<Game::Commands::TestGridCommand>(*nobbin);
	mouse.AddMouseCommands(std::move(setPathCommand), SDL_BUTTON_LEFT, InputManager::ButtonState::Pressed);



}


void LoadDefaultScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("BudgetArmsEngine");

	auto background = std::make_shared<GameObject>("Background");
	background->AddComponent<TextureComponent>(*background, "Textures/background.tga");
	scene.Add(background);

	auto logo = std::make_shared<GameObject>("Logo");
	logo->AddComponent<TextureComponent>(*logo, "Textures/logo.tga");

	SDL_Window* window = Renderer::GetInstance().GetSDLWindow();
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	logo->SetWorldLocation({ width / 2.f, height / 2.f });
	logo->GetComponent<TextureComponent>()->m_bIsCenteredAtPosition = true;
	scene.Add(logo);


}


void LoadFpsCounterScene()
{
	auto& fpsScene = SceneManager::GetInstance().CreateScene("FpsCounterScene");

	auto font = ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 36);
	auto fontSmall = ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 18);

	auto fpsCounter = std::make_shared<GameObject>("Fps Counter");
	fpsCounter->AddComponent<FpsTextComponent>(*fpsCounter, fontSmall, SDL_Color(255, 255, 255, 255));

	SDL_Window* window = Renderer::GetInstance().GetSDLWindow();
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	fpsCounter->SetWorldLocation({ width, 0.f });
	fpsCounter->AddLocation({ -75.f, 5.f });

	fpsScene.Add(fpsCounter);


}


void LoadTestSoundCommands()
{
	namespace gs = Game::Sounds;

	auto& keyboard = InputManager::GetInstance().GetKeyboard();
	auto soundSystem = &bae::ServiceLocator::GetSoundSystem();


	// Play & Pause Immediately after
	auto activeSoundId = soundSystem->Play(gs::GetSoundId(gs::SoundEvents::PlayerDeathLong), 1);
	//soundSystem->Pause(activeSoundId);


	// Sound Commands:
	std::unique_ptr<gs::TestPlaySoundCommand> soundPlayCommands;
	std::unique_ptr<gs::TestSoundCommand> soundCommands;

	// Play
	soundPlayCommands = std::make_unique<gs::TestPlaySoundCommand>(gs::GetSoundId(gs::SoundEvents::PlayerDeathLong));
	keyboard.AddKeyboardCommands(std::move(soundPlayCommands), SDLK_1, bae::InputManager::ButtonState::Down);


	// TogglePause
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::TogglePause, activeSoundId);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_2, bae::InputManager::ButtonState::Down);

	// ToggleMute
	//soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::ToggleMute, activeSoundId);
	//keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_3, bae::InputManager::ButtonState::Down);


	// Change Volume
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::SetVolume, activeSoundId, 0.5f);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_4, bae::InputManager::ButtonState::Down);

	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::SetVolume, activeSoundId, 1.0f);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_5, bae::InputManager::ButtonState::Down);



	// All Sounds Commands

	// Change Volume
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::SetVolumeAll, ActiveSoundID(-1), 0.2f);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_6, bae::InputManager::ButtonState::Down);

	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::SetVolumeAll, ActiveSoundID(-1), 0.7f);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_7, bae::InputManager::ButtonState::Down);

	// StopAll
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::StopAll);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_8, bae::InputManager::ButtonState::Down);

	// TogglePauseAll/ToglleMuteAll
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::TogglePauseAll);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_9, bae::InputManager::ButtonState::Down);

	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::ToggleMuteAll);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_0, bae::InputManager::ButtonState::Down);

	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::Mute, activeSoundId);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_3, bae::InputManager::ButtonState::Down);


}


void LoadLevel()
{
	//*/
	auto& managersScene = SceneManager::GetInstance().CreateScene("Managers");

	auto gameMode = std::make_shared<bae::GameObject>("GameModeManager");
	gameMode->AddComponent<Game::Components::GameModeManagerComponent>(*gameMode);
	managersScene.Add(gameMode);

	auto entityManager = std::make_shared<bae::GameObject>("EntityManager");
	entityManager->AddComponent<Game::Components::EntityManagerComponent>(*entityManager);
	managersScene.Add(entityManager);


	auto& scene = SceneManager::GetInstance().CreateScene("Level");
	Game::Managers::EntityManager::GetInstance().SetScene(scene);

	const auto resourcesPath = bae::ResourceManager::GetInstance().GetResourcesPath();
	auto& lm = Game::Managers::LevelManager::GetInstance();
	lm.LoadLevel(resourcesPath / "Levels/Level_1.json");
	lm.LoadLevel(resourcesPath / "Levels/Level_2.json");
	lm.LoadLevel(resourcesPath / "Levels/Level_3.json");

	lm.SetScene(scene);
	lm.SetCurrentLevel(1);
	lm.SetCurrentLevel(2);
	lm.SetCurrentLevel(3);

	lm.SetCurrentLevel(1);
	lm.SetCurrentLevel(2);
	lm.SpawnLevel();


	InputManager::GetInstance().AddController(0);
	InputManager::GetInstance().AddController(1);

	auto* myController = InputManager::GetInstance().GetController(1);
	auto& keyboard = bae::InputManager::GetInstance().GetKeyboard();

	auto pPlayer = lm.GetPlayer();
	pPlayer->AddComponent<Game::Components::MoveComponent>(*pPlayer, 100.f);


	// move player 1 (controller)

	//auto moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(0, 1), 100.f);
	/*/
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_DOWN, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(0, -1), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_UP, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(-1, 0), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_LEFT, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(1, 0), 200.f);
	myController->AddControllerCommands(std::move(moveCommand), XINPUT_GAMEPAD_DPAD_RIGHT, InputManager::ButtonState::Pressed);
	//*/

	auto realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Up);
	myController->AddControllerCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_UP, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Up);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_w, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Down);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_s, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Left);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_a, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Right);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), SDLK_d, InputManager::ButtonState::Pressed);


	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Up);
	myController->AddControllerCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_UP, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Down);
	keyboard.AddKeyboardCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_DOWN, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Left);
	myController->AddControllerCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_LEFT, InputManager::ButtonState::Pressed);

	realMoveCommand = std::make_unique<Game::Commands::MoveCommand>(*pPlayer, Game::Direction::Right);
	myController->AddControllerCommands(std::move(realMoveCommand), XINPUT_GAMEPAD_DPAD_RIGHT, InputManager::ButtonState::Pressed);


	/*/
	// move player 2 (keyboard)
	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(0, -1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_w, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(0, 1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_s, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(-1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_a, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*pPlayer, glm::vec2(1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_d, InputManager::ButtonState::Pressed);

	//*/

	/*/
	// move player 2 (keyboard)
	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(0, -1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_w, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(0, 1), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_s, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(-1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_a, InputManager::ButtonState::Pressed);

	moveCommand = std::make_unique<Game::Commands::TestMoveCommand>(*nobbin, glm::vec2(1, 0), 100.f);
	keyboard.AddKeyboardCommands(std::move(moveCommand), SDLK_d, InputManager::ButtonState::Pressed);
	//*/


}


