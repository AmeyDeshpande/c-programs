#include"Periodic.h"
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
using std::string;

Periodic::Periodic(string num,string title,string sub,string author,string desc,string publisher,string pub_his,string series,string notes,string related_titles,string othr_frm_title,string govt_doc_no)
{
      this->call_num=num;
      this->title=title;
      this->sub=sub;
      this->author=author;
      this->desc=desc;
      this->publishser=publisher;
      this->publishing_history=pub_his;
      this->series=series;
      this->related_titles=related_titles;
      this->other_forms_of_title=othr_frm_title;
      this->govt_doc_number=govt_doc_no;
      this->notes=notes;
}
void Periodic::display()
{
   
   cout<<"================================================"<<endl;
   cout<<"Data found in Periodicals:-\n"<<endl;
   cout<<"------------------------------------------------"<<endl;
   Media::display();
   cout<<setw(15)<<"Author: "<<this->author<<endl;
   cout<<setw(15)<<"Description: "<<this->desc<<endl;
   cout<<setw(15)<<"Publisher: "<<this->publishser<<endl;
   cout<<setw(15)<<"Publishing history: "<<this->publishing_history<<endl;
   cout<<"Series: "<<setw(15)<<this->series<<endl;
   cout<<"Related titles: "<<setw(15)<<this->related_titles<<endl;
   cout<<"Other forms of titles: "<<setw(10)<<this->other_forms_of_title<<endl;
   cout<<"Government document number: "<<setw(10)<<this->govt_doc_number<<endl;
}
bool Periodic::compare_by_other(const string& comp) const
{
   if(Media::compare_by_other(comp))
      return true;
    if (!(this->desc.find(comp) == string::npos))
      return true;
   else if (!(this->series.find(comp) == string::npos))
      return true;
   else if (!(this->related_titles.find(comp) == string::npos))
      return true;
   else 
      return false;
}
