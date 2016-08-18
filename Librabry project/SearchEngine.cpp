#include<iostream>
#include<fstream>
#include"SearchEngine.h"

using namespace std;

using std::string;
using std::fstream;

search_engine::search_engine()
{   
   ifstream myfile("book.txt");
   std::string in[10];
   while(!getline(myfile,in[0],'|').eof())
   {
      for(int i=1;i<9;i++)
         getline(myfile,in[i],'|');
      getline(myfile,in[9]);
      Book* temp = new Book(in[0],in[1],in[2],in[3],in[4],in[5],in[6],in[7],in[8],in[9]);
      srch.push_back(temp);
   }
   myfile.close();
   myfile.open("video.txt");
   string vid[8];
   while(!getline(myfile,vid[0],'|').eof())
   {
      for(int i=1;i<7;i++)
         getline(myfile,vid[i],'|');
      getline(myfile,vid[7]);
      Video* temp = new Video(vid[0],vid[1],vid[2],vid[3],vid[4],vid[5],vid[6],vid[7]);
      srch.push_back(temp);
   }
   myfile.close();
   myfile.open("periodic.txt");
   string per[12];
   while(!getline(myfile,per[0],'|').eof())
   {
      for(int i=1;i<11;i++)
         getline(myfile,per[i],'|');
      getline(myfile,per[11]);
      Periodic* temp = new Periodic(per[0],per[1],per[2],per[3],per[4],per[5],per[6],per[7],per[8],per[9],per[10],per[11]);
      srch.push_back(temp);
   }
   myfile.close();
   myfile.open("film.txt");
   string fil[6];
   while(!getline(myfile,fil[0],'|').eof())
   {
       for(int i=1;i<=4;i++)
          getline(myfile,fil[i],'|');
       getline(myfile,fil[5]);
       Film* temp=new Film(fil[0],fil[1],fil[2],fil[3],fil[4],fil[5]);
       srch.push_back(temp);
	
   }
   myfile.close();
}

void search_engine::search_by_subject(const string& comp) 
{
   result.clear();
   for (std::vector<Media*>::iterator it = srch.begin() ; it != srch.end(); ++it)
   {
      if((*it)->compare_by_subject(comp))
      {
         result.push_back(*it);
      }
   }           
}
void search_engine::search_by_other(const string& comp) 
{
   result.clear();
     for (std::vector<Media*>::iterator it = srch.begin() ; it != srch.end(); ++it)
     {
      if((*it)->compare_by_other(comp))
      {
         result.push_back(*it);
      }
   }
}
void search_engine::search_by_call_number(const string& comp)  
{
   result.clear();
   
   for (std::vector<Media*>::iterator it = srch.begin() ; it != srch.end(); ++it)
   {
      if((*it)->compare_by_call_number(comp))
      {
         result.push_back(*it);
      }
   }
}  
void search_engine::search_by_title(const string& comp) 
{
   result.clear();
   for (std::vector<Media*>::iterator it = srch.begin() ; it != srch.end(); ++it)
   {
      if((*it)->compare_by_title(comp))
      {
         result.push_back(*it);
      }
   }
}
void search_engine::display()
{
   for (std::vector<Media*>::iterator it = result.begin() ; it != result.end(); ++it)
   {
      (*it)->display();      
   }
   cout<<"------------------------------------------------"<<endl;
   cout<<"Number of records found: "<<result.size()<<endl;
   cout<<"------------------------------------------------"<<endl;
}
search_engine::~search_engine()
{
   for (int i=0;i<srch.size();i++)
   {
       delete srch.at(i);
   }
   for(int i=0;i<result.size();i++)
   {
       delete result.at(i);
   }
}
