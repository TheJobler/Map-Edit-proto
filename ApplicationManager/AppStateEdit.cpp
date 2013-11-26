#include "ApplicationStates.h"
#include "ApplicationManager.h"
#include "../Application/Application.h"

AppStateEdit::AppStateEdit(){
}

AppStateEdit* AppStateEdit::Instance(){
    static AppStateEdit instance;
    return &instance;
}

//Allows the player to move by reading the input from the keyboard and
//setting the appropriate movement flag for the player
void AppStateEdit::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode){
    switch(sym){
        case SDLK_1:{
            Menu::Instance()->SetActiveTile(0);
            break;
        }
        case SDLK_2:{
            Menu::Instance()->SetActiveTile(15);
            break;
        }
        case SDLK_3:{
            Menu::Instance()->SetActiveTile(31);
            break;
        }
        case SDLK_4:{
            break;
        }
        case SDLK_5:{
            break;
        }
        case SDLK_6:{
            break;
        }
        case SDLK_7:{
            break;
        }
        case SDLK_8:{
            break;
        }
        case SDLK_9:{
            break;
        }
        case SDLK_0:{
            break;
        }
        case SDLK_UP:{
            Camera::Instance()->Move(0,-5);
            break;
        }
        case SDLK_DOWN:{
            Camera::Instance()->Move(0,5);
            break;
        }
        case SDLK_LEFT:{
            Camera::Instance()->Move(-5,0);
            break;
        }
        case SDLK_RIGHT:{
            Camera::Instance()->Move(5,0);
            break;
        }
        case SDLK_TAB:{
            Menu::Instance()->show_menu = !(Menu::Instance()->show_menu);
            break;
        }
        case SDLK_SPACE:{
            Menu::Instance()->edit_mode = false;
            break;
        }
        case SDLK_ESCAPE:{
            Application::Instance()->Exit();
            break;
        }
        default:{
        }
    }
}

//resets the movement flag based on which key was released
void AppStateEdit::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode){
    switch(sym){
        case SDLK_SPACE:{
            Menu::Instance()->edit_mode = true;
            break;
        }
        default:{
        }
    }
}

void AppStateEdit::OnMouseMove(int x,int y,int rel_x,int rel_y,bool left,bool right,bool middle){
    Menu::Instance()->SetCoords(x, y);
    if(Menu::Instance()->scroll_mode){
        Camera::Instance()->Move(-rel_x,-rel_y);
    }
    if(Menu::Instance()->add_mode){
        Menu::Instance()->SetTile(x,y);
    }
}

void AppStateEdit::OnLButtonDown(int x, int y){
    if(Menu::Instance()->edit_mode){
        Menu::Instance()->add_mode = true;
        Menu::Instance()->SetTile(x,y);
    }
    else{
        Menu::Instance()->scroll_mode = true;
    }
}

void AppStateEdit::OnLButtonUp(int x, int y){
    Menu::Instance()->scroll_mode = false;
    Menu::Instance()->add_mode = false;
}

void AppStateEdit::OnMouseWheel(bool up, bool down){
    if(up){
        if(Menu::Instance()->zoom_out){
            Menu::Instance()->zoom_out = false;
        }
        else{
            Menu::Instance()->zoom_in = true;
        }
    }
    if(down){
        if(Menu::Instance()->zoom_in){
            Menu::Instance()->zoom_in = false;
        }
        else{
            Menu::Instance()->zoom_out = true;
        }
    }
}

void AppStateEdit::Enter(ApplicationManager* application_manager){
    if(Map::Instance()->Load("resources/maps/1.map") == false){
        return;
    }

    if(Menu::Instance()->LoadFont("resources/fonts/Useable/elementary_gothic_bookhand/Elementary_Gothic_Bookhand.ttf",1) == false){
        return;
    }
    Menu::Instance()->LoadMap();

    Camera::Instance()->target_mode = Camera::TARGET_MODE::NORMAL;
}


//This method is called when the loop method of the application is executed.
//Execute updates all of the entitites, the camera player etcetera.
void AppStateEdit::Execute(ApplicationManager* application_manager){
    Menu::Instance()->Loop();
}


//When the state is changed from the game to another state this will be calle. It currently handles cleanup
//however this will need to change because when a pause state is added we do not want to destroy
//all of the loaded assests just to reload them from the beginning.
//This will be handled by the application state exit class' exit method
void AppStateEdit::Exit(ApplicationManager* application_manager){
    Map::Instance()->Save(true);
    Map::Instance()->Cleanup( );
    Menu::Instance()->Cleanup();
}


void AppStateEdit::Render(SDL_Surface* display_surface){

    Map::Instance()->
        Render(
            display_surface,
            -Camera::Instance()->Get_x(),
            -Camera::Instance()->Get_y()
        );

    Menu::Instance()->Render(display_surface);
}

