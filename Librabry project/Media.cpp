#include"Media.h"
#include<iostream>
#include<iomanip>
using namespace std;

bool Media::compare_by_call_number(const string& comp) const
{
   if (this->call_num.find(comp) == string::npos)
      return false;
   else 
      return true;
}
bool Media::compare_by_title(const string& comp) const
{
   if (this->title.find(comp) == string::npos)
      return false;
   else 
      return true;
}
bool Media::compare_by_subject(const string& comp) const
{
   if (this->sub.find(comp) == string::npos)
      return false;
   else 
      return true;
}
bool Media::compare_by_other(const string& comp) const
{
   if (!(this->notes.find(comp) == string::npos))
      return true;
   else 
      return false;
}
void Media::display()
{
   cout<<left<<setw(15)<<"Call number: "<<this->call_num<<endl;
   cout<<setw(15)<<"Title: "<<this->title<<endl;
   cout<<setw(15)<<"Subject: "<<this->sub<<endl;
   cout<<setw(15)<<"Notes: "<<this->notes<<endl;
}
Media::~Media()
{
}
