
#include "Application.h"

void Application::Loop(){

    ApplicationManager::Instance()->Loop();
    FPSControl::Instance()->Loop();

}
