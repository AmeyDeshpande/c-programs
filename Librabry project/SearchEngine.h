#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#include"Media.h"
#include"Book.h"
#include"Video.h"
#include"Periodic.h"
#include"Film.h"
#include<vector>
using std::vector;
class search_engine
{
   public:
      search_engine();
      void search_by_call_number(const string&);
      void search_by_title(const string&);
      void search_by_subject(const string&);
      void search_by_other(const string&);
      ~search_engine();
      void display();
   private:
     vector<Media*> srch;
     vector<Media*> result;
};
#endif
