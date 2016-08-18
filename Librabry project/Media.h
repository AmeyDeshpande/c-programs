#ifndef MEDIA_H
#define MEDIA_H

#include<string>

using std::string;
class Media
{
   public:
       bool compare_by_call_number(const string&) const;
       bool compare_by_title(const string&) const;
       bool compare_by_subject(const string&) const;
       virtual bool compare_by_other(const string&) const;
       virtual void display();
       virtual ~Media();
   protected:
       bool sbycn;
       bool sbyti;
       bool sbysub;
       bool sbyother;
       string call_num;
       string title;
       string sub;
       string notes;      
};


#endif
