//here will be methods and objects related with units in game
#include <SDL2/SDL.h>
#include "include/units.h"
#include "include/game.h"
#include "include/game_settings.h"

//definicje klas znajduja sie w units.h 

using namespace std;

//*******************************************************************************************************
// METHODS OF CZLOWIEKI											*
//*******************************************************************************************************

void czlowieki::hide()	
	{
		//pixels[y*XRES+x]=oldcolor; //test
		pixels[y*resx+x]=oldcolor; //test
	}

void czlowieki::show()
	{
	//	oldcolor=pixels[y*XRES+x]; //test
	//	pixels[y*XRES+x]=color;
		oldcolor=pixels[y*resx+x]; //test
		pixels[y*resx+x]=color;

        }

void czlowieki::move(direction dir)
{
    /** store old x position */
    int old_x=x;
    /** store old y position */
    int old_y=y;
    hide();
    switch(dir)
    {
        case dup:
        y=y-1;
        break;

        case ddown:
        y=y+1;
        break;

        case dleft:
        x=x-1;
        break;

        case dright:
        x=x+1;
        break;

        case dupleft:
        y=y-1;
        x=x-1;
        break;

        case dupright:
        y=y-1;
        x=x+1;
        break;

        case ddownleft:
        y=y+1;
        x=x-1;
        break;

        case ddownright:
        y=y+1;
        x=x+1;
        break;
    }
    if(x>=resx) x=0;
    if(y>=resy) y=0;
    if(x<0) x=resx-1;
    if(y<0) y=resy-1;
    if(pixels[y*resx+x]==0){ 	//jesli tlo jest czarne
      show();			//to rysuj
    }else{                          // if bg is not black, do not move
        // restore old x position
        x=old_x;
        // restore old x position
        y=old_y;

        show();
    }
}

void czlowieki::testinit(int nx, int ny, int ncolor)
	{
		x=nx;
		y=ny;
		color=ncolor;
		oldcolor=0;
	}


//*******************************************************************************************************
// METHODS OF SZEREGOWY											*
//*******************************************************************************************************
void szeregowy::init(int nx, int ny, int ncolor)
	{
		color=ncolor;
		x=nx;
                y=ny;
                hp=100000;      //100k na szeregowego
                shield=30000;   //ordinary meat has 30k shield. Together with hp ~130k of hit points
	}

