#ifndef FILM_H
#define FILM_H
#include"Media.h"
#include<string>
class Film : public Media
{
   public:
      
      Film(string,string,string,string,string,string);
      void display();
      bool compare_by_other(const string&) const;
   private:
      string director;
      string year;

} ;
#endif
