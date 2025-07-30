#pragma region Includes

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


// BudgetArmsEngine Includes
#include "Core/BudgetEngine.h"
#include "Core/GameObject.h"
#include "Core/Renderer.h"
#include "Core/RingBuffer.h"
#include "Core/Scene.h"
#include "Core/ServiceLocator.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"

#include "Commands/Command.h"
#include "Commands/MoveCommand.h"

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


#ifdef STEAMWORKS_ENABLED

#include "Core/Achievement.h"
#include "Managers/SteamManager.h"
#include "Managers/AchievementManager.h"

#endif



// Game Includes
#include "Base/SoundEvents.h"
#include "Commands/TestSoundCommands.h"




#pragma endregion



namespace fs = std::filesystem;
using namespace bae;

void Start();
void LoadSounds();
void LoadStartScene();
void LoadDefaultScene();
void LoadFpsCounterScene();
void LoadTestSoundCommands();



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

#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path resourcesFolder = "./Resources/";


	if (!fs::exists(resourcesFolder))
		resourcesFolder = "../Resources/";

	if (!fs::exists(resourcesFolder))
	{
		std::cout << "Resouces Folder Not Found" << '\n';
		assert("Resouces Folder Not Found");
		exit(-1);
	}

#ifdef STEAMWORKS_ENABLED
	SteamManager::GetInstance().Initialize();

#endif

#endif


	BudgetEngine engine(resourcesFolder);
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
	LoadStartScene();
	LoadDefaultScene();
	LoadFpsCounterScene();
	LoadTestSoundCommands();


}


void LoadSounds()
{
	namespace gs = Game::Sounds;

	auto soundSystem = &bae::ServiceLocator::GetSoundSystem();

	// Sound files not made yet
	gs::g_sSoundEvents =
	{
		{ gs::SoundEvents::GameplayMusic,       soundSystem->LoadSound("Resources/Sounds/GameplayMusic.wav") },
		//{ gs::SoundEvents::CollectedEmerald,    soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::GoldBagCountdown,    soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::GoldBagFalling,      soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::PlayerHit,           soundSystem->LoadSound("Resources/Sounds/.wav") },
		{ gs::SoundEvents::PlayerDeath,         soundSystem->LoadSound("Resources/Sounds/PlayerDeath.wav") },
		{ gs::SoundEvents::PlayerDeathLong,     soundSystem->LoadSound("Resources/Sounds/PlayerDeathLong.wav") },
		//{ gs::SoundEvents::BallTravelingSound,  soundSystem->LoadSound("Resources/Sounds/.wav") },
		//{ gs::SoundEvents::BallHitSound,        soundSystem->LoadSound("Resources/Sounds/.wav") },
	};

}


void LoadStartScene()
{

}


void LoadDefaultScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene("BudgetArmsEngine");

	auto background = std::make_shared<GameObject>("Background");
	background->AddComponent<TextureComponent>(*background, "Textures/background.tga");
	scene.Add(background);

	auto logo = std::make_shared<GameObject>("Logo");
	logo->AddComponent<TextureComponent>(*logo, "Textures/logo.tga");
	logo->SetLocalLocation({ 216, 180, 0 });
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
	fpsCounter->SetWorldLocation({ width, 0, 0 });
	fpsCounter->AddLocation({ -75, 5, 0 });

	fpsScene.Add(fpsCounter);


}


void LoadTestSoundCommands()
{
	namespace gs = Game::Sounds;

	auto& keyboard = InputManager::GetInstance().GetKeyboard();
	auto soundSystem = &bae::ServiceLocator::GetSoundSystem();


	// Play & Pause Immediately after
	auto activeSoundId = soundSystem->Play(gs::GetSoundId(gs::SoundEvents::PlayerDeathLong), 1);
	soundSystem->Pause(activeSoundId);


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
	soundCommands = std::make_unique<gs::TestSoundCommand>(gs::TestSoundEvents::ToggleMute, activeSoundId);
	keyboard.AddKeyboardCommands(std::move(soundCommands), SDLK_3, bae::InputManager::ButtonState::Down);


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


}


