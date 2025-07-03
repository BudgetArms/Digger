

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
#include "Core/Scene.h"
#include "Core/SoundSystem.h"
#include "Core/SdlSoundSystem.h"
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


#ifdef STEAMWORKS_ENABLED

#include "Core/Achievement.h"
#include "Managers/SteamManager.h"
#include "Managers/AchievementManager.h"

#endif

#include "Wrappers/Controller.h"
#include "Wrappers/Keyboard.h"


// Game Includes

#include "Base/SoundEvents.h"




#pragma endregion



namespace fs = std::filesystem;
using namespace bae;

void Start();
void LoadStart();
void LoadSounds();


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

    return 0;
}


void Start()
{
    auto& scene = SceneManager::GetInstance().CreateScene("BudgetArmsEngine");

    LoadSounds();
    LoadStart();


    auto background = std::make_shared<GameObject>("Background");
    background->AddComponent<TextureComponent>(*background, "Textures/background.tga");
    scene.Add(background);

    auto logo = std::make_shared<GameObject>("Logo");
    logo->AddComponent<TextureComponent>(*logo, "Textures/logo.tga");
    logo->SetLocalLocation({ 216, 180, 0 });
    scene.Add(logo);


    auto font = ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 36);
    auto fontSmall = ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 18);

    auto fpsCounter = std::make_shared<GameObject>("Fps Counter");
    fpsCounter->AddComponent<FpsTextComponent>(*fpsCounter, fontSmall, SDL_Color(255, 255, 255, 255));

    scene.m_bIsEnabled = false;


    auto& fpsScene = SceneManager::GetInstance().CreateScene("FpsCounterScene");
    SDL_Window* window = Renderer::GetInstance().GetSDLWindow();
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    fpsCounter->SetWorldLocation({ width, 0, 0 });
    fpsCounter->AddLocation({ -75, 5, 0 });

    fpsScene.Add(fpsCounter);


}


void LoadSounds()
{
    namespace gs = Game::Sounds;

    bae::ServiceLocator::RegisterSoundSystem(std::make_unique<bae::SdlSoundSystem>());
    auto soundSystem = &bae::ServiceLocator::GetSoundSystem();

    // Sound files not made yet
    gs::g_sSoundEvents =
    {
        { gs::SoundEvents::GameplayMusic,       soundSystem->LoadSound("Resources/Sounds/GameplayMusic.wav") },
        //{ gs::SoundEvents::CollectedEmerald,    soundSystem->LoadSound("Resources/Sounds/.wav") },
        //{ gs::SoundEvents::GoldBagCountdown,    soundSystem->LoadSound("Resources/Sounds/.wav") },
        //{ gs::SoundEvents::GoldBagFalling,      soundSystem->LoadSound("Resources/Sounds/.wav") },
        //{ gs::SoundEvents::PlayerHit,           soundSystem->LoadSound("Resources/Sounds/.wav") },
        { gs::SoundEvents::PlayerDeath,         soundSystem->LoadSound("Resources/Sounds/PlayerDeathSound.wav") },
        { gs::SoundEvents::PlayerDeathMusic,    soundSystem->LoadSound("Resources/Sounds/DeadMusicSound.wav") },
        //{ gs::SoundEvents::BallTravelingSound,  soundSystem->LoadSound("Resources/Sounds/.wav") },
        //{ gs::SoundEvents::BallHitSound,        soundSystem->LoadSound("Resources/Sounds/.wav") },
    };

}

void LoadStart()
{




}


