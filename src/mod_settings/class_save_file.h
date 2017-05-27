/******************************
 *attribute.h
 * ****************************/
#ifndef _CLASS_SAVE_FILE_H
#define _CLASS_SAVE_FILE_H
#include <fstream>
#include "class_attribute.h"
/* include debug code */
#include "../mod_debug/debug.h"
using namespace std;
class class_save_file{
  private:
    ifstream iofile;
/******************************
 * function that split string to 2 strings
 * input:
 * - 1 argument - pointer to 2 elements array, 
 *   - 1 array element e.g. "width=600"
 *   - 2 array element will be overwritten 
 * - 2 argument - input char e.g. '"'
 * output:
 * - 1 array element - name e.g. "width"
 *   2 array element - value e.g. "600"
 ******************************/
    void cut_name_value(string*,char);
  public:
/******************************
* replace 1 argument with 2 argument
* 1 argument format - only name e.g. "width"
* 2 argument format - name with value e.g. "width=600"
* ===========================
* - create new_file
* - read from old_file and write to new_file
* - if finds 1st argument, replace that line with 2st argument
* - delete old_file
* - rename new_file to name of old file
******************************/
    int replace(string,string);
/******************************
 * TODO 
 ******************************/
    int save(string**);
/******************************
 * read from file settings.txt, and store elements in list
 * 1st argument is list that store settings
 ******************************/
    void read(class_attribute **);
    void read2(class_attribute *);
/******************************
 * constructor
 * open files for reading operation
 ******************************/
    class_save_file();
/******************************
 * destructor
 * close open files
 ******************************/
    ~class_save_file();
};
#endif

