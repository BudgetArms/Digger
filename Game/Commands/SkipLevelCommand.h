#pragma once

#include "Commands/Command.h"

#include "../Base/LevelManager.h"


namespace Game::Commands
{
	class SkipLevelCommand : public bae::Command
	{
	public:
		SkipLevelCommand() :
			bae::Command()
		{
		};

		virtual ~SkipLevelCommand() = default;

		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) = delete;


		virtual void Execute() override
		{
			std::cout << "Skip Level\n";
			Game::Managers::LevelManager::GetInstance().SkipLevel();
		};


	};
}


