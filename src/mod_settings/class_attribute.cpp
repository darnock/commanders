// Using SDL2's SDL_GetCurrentDisplayMode()
#include <SDL2/SDL.h>
#include <stdio.h>
#include "settings.h"
#include <iostream>
#include <fstream>
#include "class_attribute.h"
#include "../mod_debug/debug.h"

using namespace std;

  int class_attribute::protect(){
    if(this!=NULL){
      return 1;
    }
    return -1;
  }
class_attribute::class_attribute(){
    next=NULL;
    prev=NULL;
    this->name="";
    this->value="";
  }
class_attribute::class_attribute(string name, string value){
    next=NULL;
    prev=NULL;
    this->name=name;
    this->value=value;
  }
  class_attribute * class_attribute::get_next(){return next;}
  class_attribute * class_attribute::get_prev(){return prev;}
  void class_attribute::set_next(class_attribute *att){next=att;}
  void class_attribute::set_prev(class_attribute *att){prev=att;}
  void class_attribute::set_name(string n){name = n;}
  void class_attribute::set_value(string v){value = v;}
  string class_attribute::get_name(){return name;}
  string class_attribute::get_value(){return value;}
/******************************
 *function return pointer to first element of list
*******************************/
  class_attribute * class_attribute::first(){
    class_attribute *tmp=this;
    while(tmp->prev!=0){
      tmp=tmp->prev;
    }
    return tmp;
  }
void class_attribute::dump(){
#ifndef NDEBUG
  assert_msg(this!=NULL,"NULL pointer detection");
#endif
  cout<<"name = "<< name <<"\n  value ="<< value<<"\n  next = "<<next<<"\n  acc  = "<<this <<"\n  prev = "<<prev<<endl;
}
void class_attribute::dumpAll(){
#ifndef NDEBUG
  assert_msg(this!=NULL,"NULL pointer detection");
#endif
  if(this->protect()==1){
   class_attribute *attTmp=this->first();
    do{
      attTmp->dump();
      attTmp=attTmp->next;
    }while(attTmp!=NULL);
  }
}
/******************************
 *function return pointer to last element of list
 ******************************/
  class_attribute * class_attribute::last(){
   class_attribute *tmp=this;
    while(tmp->next!=0){
      tmp=tmp->next;
    }
    return tmp;

  }
/******************************
 *function create new list element and set attributes
 * name and value
 * return pointer to created element
 ******************************/
class_attribute * class_attribute::insert_end(string name, string value){
#ifndef NDEBUG
  assert_msg(this!=NULL,"NULL pointer detection");
#endif
  class_attribute *tmp = this->last();
  class_attribute *tmp_new = new class_attribute(name,value);
  tmp->next = tmp_new;
  tmp_new->prev=tmp;
  return tmp_new;
}
/******************************
 *return numbers of list elements 
 *if return 0, list is empty
 ******************************/
int class_attribute::size(){
  if(this->protect()==1){
    int count=0;
    if(this->get_value() == "" && this->get_name() == ""){
      return 0;
    }else if(this->get_next()==NULL && this->get_prev()==NULL){
      return 1;
    }else{
     class_attribute * tmp = this->first();
      while(tmp!=NULL){
        tmp=tmp->next;
        count++;
      }
      return count;
    }
/*in this case, debug me pleas */
    return -1;
  }else{
    return 0;
  }
}
/******************************
 * return pointer to n element of list
 * return -1 in case - existing element 
 * return -2 in case - when trying to get element out of boundary  
 * return -3 in default case 
 ******************************/
  int class_attribute::get_element(class_attribute ** att ,unsigned int n){
    class_attribute *tmp = NULL;
    unsigned int counter = 1;
    if( *att != NULL){
      return -1;
    }else if( (n > (unsigned int) this->size()) || (n<=0) ){
      return -2;
    }else{
      tmp = this->first();
      for(; counter < n ; counter++){
        tmp=tmp->get_next();
      }
      *att = tmp;
      cout<<"att = "<<att<<endl;
      return counter;
    }
    return -3;
  }

class_attribute *class_attribute::get_this(){
  class_attribute *tmp=NULL;
  cout<<this<<endl;
  cout<<this->name.empty()<<endl;
  return tmp;
}

