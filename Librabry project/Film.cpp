#include"Film.h"
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
using std::string;

Film::Film(string num,string title,string sub,string dir,string notes,string year)
{
   this->call_num=num;
   this->title=title;
   this->sub=sub;
   this->director=dir; 
   this->notes=notes;
   this->year=year;
}

void Film::display()
{
   cout<<"================================================\n";
   cout<<"Data found in Film:-\n"<<endl;
   cout<<"------------------------------------------------"<<endl;
   Media::display();
   cout<<setw(15)<<"Director: "<<this->director<<endl;
   cout<<setw(15)<<"Year: "<<this->year<<endl;

}
bool Film::compare_by_other(const string& comp) const
{
   if(Media::compare_by_other(comp))
      return true;
    if (!(this->director.find(comp) == string::npos))
      return true;
   else if (!(this->year.find(comp) == string::npos))
      return true;
   else 
      return false;
}
