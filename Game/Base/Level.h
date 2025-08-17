#pragma once

#include <vector>

#include <nlohmann/json.hpp>

#include "../Base/Items.h"


namespace Game::Level
{
	struct Level
	{
		int levelNumber{};
		std::string name{};

		Grid grid{};
		GridPosition playerStart{};
		std::vector<NobbinSpawner> nobbinSpawners{};
		std::vector<Emerald> emeralds{};
		std::vector<GoldBag> goldBags{};

		bool bMustCollectAllEmeralds{};
		bool bCanKillAllNobbins{};
		bool bHasBonus{};

		int hobbinTransformTime{};
		int shotRechargeTime{};
		int goldBagWobbleTime{};

		float bonusModeTime{};
		int emeraldBonusSequence{};

		int emeraldScore{};
		int emeraldBonusScore{};
		int goldBagScore{};
		int nobbinKillScore{};
		int bonusModeScore{};

		int extraLifeScoreInterval{};
	};

	// the Nlohmann way to get from json easily

	void from_json(const nlohmann::json& json, Level& plevel);


}


