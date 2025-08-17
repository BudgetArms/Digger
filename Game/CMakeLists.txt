cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("\nGame CMake")


add_executable(${PROJECT_NAME}
	"Main.cpp"

	"Base/GameModeManager.h"				"Base/GameModeManager.cpp"
	"Base/Items.h" 
	"Base/Level.h"
	"Base/LevelManager.h"					"Base/LevelManager.cpp"
	"Base/SoundEvents.h"
	"Base/TerrainCostCalculator.h" 
	"Base/TerrainTypes.h" 
	"Base/TerrainGraphNode.h" 
	"Base/TerrainGridGraph.h"				"Base/TerrainGridGraph.cpp"


	"Commands/TestGridCommands.h"
	"Commands/TestSoundCommands.h"
	"Commands/TestSpriteCommands.h"
	"Commands/TestMoveCommands.h"

	"Components/AIComponent.h"				"Components/AIComponent.cpp" 
	"Components/HealthComponent.h"			"Components/HealthComponent.cpp"
	"Components/GridComponent.h"			"Components/GridComponent.cpp"
	"Components/HitboxComponent.h"			"Components/HitboxComponent.cpp"
	"Base/EntityManager.h"			"Base/EntityManager.cpp"
	"Components/PickupComponent.h"			"Components/PickupComponent.cpp"
	"Components/ScoreComponent.h"			"Components/ScoreComponent.cpp"


	"Entities/BonusComponent.h"				"Entities/BonusComponent.cpp"
	"Entities/DiggerComponent.h"			"Entities/DiggerComponent.cpp"
				
	"Entities/EmeraldComponent.h"			"Entities/EmeraldComponent.cpp"
	"Entities/GoldBagComponent.h"			"Entities/GoldBagComponent.cpp" 
	"Entities/NobbinComponent.h"			"Entities/NobbinComponent.cpp"
	"Entities/NobbinSpawnerComponent.h"		"Entities/NobbinSpawnerComponent.cpp"
	

	"Base/GameMode.h" 
	"Base/SoloPlayerMode.h" "Base/SoloPlayerMode.cpp" 

	"Components/GameModeManagerComponent.h"

	"Components/EntityManagerComp.h"
 "Base/CoOpMode.h" "Base/CoOpMode.cpp" "Base/VersusMode.cpp" "Base/VersusMode.h" "Base/Level.cpp")
 

find_package(VLD CONFIG)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_NAME})


if(WIN32)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Resources" "${CMAKE_BINARY_DIR}/${PROJECT_FOLDER}/Resources"
	)

endif()


message("\n")


