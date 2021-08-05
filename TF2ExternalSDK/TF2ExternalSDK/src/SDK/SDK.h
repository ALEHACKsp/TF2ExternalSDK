#pragma once
#include "EntityCache/EntityCache.h"

namespace G
{
	inline CGlobalVarsBase GlobalVars = {};
}

#define TICK_INTERVAL G::GlobalVars.interval_per_tick
#define TIME_TO_TICKS(dt) (static_cast<int>(0.5f + static_cast<float>(dt) / TICK_INTERVAL))
#define TICKS_TO_TIME(t) (TICK_INTERVAL * t)