﻿cmake_minimum_required(VERSION 3.26)
project(Game)

# CMake inspired by Mikail Kahya

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_FOLDER Game)

message("\nMain CMakeList")


set(STEAMWORKS_SDK_PATH "${CMAKE_SOURCE_DIR}/3rdParty/steamworks")
set(ENABLE_STEAMWORKS ON) # temp because cann't be assed to add/remove compile option

set(EMSCRIPTEN OFF)
set(ENABLE_CONSOLE ON)


if(ENABLE_STEAMWORKS AND NOT EMSCRIPTEN)
    
    message("Using Steamworks")

    if(EXISTS "${STEAMWORKS_SDK_PATH}")
        message(STATUS "Steamworks SDK found at: ${STEAMWORKS_SDK_PATH}")
        set(STEAMWORKS_AVAILABLE TRUE)
    else()
        message(WARNING "Steamworks SDK not found at: ${STEAMWORKS_SDK_PATH}")
        set(STEAMWORKS_AVAILABLE FALSE)
    endif()

endif()


# Force updates submodule, so that it's exactly identical
execute_process(
  COMMAND git submodule update --init --remote --force
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


add_subdirectory(BudgetArmsEngine)
add_subdirectory(Game)


