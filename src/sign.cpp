#include "include/sign.h"
#include "include/game.h"
#include "include/game_settings.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

Sign::Sign() {
    font_file = "data/fonts/times.ttf";
    ptsize = 16;
    color = {255,255,255};
    font = TTF_OpenFont(font_file.c_str(),ptsize);
}

Sign::Sign(const Sign& orig) {
}

Sign::~Sign() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(ptr_texture);
}


SDL_Texture * Sign::creat_char(SDL_Renderer* renderer, SDL_Rect *rect_FPS, char ch){
    ptr_renderer = renderer;
    TTF_Font * font = TTF_OpenFont(font_file.c_str(),ptsize);
    SDL_Surface* solid = TTF_RenderText_Solid( font, (std::string(ch+(std::string)"")).c_str(), color );
    ptr_texture = SDL_CreateTextureFromSurface( renderer, solid );
    SDL_FreeSurface(solid);
    int width, height;
    SDL_QueryTexture(ptr_texture, NULL, NULL, &width , &height );
    (*rect_FPS).x = 0;
    (*rect_FPS).y = 0;
    (*rect_FPS).w = width;
    (*rect_FPS).h = height;
    TTF_CloseFont(font);
    return ptr_texture;
}
/**
 * 
 * @param renderer pointer to renderer
 * @param x position 
 * @param y position
 * @param ch character to show
 * @return 0 on success, or -1 on error
 */
void Sign::show_char(SDL_Renderer* renderer,int x,int y, char ch){
    ptr_renderer = renderer;
    creat_char(renderer,&srcrect,ch);
    desrect.w=srcrect.w;
    desrect.h=srcrect.h;
    desrect.x=x;
    desrect.y=y;
}

void Sign::show_char(SDL_Renderer* renderer,char ch){
    ptr_renderer = renderer;
    creat_char(renderer,&srcrect,ch);
    desrect.w=srcrect.w;
    desrect.h=srcrect.h;
}

/**
 * 
 * @param x move to position x
 * @param y move to position y
 */
void Sign::move(int x, int y){
    //do not move when move is not on screen
    if( (y>=0) && (y <= resx) )
        desrect.y = y;
    if( (x>=0) && (x <= resy) )
        desrect.x = x;
}
/**
 * this method must be called last\n 
 * after call of this method, changes to object will be discarded
 */
void Sign::render(){
    SDL_RenderCopy(ptr_renderer, ptr_texture, &srcrect, &desrect);
}

/**
 * 
 * @return x position
 */
int Sign::get_x(){
    return desrect.x;
}
/**
 * 
 * @return y position
 */
int Sign::get_y(){
    return desrect.y;
}
/**
 * 
 * @return width of texture
 */
int Sign::get_w(){
    return desrect.w;
}
/**
 * 
 * @return height of texture
 */
int Sign::get_h(){
    return desrect.h;
}

void Sign::clear(){
    SDL_DestroyTexture(ptr_texture);
}
