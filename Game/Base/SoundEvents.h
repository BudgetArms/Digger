﻿#pragma once


#include <unordered_map>


namespace Game::Sounds
{
    enum class SoundEvents
    {
        GameplayMusic,
        CollectedEmerald,
        GoldBagCountdown,
        GoldBagFalling,
        PlayerHit,
        PlayerDeath,
        PlayerDeathLong,
        BallTravelingSound,
        BallHitSound,
    };


    static std::unordered_map<SoundEvents, int> g_sSoundEvents;

    // gives warning if not used
#pragma warning (push)
#pragma warning(disable : 4505)

    static int GetSoundId(SoundEvents event)
    {
        auto it = g_sSoundEvents.find(event);

        // sound not found
        if (it == g_sSoundEvents.end())
            return -1;

        return it->second;
    }

#pragma warning (pop)

}

