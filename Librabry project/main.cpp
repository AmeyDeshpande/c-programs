#include<iostream>
#include"SearchEngine.h"
#include"Media.h"
#include<cstdlib>

using namespace std;
int main()
{
    search_engine sr;
    string comp,gettype;int temp;
    bool con=true;
    cout<<"Type your search criteria:"<<endl;
    cout<<"1. Call number"<<endl;
    cout<<"2. Title"<<endl;
    cout<<"3. Subject"<<endl;
    cout<<"4. Other"<<endl;
    cout<<"5. Exit"<<endl;
    while(std::getline(cin,gettype))
    {       
       if(gettype=="call number")
       { 
          cout<<"\nEnter a string to compare"<<endl;
          cin>>comp;
          sr.search_by_call_number(comp);
          sr.display();
       }
       else if(gettype=="title") 
       {
          cout<<"\nEnter a string to compare"<<endl;
          cin>>comp;
          sr.search_by_title(comp);
          sr.display();
       }
       else if(gettype=="subject")
       {
          cout<<endl;
          cout<<"Enter a string to compare"<<endl;
          cin>>comp;
          sr.search_by_subject(comp);
          sr.display();
       }
       else if(gettype=="other") 
       {
          cout<<endl;
          cout<<"Enter a string to compare"<<endl;
          cin>>comp;
          sr.search_by_other(comp);
          sr.display();
       }
       else if(gettype=="exit")
       {
           exit(0);
       }
       else
       {
          cout<<"\nInvalid input\nPress Enter"<<endl;          
       }
       cin.ignore();
       cout<<"Type your search criteria:"<<endl;
    cout<<"1. Call number"<<endl;
    cout<<"2. Title"<<endl;
    cout<<"3. Subject"<<endl;
    cout<<"4. Other"<<endl;
    cout<<"5. Exit"<<endl;
    
   }
   return 0;
}
