#pragma once

#include "stateIntro.h"
#include "stateMainMenu.h"
#include "stateGame.h"
#include "statePaused.h"
#include "sharedContext.h"

#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>
#include <algorithm>


enum class StateType
{
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};


using StateContainer = std::vector<std::pair<StateType, BaseState*>>;					// state container
using TypeContainer = std::vector<StateType>;											// type container
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;	// state factory


class StateManager
{
public:
	StateManager(SharedContext* l_shared);
	~StateManager();

	void Update(const sf::Time & l_time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType & l_type);

	void SwitchTo(const StateType & l_type);
	void Remove(const StateType & l_type);

private:
	// methods
	void CreateState(const StateType & l_type);
	void RemoveState(const StateType & l_type);

	template<typename T>
	void RegisterState(const StateType & l_type)
	{
		m_stateFactory[l_type] = [this]()->BaseState*
		{
			return new T(this);
		};
	}

	// members
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};
