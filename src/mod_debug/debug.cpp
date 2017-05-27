/*****************************
 *debug.c
 * ***************************/
#include "debug.h"

/* definition of function if debug is on */
#ifndef NDEBUG
void assert_msg(int condition, std::string msg){
  if(condition == 0 ){
    std::cout<<">>>"<<msg<<"<<<"<<std::endl;
    assert(condition);
  }
}

/* empty functions if debug code is off*/
#else 
void assert_msg(int condition, std::string msg){}
#endif
