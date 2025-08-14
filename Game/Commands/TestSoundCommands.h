﻿#pragma once

#include <iostream>

#include "Commands/Command.h"
#include "Core/ServiceLocator.h"

#include "../Base/SoundEvents.h"


namespace Game::Sounds
{

	enum class TestSoundEvents
	{
		Stop,
		Resume,
		Pause,
		Mute,
		UnMute,
		SetVolume,
		TogglePause,
		ToggleMute,

		StopAll,
		ResumeAll,
		PauseAll,
		MuteAll,
		UnMuteAll,
		SetVolumeAll,
		TogglePauseAll,
		ToggleMuteAll,
	};


	class TestSoundCommand : public bae::Command
	{
	public:
		TestSoundCommand(TestSoundEvents soundEvent, bae::ActiveSoundID activeSoundId = bae::ActiveSoundID(-1), float volume = 1.f) :
			bae::Command(),
			m_TestEvent{ soundEvent },
			m_ActiveSoundId{ activeSoundId },
			m_Volume{ volume }
		{
		};

		virtual ~TestSoundCommand() = default;

		TestSoundCommand(const TestSoundCommand& other) = delete;
		TestSoundCommand(TestSoundCommand&& other) = delete;
		TestSoundCommand& operator=(const TestSoundCommand& other) = delete;
		TestSoundCommand& operator=(TestSoundCommand&& other) = delete;


		virtual void Execute() override
		{
			auto& soundSystem = bae::ServiceLocator::GetSoundSystem();

			switch (m_TestEvent)
			{
				case Game::Sounds::TestSoundEvents::Stop:
					soundSystem.Stop(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::Resume:
					soundSystem.Resume(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::Pause:
					soundSystem.Pause(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::Mute:
					soundSystem.Mute(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::UnMute:
					soundSystem.UnMute(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::SetVolume:
					soundSystem.SetVolume(m_ActiveSoundId, m_Volume);
					break;
				case Game::Sounds::TestSoundEvents::TogglePause:
					if (soundSystem.IsPaused(m_ActiveSoundId))
						soundSystem.Resume(m_ActiveSoundId);
					else
						soundSystem.Pause(m_ActiveSoundId);
					break;
				case Game::Sounds::TestSoundEvents::ToggleMute:
					if (soundSystem.IsMuted(m_ActiveSoundId))
						soundSystem.UnMute(m_ActiveSoundId);
					else
						soundSystem.Mute(m_ActiveSoundId);
					break;

				case Game::Sounds::TestSoundEvents::StopAll:
					soundSystem.StopAllSounds();
					break;
				case Game::Sounds::TestSoundEvents::ResumeAll:
					soundSystem.ResumeAllSounds();
					break;
				case Game::Sounds::TestSoundEvents::PauseAll:
					soundSystem.PauseAllSounds();
					break;
				case Game::Sounds::TestSoundEvents::MuteAll:
					soundSystem.MuteAllSounds();
					break;
				case Game::Sounds::TestSoundEvents::UnMuteAll:
					soundSystem.UnMuteAllSounds();
					break;
				case Game::Sounds::TestSoundEvents::SetVolumeAll:
					soundSystem.SetVolumeAllSounds(m_Volume);
					break;
				case Game::Sounds::TestSoundEvents::TogglePauseAll:
					if (m_bAreAllSoundsPaused)
						soundSystem.ResumeAllSounds();
					else
						soundSystem.PauseAllSounds();

					m_bAreAllSoundsPaused = !m_bAreAllSoundsPaused;
					break;
				case Game::Sounds::TestSoundEvents::ToggleMuteAll:
					if (m_bAreAllSoundsMuted)
						soundSystem.UnMuteAllSounds();
					else
						soundSystem.MuteAllSounds();

					m_bAreAllSoundsMuted = !m_bAreAllSoundsMuted;
					break;
				default:
					break;
			}

		};


	protected:
		bae::ActiveSoundID m_ActiveSoundId;
		TestSoundEvents m_TestEvent;

		float m_Volume;

		bool m_bAreAllSoundsPaused{ false };
		bool m_bAreAllSoundsMuted{ false };


	};

	class TestPlaySoundCommand : public bae::Command
	{
	public:
		TestPlaySoundCommand(bae::SoundID soundId, float volume = 1.f) :
			bae::Command(),
			m_SoundId{ soundId },
			m_Volume{ volume }
		{
		};

		virtual ~TestPlaySoundCommand() = default;

		TestPlaySoundCommand(const TestPlaySoundCommand& other) = delete;
		TestPlaySoundCommand(TestPlaySoundCommand&& other) = delete;
		TestPlaySoundCommand& operator=(const TestPlaySoundCommand& other) = delete;
		TestPlaySoundCommand& operator=(TestPlaySoundCommand&& other) = delete;


		virtual void Execute() override
		{
			auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
			soundSystem.Play(m_SoundId, m_Volume);
		};


	protected:
		bae::SoundID m_SoundId;
		float m_Volume;


	};
}


