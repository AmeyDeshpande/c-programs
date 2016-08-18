#ifndef PERIODIC_H
#define PERIODIC_H
#include"Media.h"
#include<string>
class Periodic : public Media
{
   public:
      Periodic(string,string,string,string,string,string,string,string,string,string,string,string);
      void display();
      bool compare_by_other(const string&) const;
   private:
      string author;
      string desc;
      string publishser;
      string publishing_history;
      string series;
      string related_titles;
      string other_forms_of_title;
      string govt_doc_number;
} ;
#endif
