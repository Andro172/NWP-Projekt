#pragma once
#include "stdafx.h"
#include <stack>
#include "State.h"

namespace NWP {
	typedef std::unique_ptr<State> StateRef;

	class StateMachine {
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();

		StateRef &GetActiveState();
	private:
		std::stack<StateRef> _states;
		StateRef _newState;

		bool _isRemoving = false;
		bool _isAdding = false;
		bool _isReplacing = false;
	};
}