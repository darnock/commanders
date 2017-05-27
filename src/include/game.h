#ifndef GAME_H
#define	GAME_H

#include <SDL2/SDL.h>
#include "units.h"

extern Uint32 *pixels;
extern int resx;
extern int resy;

struct Bits{
    unsigned char fps:1; // fps flag 1 - fps turn on, 0 fps off
    unsigned char fps_terminal:1; // cout fps to terminal
    unsigned char quit:1; // 1 - quit game \n 0 - runing game
    unsigned char bit3:1; // free flag
    unsigned char bit4:1; // free flag
    unsigned char bit5:1; // free flag
    unsigned char bit6:1; // free flag
    unsigned char bit7:1; // free flag
};

typedef struct game_flags{
    union{
        Bits bits;
        unsigned char fps:2; // acces to fps flags
        unsigned char all;   // acces to all flags
    };
}game_flags;

class Game{
private:
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Texture * texture = NULL;
    SDL_Event event;
    /** true - left mouse button click */
    bool leftMouseButtonDown;
    /** used in movement of units */
    int hlp;
    /** used in movement of units */
    direction dir;
    /** width of window in pixels */
    unsigned int settings_xres;
    /** height of window in pixels */
    unsigned int settings_yres;
public:
    /** game flags */
    game_flags flags;
    /** true - quit game\n false - runing game */
//    bool quit;
    void init(game_flags flags);
    void render();
    void update();
    void handleEvents();
    void clean();
    int get_width();
    int get_height();
    void read_settings();
    void write_settings();
    void draw_fps();
};

#endif	/* GAME_H */
