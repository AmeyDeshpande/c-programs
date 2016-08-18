#include"Book.h"
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
using std::string;

Book::Book(string num,string title,string sub,string author,string desc,string publisher,string city,string year,string series,string notes)
{
   this->call_num=num;
   this->title=title;
   this->sub=sub;
   this->author=author;
   this->desc=desc;
   this->publishser=publisher;
   this->city=city;
   this->year=year;
   this->series=series;   
   this->notes=notes; 
}
void Book::display()
{   
   cout<<"================================================"<<endl;
   cout<<"Data found in books:-\n"<<endl;
   cout<<"------------------------------------------------"<<endl;
   Media::display();
   cout<<setw(15)<<"Author: "<<this->author<<endl;
   cout<<setw(15)<<"Description: "<<this->desc<<endl;
   cout<<setw(15)<<"Publisher: "<<this->publishser<<endl;
   cout<<setw(15)<<"City: "<<this->city<<endl;
   cout<<setw(15)<<"Year: "<<this->year<<endl;
   cout<<setw(15)<<"Series: "<<this->series<<endl;
}
bool Book::compare_by_other(const string& comp) const
{
   if(Media::compare_by_other(comp))
      return true;
   else if (!(this->desc.find(comp) == string::npos))
      return true;
   else if (!(this->year.find(comp) == string::npos))
      return true;
   else 
      return false;
}
