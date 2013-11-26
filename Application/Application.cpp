#include "Application.h"


Application::Application(){
    this->game_display = nullptr;
    this->running = true;
}

Application* Application::Instance(){
    static Application instance;
    return &instance;
}

