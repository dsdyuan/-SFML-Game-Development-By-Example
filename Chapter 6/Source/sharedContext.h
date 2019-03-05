#pragma once

#include "window.h"
#include "eventManager.h"

struct SharedContext
{
	SharedContext()
		: m_wind(nullptr), m_eventManager(nullptr)
	{
	}

	Window* m_wind;
	EventManager* m_eventManager;
};