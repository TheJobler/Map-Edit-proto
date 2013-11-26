#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include <typeinfo>
#include "State.h"

template<class _StateMaster>
class StateMachine{

    public:
        StateMachine(_StateMaster* owner);
        virtual ~StateMachine(){};

    private:
        _StateMaster*        state_master;

        State<_StateMaster>* current_state;
        State<_StateMaster>* previous_state;
        State<_StateMaster>* global_state;

    public:

        void SetCurrentState (State<_StateMaster>* state);
        void SetPreviousState(State<_StateMaster>* state);
        void SetGlobalState  (State<_StateMaster>* state);

        void Update()const;
        void ChangeState(State<_StateMaster>* new_state);
        void RevertState();

        State<_StateMaster>* CurrentState() const;
        State<_StateMaster>* PreviousState()const;
        State<_StateMaster>* GlobalState()  const;

        bool InState(const State<_StateMaster>& state)const;

};


template<class _StateMaster>
StateMachine<_StateMaster>::StateMachine(_StateMaster* owner){
    state_master   = owner;
    current_state  = nullptr;
    previous_state = nullptr;
    global_state   = nullptr;
}

template<class _StateMaster>
void StateMachine<_StateMaster>::SetCurrentState(State<_StateMaster>* state){
    this->current_state = state;
}

template<class _StateMaster>
void StateMachine<_StateMaster>::SetPreviousState(State<_StateMaster>* state){
    this->previous_state = state;
}

template<class _StateMaster>
void StateMachine<_StateMaster>::SetGlobalState(State<_StateMaster>* state){
    this->global_state = state;
}

template<class _StateMaster>
void StateMachine<_StateMaster>::Update()const{

    if(global_state){
        global_state->Execute(state_master);
    }
    if(current_state){
        current_state->Execute(state_master);
    }

}

template<class _StateMaster>
void StateMachine<_StateMaster>::ChangeState(State<_StateMaster>* new_state){

    if(new_state != nullptr){
        this->previous_state = current_state;
        if(this->CurrentState()){
            this->current_state->Exit(state_master);
        }
        this->current_state = new_state;
        this->current_state->Enter(state_master);
    }

}

template<class _StateMaster>
void StateMachine<_StateMaster>::RevertState(){
    ChangeState(this->previous_state);
}

template<class _StateMaster>
State<_StateMaster>* StateMachine<_StateMaster>::CurrentState()const{
    return current_state;
}

template<class _StateMaster>
State<_StateMaster>* StateMachine<_StateMaster>::PreviousState()const{
    return previous_state;
}

template<class _StateMaster>
State<_StateMaster>* StateMachine<_StateMaster>::GlobalState()const{
    return global_state;
}

template<class _StateMaster>
bool StateMachine<_StateMaster>::InState(const State<_StateMaster>& state)const{
    return ( typeid(*current_state) == typeid(state) );
}




#endif
