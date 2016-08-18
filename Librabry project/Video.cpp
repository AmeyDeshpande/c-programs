#include"Video.h"
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
using std::string;

Video::Video(string num,string title,string sub,string desc,string distributor,string notes,string series,string label)
{
   this->call_num=num;
   this->title=title;
   this->sub=sub;
   this->desc=desc; 
   this->distributor=distributor;
   this->notes=notes;
   this->series=series;
   this->label=label;
}

void Video::display()
{
   cout<<"================================================\n";
   cout<<"Data found in video:-\n"<<endl;
   cout<<"------------------------------------------------"<<endl;
   Media::display();
   cout<<setw(15)<<"Description: "<<this->desc<<endl;
   cout<<setw(15)<<"Distributor: "<<this->distributor<<endl;
   cout<<setw(15)<<"Series:"<<this->series<<endl;
   cout<<setw(15)<<"Label: "<<this->label<<endl;
}
bool Video::compare_by_other(const string& comp) const
{
   if((Media::compare_by_other(comp)))
      return true;
   else if (!(this->desc.find(comp) == string::npos))
      return true;
   else if (!(this->distributor.find(comp) == string::npos))
      return true;
   else 
      return false;
}
