#include <SDL2/SDL.h>
#include "include/main.h"
#include "include/game.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <bitset>

/*
 * fix for command line
 * if this define is commented then command line does not work
 */
#define SDL_main main

extern void print_help();

int main(int argc, char ** argv)
{
    game_flags flags;
    // reset all flags, turn all off
    flags.all = 0;
    if(argc>1){
        for(int i = 1; i < argc; i++){
            if(argv[i][0]=='-'){
                switch((int)argv[i][1]){
                    case enum_cmd_para_FPS:
                        // turn on fps
                        flags.bits.fps = 1;
                    break;

                    case enum_cmd_para_HELP:
                    default:
                        print_help();
                        return 0;
                    break;
                }
            }else{
                print_help();
                return 0;
            }
        }
    }
    
    Game game;
    game.init(flags);
    // main loop of game
    while(!(game.flags.bits.quit)){
        game.handleEvents();
        game.render();
    }
    game.clean();

    return 0;
}
/**
 * \brief cout help message
 */
void print_help(){
    std::cout<<"\t -f turn on fps, default off"<<std::endl;
    std::cout<<"\t -h help message"<<std::endl;
}
