
#include "Menu.h"


Menu::Menu(){

    this->show_menu = true;
    this->edit_mode = true;

    SetActiveTile(0);

    active_tile = "Active Tile: ";
    tile_id = "Tile ID: ";
    tile_type = "Tile Type: ";
    tile_coords = "Tile Co-ordinates: ";
    mouse_coords = "Mouse Co-ordinates: ";

    this->menu_font = nullptr;
    this->mouse_coordinates_txt = nullptr;
    this->tile_coordinates_txt = nullptr;
    this->tile_id_txt = nullptr;
    this->tile_type_txt = nullptr;
    this->active_tile_txt = nullptr;

    this->zoomOut = nullptr;

    this->tile_highlight = AppSurface::Load(
        "resources/gfx/tilesets/highlight2.png"
    );

    font_color = {180,190,200};

}

Menu* Menu::Instance(){
    static Menu instance;
    return & instance;
}

bool Menu::LoadFont(char* file, int font_num){
    if((menu_font = TTF_OpenFont(file, FONTSIZE/*, font_num*/)) ==  nullptr){
        return false;
    }
    return true;
}

void Menu::LoadMap(){

    for(unsigned j = Map::Instance()->map_size * AREA_HEIGHT; j > 0; --j){
        mMap.push_back(std::vector<Tile*>());
    }

    for(int A = 0, offset = 0; A < Map::Instance()->area_list.size(); ++A){
        if(A % Map::Instance()->map_size == 0 &&
           A - Map::Instance()->map_size >= 0){
               offset += Map::Instance()->map_size;
        }
        for(int i = 0, y = -1; i < Map::Instance()->area_list[A].tile_list.size(); ++i){
            if(i % AREA_WIDTH == 0){
                ++y;
            }
            mMap[y + offset].push_back(&Map::Instance()->area_list[A].tile_list[i]);
        }
    }
}

void Menu::SetTile(int x, int y){
    /*
    the set tile function is based on a binary significant digit algorithm which will
    simulate each corner of the tiles having a binary digit represent what type of tile
    it is supposed to be;
    the  cornersrs are represented by ul, ur, ll, lr being upper left, upper right,
    lower left, and lower right respectively.
    the significance of the bits from most to least is as follows:

        | lr | ll |  ur |  ul | tile_id
        | 0  | 0  |  0  |  0  | tile ->  0
        | 0  | 0  |  0  |  1  | tile ->  1
        | 0  | 0  |  1  |  0  | tile ->  2
        | 0  | 0  |  1  |  1  | tile ->  3
        | .  | .  |  .  |  .  | tile -> ...
        | 1  | 1  |  0  |  0  | tile ->  12
        | 1  | 1  |  0  |  1  | tile ->  13
        | 1  | 1  |  1  |  0  | tile ->  14
        | 1  | 1  |  1  |  1  | tile ->  15

    */

    //if(tileset_surface == nullptr){
    //    return;
    //}
    static Tile* tmp_tile = nullptr;

    int tileset_w = 1024/64;
    //int tileset_w = tileset_surface->w / TILE_SIZE;

    int tile_x = ((x + Camera::Instance()->Get_x())/TILE_SIZE);
    int tile_y = ((y + Camera::Instance()->Get_y())/TILE_SIZE);

    if(tile_x >= 0 && tile_y >= 0){
        *(mMap[tile_y][tile_x]) = this->ActiveTile;

        if(tile_x - 1 >= 0 && mMap[tile_y][tile_x - 1]){//left
            tmp_tile = mMap[tile_y][tile_x - 1];
            if(tmp_tile->ur != ActiveTile.ul || tmp_tile->lr != ActiveTile.ll){
                tmp_tile->ur = ActiveTile.ul;
                tmp_tile->lr = ActiveTile.ll;

                //the binary equivalent is used to determine the
                //proper column of the transition tile.
                // it basically serves the function of finding out out
                // which bits on a tile are turned off or on.
                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if((tile_x + 1) < mMap[0].size() && mMap[tile_y][tile_x + 1]){//right
            tmp_tile = mMap[tile_y][tile_x + 1];
            if(tmp_tile->ul != ActiveTile.ur || tmp_tile->ll != ActiveTile.lr){
                tmp_tile->ul = ActiveTile.ur;
                tmp_tile->ll = ActiveTile.lr;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if(tile_y - 1 >= 0 && mMap[tile_y - 1][tile_x]){//top
            tmp_tile = mMap[tile_y - 1][tile_x];
            if(tmp_tile->ll != ActiveTile.ul || tmp_tile->lr != ActiveTile.ur){
                tmp_tile->ll = ActiveTile.ul;
                tmp_tile->lr = ActiveTile.ur;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if(tile_y + 1 < mMap.size() && mMap[tile_y + 1][tile_x]){//bottom
            tmp_tile = mMap[tile_y + 1][tile_x];
            if(tmp_tile->ul != ActiveTile.ll || tmp_tile->ur != ActiveTile.lr){
                tmp_tile->ul = ActiveTile.ll;
                tmp_tile->ur = ActiveTile.lr;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if(tile_x - 1 >= 0 && tile_y - 1 >= 0 && mMap[tile_y - 1][tile_x - 1]){//upper left
            tmp_tile = mMap[tile_y - 1][tile_x - 1];
            if(tmp_tile->lr != ActiveTile.ul){
                tmp_tile->lr = ActiveTile.ul;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if((tile_x + 1) < mMap[0].size() && tile_y - 1 >= 0 && mMap[tile_y - 1][tile_x + 1]){// upper right
            tmp_tile = mMap[tile_y - 1][tile_x + 1];
            if(tmp_tile->ll != ActiveTile.ur){
                tmp_tile->ll = ActiveTile.ur;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if(tile_x - 1 >= 0 && tile_y + 1 < mMap.size() && mMap[tile_y + 1][tile_x - 1]){// botttom left
            tmp_tile = mMap[tile_y + 1][tile_x - 1];
            if(tmp_tile->ur != ActiveTile.ll){
                tmp_tile->ur = ActiveTile.ll;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
        if(tile_x + 1 < mMap[0].size() && tile_y + 1 < mMap.size() && mMap[tile_y + 1][tile_x + 1]){// bottom right
            tmp_tile = mMap[tile_y + 1][tile_x + 1];
            if(tmp_tile->ul != ActiveTile.lr){
                tmp_tile->ul = ActiveTile.lr;

                int binary_equiv = MAX(
                        MAX((tmp_tile->ul), (tmp_tile->ur)),
                        MAX((tmp_tile->ll), (tmp_tile->lr))
                    );

                int trans_col = 0;
                if(binary_equiv % tileset_w != 0){

                    if(tmp_tile->lr == binary_equiv){
                        trans_col += 8;
                    }
                    if(tmp_tile->ll == binary_equiv){
                        trans_col += 4;
                    }
                    if(tmp_tile->ur == binary_equiv){
                        trans_col += 2;
                    }
                    if(tmp_tile->ul == binary_equiv){
                        trans_col += 1;
                    }
                }
                int tmp_tile_h = tmp_tile->tile_id / tileset_w;
                int ActiveTile_h = this->ActiveTile.tile_id / tileset_w;
                if(tmp_tile_h == ActiveTile_h){
                    tmp_tile->tile_id = tmp_tile->tile_id
                        +(trans_col - (tmp_tile->tile_id % tileset_w));
                }
                else{
                    tmp_tile->tile_id =
                        (MAX(tmp_tile_h, ActiveTile_h) - MIN(tmp_tile_h, ActiveTile_h))
                        * (tmp_tile->tile_id + (trans_col - (tmp_tile->tile_id % tileset_w)));
                }


            }
            tmp_tile = nullptr;
        }
    }

}

void Menu::SetActiveTile(int tile_id){
    this->ActiveTile.tile_id = tile_id;
    this->ActiveTile.ul = tile_id;
    this->ActiveTile.ll = tile_id;
    this->ActiveTile.ur = tile_id;
    this->ActiveTile.lr = tile_id;
    this->ActiveTile.type_id = 1;
}

void Menu::SetCoords(int rel_x, int rel_y){

    position.x = rel_x;
    position.y = rel_y;

    std::stringstream stream;
    stream << std::setw(6) << (rel_x + Camera::Instance()->Get_x());
    std::string tmpx = stream.str();
    stream.str(std::string());
    stream << std::setw(6) << (rel_y + Camera::Instance()->Get_y());
    std::string tmpy = stream.str();

    mouse_coords = "Mouse Co-ordinates: (" + tmpx + ", " + tmpy +" )";

    stream.str(std::string());
    stream << std::setw(4) << ((rel_x + Camera::Instance()->Get_x())/TILE_SIZE);
    tmpx = stream.str();
    stream.str(std::string());
    stream << std::setw(4) << ((rel_y + Camera::Instance()->Get_y())/TILE_SIZE);
    tmpy = stream.str();

    tile_coords  =  "Tile Co-ordinates: (" + tmpx + ", " + tmpy +" )";
}



void Menu::Loop(){
    if(show_menu && menu_font){
        if(mouse_coordinates_txt){
            SDL_FreeSurface(mouse_coordinates_txt);
            mouse_coordinates_txt = nullptr;
        }
        mouse_coordinates_txt
            = TTF_RenderText_Blended(menu_font, mouse_coords.c_str(), font_color);

        if(tile_coordinates_txt){
            SDL_FreeSurface(tile_coordinates_txt);
            tile_coordinates_txt = nullptr;
        }
        tile_coordinates_txt
            = TTF_RenderText_Blended(menu_font, tile_coords.c_str(),  font_color);

        if(active_tile_txt == nullptr){
            active_tile_txt =
                TTF_RenderText_Blended(menu_font, active_tile.c_str(), font_color);
        }
    }
}

void Menu::Render(SDL_Surface* display_surface){
    if(display_surface == nullptr || show_menu == false){
        return;
    }

    //if(zoom_in){
    //    if(Menu::Instance()->zoomOut){
    //        SDL_FreeSurface(Menu::Instance()->zoomOut);
    //        Menu::Instance()->zoomOut = nullptr;
    //    }
    //    Menu::Instance()->zoomOut = Menu::Instance()->ScaleSurface(
    //            display_surface,
    //            display_surface->w * 1.5,
    //            display_surface->h * 1.5
    //        );
    //
    //    if(Menu::Instance()->zoomOut){
    //    AppSurface::Instance()->Draw(
    //            display_surface,
    //            Menu::Instance()->zoomOut,
    //            0, 0
    //        );
    //    }
    //}
    //
    //if(zoom_out){
    //    if(Menu::Instance()->zoomOut){
    //        SDL_FreeSurface(Menu::Instance()->zoomOut);
    //        Menu::Instance()->zoomOut = nullptr;
    //    }
    //    Menu::Instance()->zoomOut = Menu::Instance()->ScaleSurface(
    //            display_surface,
    //            display_surface->w * 0.5,
    //            display_surface->h * 0.5
    //        );
    //
    //    if(Menu::Instance()->zoomOut){
    //    AppSurface::Instance()->Draw(
    //            display_surface,
    //            Menu::Instance()->zoomOut,
    //            0, 0
    //        );
    //    }
    //}

    if(edit_mode){

        if(position.x >= 0 && position.y >= 0){
        AppSurface::Instance()->Draw(
            display_surface,
            tile_highlight,
            ((position.x + Camera::Instance()->Get_x()) / TILE_SIZE)
            *TILE_SIZE - ( Camera::Instance()->Get_x()/*  - WWIDTH % TILE_SIZE*/),
            ((position.y + Camera::Instance()->Get_y()) / TILE_SIZE)
            *TILE_SIZE - ( Camera::Instance()->Get_y()/*  - WWIDTH % TILE_SIZE*/)
            );
        }/*
        else
        if(position.x < 0 && position.y >= 0){
        AppSurface::Instance()->Draw(
            display_surface,
            tile_highlight,
            ((position.x - Camera::Instance()->Get_x()) / TILE_SIZE)*TILE_SIZE - (Camera::Instance()->Get_x() - WWIDTH % TILE_SIZE),
            ((position.y + Camera::Instance()->Get_y()) / TILE_SIZE)*TILE_SIZE + (Camera::Instance()->Get_y() - WWIDTH % TILE_SIZE)
            );
        }
        else
        if(position.x >= 0 && position.y < 0){
        AppSurface::Instance()->Draw(
            display_surface,
            tile_highlight,
            ((position.x + Camera::Instance()->Get_x()) / TILE_SIZE)*TILE_SIZE + (Camera::Instance()->Get_x() - WWIDTH % TILE_SIZE),
            ((position.y - Camera::Instance()->Get_y()) / TILE_SIZE)*TILE_SIZE - (Camera::Instance()->Get_y() - WWIDTH % TILE_SIZE)
            );
        }
        else{
        AppSurface::Instance()->Draw(
            display_surface,
            tile_highlight,
            ((position.x - Camera::Instance()->Get_x()) / TILE_SIZE)*TILE_SIZE + (Camera::Instance()->Get_x() - WWIDTH % TILE_SIZE),
            ((position.y - Camera::Instance()->Get_y()) / TILE_SIZE)*TILE_SIZE + (Camera::Instance()->Get_y() - WWIDTH % TILE_SIZE)
            );
        }*/
    }

    if(mouse_coordinates_txt){
    AppSurface::Instance()->Draw(
        display_surface,
        mouse_coordinates_txt,
        10,WHEIGHT-25);
    }

    if(tile_coordinates_txt){
    AppSurface::Instance()->Draw(
        display_surface,
        tile_coordinates_txt,
        360,WHEIGHT-25);
    }

    if(active_tile_txt){
    AppSurface::Instance()->Draw(
        display_surface,
        active_tile_txt,
        640, WHEIGHT-25);
    }

}

void Menu::Cleanup(){
    if(mouse_coordinates_txt){
        SDL_FreeSurface(mouse_coordinates_txt);
    }
    mouse_coordinates_txt = nullptr;

    if(tile_coordinates_txt){
        SDL_FreeSurface(tile_coordinates_txt);
    }
    tile_coordinates_txt = nullptr;

    if(menu_font){
        TTF_CloseFont(menu_font);
    }
    menu_font = nullptr;

}

/*
SDL_Surface* Menu::ScaleSurface(SDL_Surface* display_surface, Uint16 Width, Uint16 Height){
    if(!display_surface || !Width || !Height){
        return nullptr;
    }

    SDL_Surface* ret_surface = SDL_CreateRGBSurface(
        display_surface->flags,
        Width, Height,
        display_surface->format->BitsPerPixel,
        display_surface->format->Rmask,
        display_surface->format->Gmask,
        display_surface->format->Bmask,
        display_surface->format->Amask
    );

    double str_x = (static_cast<double>(Width) / static_cast<double>(display_surface->w));
    double str_y = (static_cast<double>(Height)/ static_cast<double>(display_surface->h));

    for(Sint32 y = 0; y < display_surface->h ; ++y){
        for(Sint32 x = 0; x < display_surface->w; ++x){
            for(Sint32 iy = 0; iy < str_y; ++iy){
                for(Sint32 ix = 0;ix < str_x; ++ix){
                    DrawPixel(
                        ret_surface,
                        static_cast<Sint32>(str_x*x) + ix,
                        static_cast<Sint32>(str_y*y) + iy,
                        ReadPixel(display_surface, x, y)
                    );
                }
            }
        }
    }

    return ret_surface;
}
*/
