#ifndef VIDEO_H
#define VIDEO_H
#include"Media.h"
#include<string>
class Video : public Media
{
   public:
      Video(string,string,string,string,string,string,string,string);
      void display();
      bool compare_by_other(const string&) const;
   private:
      string desc;
      string distributor;
      string label;
      string series;
} ;
#endif
