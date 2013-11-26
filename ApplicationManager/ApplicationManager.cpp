
#include "ApplicationManager.h"
#include "ApplicationStates.h"

ApplicationManager::ApplicationManager(){
    state_machine = new StateMachine<ApplicationManager>(this);
}

ApplicationManager* ApplicationManager::Instance(){
    static ApplicationManager instance;
    return &instance;
}

void ApplicationManager::HandleEvent(SDL_Event* event){
    if(this->GetFSM()->CurrentState()){
        this->GetFSM()->CurrentState()->HandleEvent(event);
    }
}

void ApplicationManager::Loop(){
    if(this->GetFSM()->CurrentState()){
        this->GetFSM()->CurrentState()->Execute(this);
    }
}

void ApplicationManager::Render(SDL_Surface* display_surface){
    if(this->GetFSM()->CurrentState()){
        this->GetFSM()->CurrentState()->Render(display_surface);
    }
}

void ApplicationManager::SetActiveState(int state_id){

    switch(state_id){
        case ApplicationManager::STATE::INTRO:{
            this->GetFSM()->ChangeState(AppStateIntro::Instance());
            break;
        }
        case ApplicationManager::STATE::EDIT:{
            this->GetFSM()->ChangeState(AppStateEdit::Instance());
            break;
        }
        case ApplicationManager::STATE::NONE:{
            if(this->GetFSM()->CurrentState()){
                this->GetFSM()->CurrentState()->Exit(this);
            }
        }
    }

}

StateMachine<ApplicationManager>* ApplicationManager::GetFSM()const{
    return state_machine;
}


