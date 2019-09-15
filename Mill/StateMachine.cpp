#include "stdafx.h"
#include "StateMachine.h"

namespace NWP{
	void StateMachine::AddState(StateRef newState,bool isReplacing) {
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges() {
		if (this->_isRemoving && this->_state) {
			if (this->_previousState) {
				this->_state = std::move(this->_previousState);
				this->_state->Resume();
				this->_previousState = nullptr;
			}
			else {
				this->_state = nullptr;
			}
			this->_isRemoving = false;
		}

		if (this->_isAdding) {
			if (this->_state && !this->_isReplacing) {
				this->_state->Pause();
				this->_previousState = std::move(this->_state);
			}
			this->_state = (std::move(this->_newState));
			this->_state->Init();
			this->_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveState() {
		return this->_state;
	}
}