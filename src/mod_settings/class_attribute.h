/******************************
 *attribute.h
 * ****************************/
#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H
//#include <stdio.h>
/* include debug code*/
#include "../mod_debug/debug.h"

using namespace std;
class class_attribute{
  private:
  string name;
  string value;
  class_attribute *next;
  class_attribute *prev;
  int protect();
  public:
  class_attribute();
  class_attribute(string name, string value);
  class_attribute *get_next();
  class_attribute *get_prev();
  void set_next(class_attribute *);
  void set_prev(class_attribute *);
  void set_name(string);
  void set_value(string);
  string get_name();
  string get_value();
  class_attribute *get_this();
  class_attribute *first();
  void dump();
  void dumpAll();
  class_attribute * last();
  class_attribute * insert_end(string,string);
  int size();
  int get_element(class_attribute**,unsigned int);
};
#endif

