#include "Level.h"



void Game::Level::from_json(const nlohmann::json& json, Level& plevel)
{
	json.at("levelNumber").get_to(plevel.levelNumber);
	json.at("name").get_to(plevel.name);


	const auto& gridJson = json.at("grid");
	plevel.grid =
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

		plevel.nobbinSpawners.push_back(spawner);
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

		plevel.emeralds.push_back(emerald);
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

		plevel.goldBags.push_back(goldBag);
	}

	plevel.playerStart.column = json.at("playerStart").at("column");
	plevel.playerStart.row = json.at("playerStart").at("row");

	// get_to for small variables
	json.at("mustCollectAllEmeralds").get_to(plevel.bMustCollectAllEmeralds);
	json.at("canKillAllNobbins").get_to(plevel.bCanKillAllNobbins);
	json.at("hasBonus").get_to(plevel.bHasBonus);
	json.at("hobbinTransformTime").get_to(plevel.hobbinTransformTime);
	json.at("shotRechargeTime").get_to(plevel.shotRechargeTime);
	json.at("goldBagWobbleTime").get_to(plevel.goldBagWobbleTime);
	json.at("emeraldBonusSequence").get_to(plevel.emeraldBonusSequence);

	json.at("emeraldScore").get_to(plevel.emeraldScore);
	json.at("emeraldBonusScore").get_to(plevel.emeraldBonusScore);
	json.at("goldBagScore").get_to(plevel.goldBagScore);
	json.at("nobbinKillScore").get_to(plevel.nobbinKillScore);
	json.at("bonusModeScore").get_to(plevel.bonusModeScore);

	json.at("extraLifeScoreInterval").get_to(plevel.extraLifeScoreInterval);
}


