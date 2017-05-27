// Using SDL2's SDL_GetCurrentDisplayMode()
#include <SDL2/SDL.h>
#include <stdio.h>
#include "settings.h"
#include <iostream>
#include <fstream>
#include "class_attribute.h"
#include "class_save_file.h"
using namespace std;

class_save_file::class_save_file(){
  iofile.open("settings.txt", ios::in | ios::out);
  /* error - file not existing */
  assert_msg(iofile.is_open(),"file not opened");
}

class_save_file::~class_save_file(){
  iofile.close();
}
int class_save_file::replace(string old_name,string new_string){
  ofstream outfile("settings.txt.new");
  char tmp[255];
  string string_tmp;
  while(iofile.eof()!=true){
    iofile.getline(tmp,255);
    string_tmp=tmp;
    if(string_tmp.find("=",0)!=string::npos){
      if(string_tmp.find(old_name,0)!=string::npos){
        cout<<new_string<<endl;
        outfile<<new_string<<endl;
      }else{
        cout<<string_tmp<<endl;
        outfile<<string_tmp<<endl;
      }
    }
  }
  outfile<<ios_base::eofbit;
  iofile.close();
  outfile.close();
  remove("settings.txt");
  rename("settings.txt.new","settings.txt");
  iofile.open("settings.txt");
  outfile.close();
  return 0;
}
int class_save_file::save(string ** values){
  //TODO
  return 0;
}

void class_save_file::cut_name_value(string *txt,char delimiter){
  int pos=txt[0].find(delimiter,0);
  int length=txt[0].length();
  txt[1]=txt[0].substr(pos+1,length-pos-1);
  txt[0]=txt[0].substr(0,pos);
}

void class_save_file::read(class_attribute **att){
//#ifndef NDEBUG
//  assert_msg(*att==NULL," *att must be a NULL pointer");
//#endif
  char tmp[255];
  string line[2];
  while(iofile.eof()!=true){
    iofile.getline(tmp,255);
    line[0]=tmp;
    if(line[0].find("=",0)!=string::npos){
      this->cut_name_value(&line[0],'=');
      if((*att)==NULL){
        *att = new class_attribute(line[0],line[1]);
      }else{
        (**att).insert_end(line[0],line[1]);
      }
    }
  }
}

void class_save_file::read2(class_attribute *att){
//#ifndef NDEBUG
//  assert_msg(*att==NULL," *att must be a NULL pointer");
//#endif
  char tmp[255];
  string line[2];
  while(iofile.eof()!=true){
    iofile.getline(tmp,255);
    line[0]=tmp;
    if(line[0].find("=",0)!=string::npos){
      this->cut_name_value(&line[0],'=');
      if((att)==NULL){
        att = new class_attribute(line[0],line[1]);
      }else{
        (*att).insert_end(line[0],line[1]);
      }
    }
  }
}


#ifdef DEBUG_FILE_OPERATIONS
int main(int argc, char* argv[]){
  class_save_file sf;
  class_attribute * att=NULL;
//  string str[2]={"variable=123",""};
  sf.read(&att);
cout<<"****************\n";
  att->dumpAll();
  return 0;
}
#endif
