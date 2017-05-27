#ifndef SIGN_H
#define	SIGN_H
#include <SDL2/SDL_ttf.h>
#include <string>

class Sign {
private:
    /** path with file name to font */
    std::string font_file;
    /** holder of a loaded font */
    TTF_Font *font;
    /** point size translates to pixel height */
    int ptsize;
    /** color of font */
    SDL_Color color;
    SDL_Texture * creat_char(SDL_Renderer* renderer, SDL_Rect *rect_FPS, char ch);
    /** source rectangle */
    SDL_Rect srcrect;
    /** destination rectangle */
    SDL_Rect desrect;
    /**  pointer to renderer */
    SDL_Renderer* ptr_renderer;
    /** pointer to texture */
    SDL_Texture* ptr_texture;
public:
    Sign();
    Sign(const Sign& orig);
    virtual ~Sign();
    void show_char(SDL_Renderer* renderer,int x,int y, char ch);
    void show_char(SDL_Renderer* renderer,char ch);
    void move(int x , int y);
    void render();
    int get_x();
    int get_y();
    int get_w();
    int get_h();
    void clear();
private:

};

#endif	/* SIGN_H */

