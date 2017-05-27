#include <ctime>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include "include/game.h"
#include "include/game_settings.h"
#include "include/units.h"
#include "include/text.h"
#include "include/sign.h"
//uncomment to turn off assert functions
#define NDEBUG
#include <assert.h>
#include <vector>
#include <sstream>

Uint32 * pixels = NULL;

 int resx=0; //globalna rozdzielczosc na x
 int resy=0; //j.w. Y. KORZYSTAJA Z TEGO FUNKCJE Z units.cpp

szeregowy zolnierze[ILEOBJ]; //deklaracja ILEOBJ ludzi
szeregowy killer[1];

char return_value=0;

/** pointer to msg with fps */
//Text msg_FPS = NULL;

void Game::init(game_flags flags){

    // copy game flags
    Game::flags = flags;

    // left mouse buton click set to false
    leftMouseButtonDown = false;
    // init SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // init ttf
    TTF_Init();
    srand( time( NULL ) );
    
    // read settings
    read_settings();
    
    resx=get_width(); //robic to tylko raz a nie przy kazdym uzyciu 
    resy=get_height(); // jw.

    pixels =  new Uint32[resx * resy];

    // creat window
    window = SDL_CreateWindow("MISA v0.1b",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resx, resy, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, resx, resy);

    memset(pixels, 0, resx * resy * sizeof(Uint32)); //czyszczenie ekranu

    for(int x=0; x<ILEOBJ; x++) zolnierze[x].init(rand()%(resx-1),rand()%(resy-1),0x00ff00);
    
    // green killer pixel
    for(int x=0; x<1; x++) killer[x].init(resx/2,resy/2,0xff0000);
    
}
void Game::handleEvents(){
    while(SDL_PollEvent(&event) > 0)
    {
        //SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                leftMouseButtonDown = true;
        case SDL_MOUSEMOTION:
            if (leftMouseButtonDown)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                pixels[mouseY * resx + mouseX] = 0xffffffff;
            }
            break;
        /*any keyboard key pressed*/
        case SDL_KEYDOWN:
            /*exit game*/
            if(event.key.keysym.sym==SDLK_ESCAPE)
                Game::flags.bits.quit = true;
            //turn fps on/off
            if(event.key.keysym.sym==SDLK_f){
                // increment to overflow then start from 0
                Game::flags.fps++;
                if(Game::flags.fps==0){
                    std::cout<<"\t fps to game window off"<<std::endl;
                    std::cout<<"\t fps to terminal off"<<std::endl;
                }else if(Game::flags.fps==1){
                    std::cout<<"\t fps to game window on"<<std::endl;
                }else if(Game::flags.fps==2){
                    std::cout<<"\t fps to game window off"<<std::endl;
                    std::cout<<"\t fps to terminal on"<<std::endl;
                }else if(Game::flags.fps==3){
                    std::cout<<"\t fps to game window on"<<std::endl;
                    std::cout<<"\t fps to terminal on"<<std::endl;
                }
            }
            break;
        case SDL_QUIT:
            Game::flags.bits.quit = true;
            break;
        }
    }
}
void Game::render(){
    return_value = SDL_UpdateTexture(texture, NULL, pixels, resx * sizeof(Uint32));
    assert( return_value == 0);
    
    for(int x=0; x<ILEOBJ; x++) 
            {
            hlp=rand()%8; 
            if(hlp==0) dir=dup;		
            if(hlp==1) dir=ddown;		
            if(hlp==2) dir=dleft;		
            if(hlp==3) dir=dright;		
            if(hlp==4) dir=dupleft;		
            if(hlp==5) dir=dupright;		
            if(hlp==6) dir=ddownleft;		
            if(hlp==7) dir=ddownright;		

            zolnierze[x].move(dir);
            }
    //for (int y=0; y<=YRES-1; y++)
    //for (int x=0; x<=XRES-1; x++) 
//		pixels[y*XRES+x]=rand() *1000;
    //SDL_Delay(10);

    return_value = SDL_RenderClear(renderer);
    assert( return_value == 0);
    return_value = SDL_RenderCopy(renderer, texture, NULL, NULL);
    assert( return_value == 0);
    
    // if any of fps bit is set
    if(Game::flags.fps){
        // draw FPS's
        draw_fps();
    }
    

/*
//TODO rewrite all lines
    std::cout<<std::endl<<"+";
    for(int i =0;i< resx ;i++)
        std::cout<<"-";
    std::cout<<"+"<<std::endl<<"|";
    for(int i=1;i<=resy*resx;i++){
        switch(pixels[i]){
            case 0x00ff00:
                std::cout<<' ';
            break;
            case 0x000000:
                std::cout<<' ';
            break;
            case 0xff0000:
                std::cout<<'K';
            break;
            default:
                std::cout<<" ";
            break;
        }
        if( (i!=0) && ((i%(resx))==0) )
            std::cout<<"|";
        if( (i!=resy*resx ) && (i!=0) && ((i%(resx))==0) )
            std::cout<<std::endl<<"|";
        
    }
    std::cout<<std::endl<<"+";
    for(int i =0;i< resx ;i++)
        std::cout<<"-";
    std::cout<<"+"<<std::endl;
*/
    static direction last;
    static int last_x;
    static int last_y;
    
    //store last x position
    last_x=killer[0].x;
    
    //store last y position
    last_y=killer[0].y;
    
    if( (killer[0].y!=0) && (killer[0].x!=0)){
        if(pixels[killer[0].y*resx+killer[0].x+1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y) && (zolnierze[i].x == killer[0].x+1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(dright);
                    last=dright;
                }
            }
        }else if(pixels[(killer[0].y-1)*resx+killer[0].x+1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y-1) && (zolnierze[i].x == killer[0].x+1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(dupright);
                    last=dupright;
                }
            }
        }else if(pixels[(killer[0].y+1)*resx+killer[0].x+1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y+1) && (zolnierze[i].x == killer[0].x+1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(ddownright);
                    last=ddownright;
                }
            }
        }else if(pixels[(killer[0].y+1)*resx+killer[0].x] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y+1) && (zolnierze[i].x == killer[0].x) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(ddown);
                    last=ddown;
                }
            }
        }else if(pixels[(killer[0].y+1)*resx+killer[0].x-1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y+1) && (zolnierze[i].x == killer[0].x-1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(ddownleft);
                    last=ddownleft;
                }
            }
        }else if(pixels[(killer[0].y)*resx+killer[0].x-1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y) && (zolnierze[i].x == killer[0].x-1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(dleft);
                    last=dleft;
                }
            }
        }else if(pixels[(killer[0].y-1)*resx+killer[0].x-1] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y-1) && (zolnierze[i].x == killer[0].x-1) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(dupleft);
                    last=dupleft;
                }
            }
        }else if(pixels[(killer[0].y-1)*resx+killer[0].x] != 0){
            for(int i=0;i<ILEOBJ;i++){
                if( (zolnierze[i].y == killer[0].y-1) && (zolnierze[i].x == killer[0].x) ){
                    zolnierze[i].color=0x000000;
                    killer[0].move(dup);
                    last=dup;
                }
            }
        }else{
            killer[0].move(last);
        }
    }
    //if actual position is the same as in last frame
    if( (last_x==killer[0].x) && (last_y==killer[0].y)){
        //force move
        killer[0].move(last);
    }
//TODO rewrite all lines
    
    
    //Update the screen with rendering performed, function SDL_RenderPresent must be on end of frame
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    delete[] pixels;
    // write settings on quit
    write_settings();
}

/**
 * 
 * @return the height of the game window
 */
int Game::get_height(){
    return settings_yres;
}
/**
 * 
 * @return the width of the game window
 */
int Game::get_width(){
    return settings_xres;
}

/**
 * read height and width from file settings.txt to settings_xres settings_yres
 */
void Game::read_settings(){
    std::ifstream in("settings.txt");
    if(in.is_open()){
        char ch=0;
        std::string line="";
        unsigned int setx=0;
        unsigned int sety=0;
        while(in.get(ch)){
            // if encountered tag "end of line"
            if(ch=='\n'){
                if(line.find("height=",0)!=std::string::npos){
                    sety=atoi(line.substr(((std::string)"height=").size()+1,line.size()-((std::string)"height=").size()).c_str());
                }else if(line.find("width=",0)!=std::string::npos){
                    setx=atoi(line.substr(((std::string)"width=").size()+1,line.size()-((std::string)"width=").size()).c_str());
                }
                line="";
                }
            line=line+ch;
        }
        in.close();
        if(setx!=0 && sety!=0){
            settings_xres = setx;
            settings_yres = sety;
        }
        //set default values
        else{
            settings_xres = 800;
            settings_yres = 600;
        }
    }
    //set default values
    else{
        settings_xres = 800;
        settings_yres = 600;
    }
    in.close();
}
/**
 * overwrite file settings.txt with new height and width, file is created if do not exists
 */
void Game::write_settings(){
    std::ofstream out("settings.txt");
    if(out.is_open()){
        out<<"#settings\n";
        out<<"width=" << settings_xres <<"\n";
        out<<"height="<< settings_yres <<"\n";
    }
    out.close();
}

void Game::draw_fps(){
    /** counter in ms \n reset if reach 1000ms */
    static unsigned int timeCounter=0;
    static double FPS=0;
    static int ramka=0;
    static unsigned int last_frame_time, cur_frame_time;
    ramka++; //ilosc klatek    
    last_frame_time = cur_frame_time;
    cur_frame_time = SDL_GetTicks();
    timeCounter += cur_frame_time - last_frame_time;
    // after 1000ms
    if(timeCounter >= 1000 ){
        
        //calculate fps
        FPS = (ramka);
        //if fps terminal bit is set
        if(Game::flags.bits.fps_terminal){
            // print FPS on terminal
            std::cout<<"FPS: "<<FPS<<"\n";
            
            //count visible pixels
            int ct=0;
            for(int i=0;i<ILEOBJ;i++){
                if(zolnierze[i].color!=0)
                    ct++;
            }
            std::cout<<"\t green pixels on screen: "<<ct<<"\n";
        }
        // reset time counter 
        timeCounter = 0;
        ramka=0;
    }
    
    // if fps to screen bit is set
    if(Game::flags.bits.fps){
        // creat stream with fps
        std::ostringstream stream;
        // append strings
        stream<<"fps: "<<FPS;
        // creat string with fps
        std::string text = (char *)stream.str().c_str();
        // creat msg with default position
        static Text msg_FPS(renderer,0,resy, resx, resy);
        // Create msg to show on screen with info about fps
        msg_FPS.change_txt(&text);
        msg_FPS.render();
    }
}