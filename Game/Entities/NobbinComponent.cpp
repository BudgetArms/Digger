#include "NobbinComponent.h"

#include "Core/Utils.h"
#include "Singletons/GameTime.h"
#include "Components/SpriteComponent.h"

#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/AIComponent.h"
#include "../Base/LevelManager.h"


using namespace Game::Entities;
namespace bu = bae::Utils;


NobbinComponent::NobbinComponent(bae::GameObject& owner) :
	bae::Component(owner)
{
	m_Owner->AddComponent<Game::Components::HealthComponent>(*m_Owner, 100.f);
	m_Owner->AddComponent<bae::SpriteComponent>(*m_Owner, "Textures/SpriteSheet.png",
		SDL_Rect(0, 136, 584, 24), 12, 12, glm::ivec2{ 8, 0 });

	m_Owner->AddComponent<Game::Components::AIComponent>(*m_Owner);


	m_Owner->AddComponent<Game::Components::HitboxComponent>(*m_Owner, 17, 17);
	//m_Owner->GetComponent<Game::Components::HitboxComponent>()->m_bRenderHitbox = true;

	m_Owner->SetWorldScale({ 3.f, 3.f });


	m_SpriteComp = m_Owner->GetComponent<bae::SpriteComponent>();

	auto& lm = Game::Managers::LevelManager::GetInstance();
	m_Player = lm.GetPlayer();

	auto aiComp = m_Owner->GetComponent<Game::Components::AIComponent>();
	aiComp->m_TerrainGridGraph = lm.GetGridComponent()->GetTerrainGridGraph();
	aiComp->m_Speed = 70.f;
}


void NobbinComponent::Update()
{
	auto aiComp = m_Owner->GetComponent<Game::Components::AIComponent>();
	if (!aiComp || !m_Player)
		return;

	m_DelayMovingElapsedSec += bae::GameTime::GetInstance().GetDeltaTime();
	if (!m_bStartedMoving && m_DelayMovingElapsedSec >= m_DelayStartMoving)
	{
		m_bStartedMoving = true;
		aiComp->SetPath(m_Player);
	}

	m_AnimationElapsedSec += bae::GameTime::GetInstance().GetDeltaTime();
	if (m_AnimationElapsedSec >= m_AnimationDelay)
	{
		m_AnimationElapsedSec = 0.f;
		SwitchAnimation();
	}


}

void NobbinComponent::ChangeSpeed(float speed)
{
	auto aiComp = m_Owner->GetComponent<Game::Components::AIComponent>();
	if (!aiComp || !m_Player)
		return;

	aiComp->m_Speed = speed;
}

void NobbinComponent::SwitchAnimation()
{
	m_SpriteComp->NextSprite();
	if (m_SpriteComp->m_Index > static_cast<int>(NobbinSprites::LooksUpRight))
		m_SpriteComp->m_Index = 0;


}


