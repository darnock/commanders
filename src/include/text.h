#ifndef TEXT_H
#define	TEXT_H

#include <SDL2/SDL.h>
#include <string>
#include "sign.h"
#include <map>

/**
 * \brief The type used to creat and show message on screen
*/
class Text{
private:
    /** pointer to renderer */
    SDL_Renderer* renderer;
    /** x - x position */
    int x;
    /** y - y position */
    int y;
    /** n - numbers of character in message */
    int n;
    /** max_x - x maximal position */
    int max_x;
    /** max_y - y maximal position */
    int max_y;
    /** width of message */
    int w;
    /** height of message */
    int h;
    /** message */
    std::string txt;
    /**  pointer to hash map\n ascii char - pointer to SDL_Texture */
    std::map<unsigned char, SDL_Texture *> map_ascii;
    
    SDL_Texture * creat_Texture(char ch, TTF_Font * font);
    
    void init_map_ascii();

public:
    Text(SDL_Renderer* renderer, int x, int y, int max_x, int max_y);
    void change_txt(std::string * msg);
    void render();
    virtual ~Text();
};

#endif	/* TEXT_H */

