// Using SDL2's SDL_GetCurrentDisplayMode()
#include <SDL2/SDL.h>
#include <stdio.h>
#include "settings.h"
#include "class_save_file.h"

class screen
{
  private:
    unsigned int number_of_displays;                      // liczba wyświetlaczy
    unsigned int * number_of_display_modes;               // liczba trybów wyświetlania
    SDL_DisplayMode display_mode;                         //struktura opisująca tryb wyświetlania

    void get_display_mode(unsigned int display_index, unsigned int mode_index) 
    {
      SDL_GetDisplayMode(display_index, mode_index, &display_mode);                 //pobiera informacje o trybie wyświetlania
    }
    //inicjuje
    private: void init()
    {
      SDL_Init(SDL_INIT_VIDEO);
      this->number_of_displays = SDL_GetNumVideoDisplays();
      this->number_of_display_modes = new unsigned int[this->number_of_displays];
      for(unsigned int i = 0 ; i < this->number_of_displays ; ++i)
      {
        this->number_of_display_modes[i] = SDL_GetNumDisplayModes(i);
      }
    }
    //wypisuje dostępne wyświetlacze oraz ich tryby działania
    public: void log()
    {
      this->init();
      SDL_Log("Liczba ekranów = %d \n", this->number_of_displays);
      for(unsigned int i =0 ;i< this->number_of_displays;++i)
      {
        SDL_Log("  Ekran = %d ; liczba trybów %d", i, this->number_of_display_modes[i]);
        for(unsigned int j = 0 ; j<this->number_of_display_modes[i]  ;++j)
        {
          get_display_mode(i,j);
          SDL_Log("    %i x %i  %i bits per pixel", display_mode.w, display_mode.h, SDL_BITSPERPIXEL(display_mode.format));
        }

      }
      this->finish();
    }
    //niszczy to co stworzył
    private: void finish()
    {
      delete [] number_of_display_modes;
      SDL_Quit();
    }
};

#ifdef MAIN_SETTINGS
int main(int argc, char* argv[]){
  screen wyswietlacz;
  wyswietlacz.log();
  class_save_file sfile;
//  class_attribute *att;
//  att->dump();
//  att->get_this();
//  sfile.read2(att);
//  att->dump();
  return 0;
}
#endif
