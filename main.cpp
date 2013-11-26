#include "Application\Application.h"


int main(int argc, char** argv){
    Application::Instance();
    return Application::Instance()->Execute();
}
