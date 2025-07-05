#pragma once

#include <iostream>

#include "Commands/Command.h"
#include "Core/ServiceLocator.h"

#include "../Base/SoundEvents.h"


namespace Game::Sounds
{

    class TestSoundCommand : public bae::Command
    {
    public:
        TestSoundCommand(Game::Sounds::SoundEvents sound) :
            bae::Command(),
            m_SoundId{ Game::Sounds::GetSoundId(sound) }
        {
        };

        virtual ~TestSoundCommand() = default;

        TestSoundCommand(const TestSoundCommand& other) = delete;
        TestSoundCommand(TestSoundCommand&& other) = delete;
        TestSoundCommand& operator=(const TestSoundCommand& other) = delete;
        TestSoundCommand& operator=(TestSoundCommand&& other) = delete;


        virtual void Execute() override = 0;


    protected:
        int m_SoundId;


    };

    class TestAllSoundsCommand : public bae::Command
    {
    public:
        TestAllSoundsCommand() :
            bae::Command()
        {
        };

        virtual ~TestAllSoundsCommand() = default;

        TestAllSoundsCommand(const TestAllSoundsCommand& other) = delete;
        TestAllSoundsCommand(TestAllSoundsCommand&& other) = delete;
        TestAllSoundsCommand& operator=(const TestAllSoundsCommand& other) = delete;
        TestAllSoundsCommand& operator=(TestAllSoundsCommand&& other) = delete;


        virtual void Execute() override = 0;


    };


    class TestPlaySoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestPlaySoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.Play(m_SoundId, 0.5f);
        }
    };

    class TestStopSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestStopSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.Resume(m_SoundId);
        }
    };

    class TestResumeSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestResumeSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.Resume(m_SoundId);
        }
    };

    class TestPauseSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestPauseSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.Pause(m_SoundId);
        }
    };

    class TestMuteSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestMuteSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.Pause(m_SoundId);
        }
    };

    class TestUnMuteSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestUnMuteSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.UnMute(m_SoundId);
        }
    };


    class TestTogglePauseSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestTogglePauseSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            if (m_bIsPaused)
                soundSystem.Resume(m_SoundId);
            else
                soundSystem.Pause(m_SoundId);

            m_bIsPaused = !m_bIsPaused;
        }


    private:
        bool m_bIsPaused{ false };


    };

    class TestToggleMuteSoundCommand final : public Game::Sounds::TestSoundCommand
    {
    public:
        TestToggleMuteSoundCommand(Game::Sounds::SoundEvents sound) :
            Game::Sounds::TestSoundCommand(sound)
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            if (m_bIsMuted)
                soundSystem.UnMute(m_SoundId);
            else
                soundSystem.Mute(m_SoundId);

            m_bIsMuted = !m_bIsMuted;
        }


    private:
        bool m_bIsMuted{ false };


    };




    class TestStopAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestStopAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.StopAllSounds();
        }
    };

    class TestResumeAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestResumeAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.ResumeAllSounds();
        }
    };

    class TestPauseAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestPauseAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.PauseAllSounds();
        }
    };

    class TestMuteAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestMuteAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.MuteAllSounds();
        }
    };

    class TestUnMuteAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestUnMuteAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            soundSystem.UnMuteAllSounds();
        }
    };


    class TestTogglePauseAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestTogglePauseAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            if (m_bIsPaused)
                soundSystem.ResumeAllSounds();
            else
                soundSystem.PauseAllSounds();

            m_bIsPaused = !m_bIsPaused;
        }


    private:
        bool m_bIsPaused{ false };


    };

    class TestToggleMuteAllSoundsCommand final : public Game::Sounds::TestAllSoundsCommand
    {
    public:
        TestToggleMuteAllSoundsCommand() :
            Game::Sounds::TestAllSoundsCommand()
        {
        };

        virtual void Execute() override
        {
            auto& soundSystem = bae::ServiceLocator::GetSoundSystem();
            if (m_bIsMuted)
                soundSystem.UnMuteAllSounds();
            else
                soundSystem.MuteAllSounds();

            m_bIsMuted = !m_bIsMuted;
        }

    private:
        bool m_bIsMuted{ false };


    };


}


