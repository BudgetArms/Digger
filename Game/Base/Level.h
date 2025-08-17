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

		Grid grid;
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
	void from_json(const nlohmann::json& json, Level& level)
	{
		json.at("levelNumber").get_to(level.levelNumber);
		json.at("name").get_to(level.name);


		const auto& gridJson = json.at("grid");
		level.grid =
		{
			.columns = gridJson.at("columns"),
			.rows = gridJson.at("rows"),
			.cellSize = { gridJson.at("cellSize").at("x"), gridJson.at("cellSize").at("y") },
			.bIsDirectionalGraph = gridJson.at("isDirectionalGraph"),
			.bIsConnectedDiagonally = gridJson.at("isConnectedDiagonally"),
			.costStraight = gridJson.at("costStraight"),
			.costDiagonally = gridJson.at("costDiagonally"),
		};


		for (const auto& spawnerJson : json.at("nobbinSpawners"))
		{
			NobbinSpawner spawner
			{
				.position =
				{
					.column = spawnerJson.at("position").at("column"),
					.row = spawnerJson.at("position").at("row"),
				},
				.spawnDelay = spawnerJson.at("spawnDelay"),
				.maxNobbins = spawnerJson.at("maxNobbins"),
				.totalToSpawn = spawnerJson.at("totalToSpawn"),
				.bonus =
				{
					.bonusModeTime = json.at("bonusModeTime"),
					.bonusModeScore = json.at("bonusModeScore"),
				}
			};

			level.nobbinSpawners.push_back(spawner);
		}

		for (const auto& emeraldJson : json.at("emeralds"))
		{
			Emerald emerald =
			{
				.position =
				{
					.column = emeraldJson.at("position").at("column"),
					.row = emeraldJson.at("position").at("row"),
				},
			};

			level.emeralds.push_back(emerald);
		}

		for (const auto& goldBagJson : json.at("goldBags"))
		{
			GoldBag goldBag =
			{
				.position =
				{
					.column = goldBagJson.at("position").at("column"),
					.row = goldBagJson.at("position").at("row"),
				},
			};

			level.goldBags.push_back(goldBag);
		}

		level.playerStart.column = json.at("playerStart").at("column");
		level.playerStart.row = json.at("playerStart").at("row");

		// get_to for small variables
		json.at("mustCollectAllEmeralds").get_to(level.bMustCollectAllEmeralds);
		json.at("canKillAllNobbins").get_to(level.bCanKillAllNobbins);
		json.at("hasBonus").get_to(level.bHasBonus);
		json.at("hobbinTransformTime").get_to(level.hobbinTransformTime);
		json.at("shotRechargeTime").get_to(level.shotRechargeTime);
		json.at("goldBagWobbleTime").get_to(level.goldBagWobbleTime);
		json.at("emeraldBonusSequence").get_to(level.emeraldBonusSequence);

		json.at("emeraldScore").get_to(level.emeraldScore);
		json.at("emeraldBonusScore").get_to(level.emeraldBonusScore);
		json.at("goldBagScore").get_to(level.goldBagScore);
		json.at("nobbinKillScore").get_to(level.nobbinKillScore);
		json.at("bonusModeScore").get_to(level.bonusModeScore);

		json.at("extraLifeScoreInterval").get_to(level.extraLifeScoreInterval);
	}

}


