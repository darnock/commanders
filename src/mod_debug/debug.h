/*****************************
 *file: debug.h
 *****************************/
#ifndef _DEBUG_H
#define _DEBUG_H

/* if commented turn on assert code*/
/*#define NDEBUG*/


/* use only one define for one main() */


/* for main() in class_save_file.cpp */
/*#define DEBUG_FILE_OPERATIONS*/

/* include assert */
#include <assert.h>
#include <iostream>

/******************************
 * function print message and then is calling a assert macro from assert.h
 * which causes interrupts of program.
 *
 * First argument of function is an expression to be evaluated.
 * If this expression evaluates to 0,
 * this causes an assertion failure that terminates the program.
 *
 * Second argument is a message to print before call of assert macro.
 * ***************************/
extern void assert_msg(int,std::string);

#endif
/* _DEBUG_H */
