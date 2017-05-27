#include "include/text.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "include/sign.h"
#include <map>
#include "include/game.h"

/**
 * \brief default constructor
 * @param renderer
 * @param x position
 * @param y position
 * @param max_x maximum position of text (horizontally), usually x resolution
 * @param max_y maximum position of text (vertical), usually y resolution
 */
Text::Text(SDL_Renderer* renderer, int x, int y, int max_x, int max_y){
    Text::renderer = renderer;
    Text::x=x;
    Text::y=y;
    Text::max_x=max_x;
    Text::max_y=max_y;
    // init ascii map
    init_map_ascii();
}

/**
 * \brief default destructor
 */
Text::~Text(){
    for(unsigned char ch = 32; ch < 127; ch++){
        SDL_DestroyTexture(map_ascii[ch]);
    }
    map_ascii.clear();
}

/**
 * 
 * @param ch - character
 * @param font - ttf font
 * @return texture created from character
 */
SDL_Texture * Text::creat_Texture(char ch, TTF_Font * font){
    SDL_Texture * texture = NULL;
    SDL_Color color = {255,255,255};
    SDL_Surface* solid = TTF_RenderText_Solid( font, (std::string(ch+(std::string)"")).c_str(), color );
    texture = SDL_CreateTextureFromSurface( renderer, solid );
    SDL_FreeSurface(solid);
    return texture;

}

/**
 * inicialization of ascii map
 */
void Text::init_map_ascii(){
    TTF_Font * font = TTF_OpenFont("data/fonts/times.ttf",12);
    for(unsigned char ch = 32;ch < 127;ch++){
        map_ascii[ch] = Text::creat_Texture(ch, font);
    }
    TTF_CloseFont(font);
}
/**
 * \brief store message; check and correct text if text is out off screen
 * @param msg to draw
 */
void Text::change_txt(std::string * msg){
    // get length of txt
    Text::n = msg->length();
    // store msg
    txt = *msg ;
    SDL_Rect srcrect={0,0,0,0}, dstrect={x,y,0,0};
    // offset of characters 
    int offset_x=x;
    for(int i=0;i<Text::n;i++){
        SDL_QueryTexture(map_ascii[(*msg)[i]], NULL, NULL, &(srcrect.w) , &(srcrect.h) );
        dstrect.w=srcrect.w;
        dstrect.h=srcrect.h;
        if(i>0){
            dstrect.x=offset_x;
        }
        offset_x+=dstrect.w;
    }
    Text::h = dstrect.h;
    Text::w = offset_x-x;
    
    if( (Text::x + Text::w) > Text::max_x ) {
        Text::x=Text::max_x-Text::w;
    }
    if( (Text::y + Text::h) > Text::max_y ) {
        Text::y=Text::max_y-Text::h;
    }
}
/**
 * this method must be called last\n 
 * after call of this method, changes to object will be discarded
 */
void Text::render(){
    SDL_Rect srcrect={0,0,0,0}, dstrect={x,y,0,0};
    srcrect={0,0,0,0};
    dstrect={x,y,0,0};
    int offset_x=x;
    for(int i=0;i<Text::n;i++){
        SDL_QueryTexture(map_ascii[txt[i]], NULL, NULL, &(srcrect.w) , &(srcrect.h) );
        dstrect.w=srcrect.w;
        dstrect.h=srcrect.h;
        if(i>0){
            dstrect.x=offset_x;
        }
        offset_x+=dstrect.w;
        SDL_RenderCopy(renderer,map_ascii[txt[i]],&srcrect, &dstrect);
    }
}
