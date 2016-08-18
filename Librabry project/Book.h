#ifndef BOOK_H
#define BOOK_H
#include"Media.h"
#include<string>
class Book : public Media
{
   public:
      Book(string,string,string,string,string,string,string,string,string,string);
      void display();
      bool compare_by_other(const string&) const;
   private:
      string author;
      string desc;
      string publishser;
      string city;
      string year;
      string series;
} ;
#endif
