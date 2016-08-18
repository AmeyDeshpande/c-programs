#include "orig_stack.cpp"
#include "Nausea.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{

    /* Nausea::type=Nausea::default_ctor;
   Nausea::trigger=5;
   try{
   Nausea* n=new Nausea;}
catch(std::exception& e){
    std::cout << e.what() << std::endl;
  }*/
    Stack<string> st;
   //st.push(12.32);
   cout<<st.pop()<<endl;

   //Stack<Nausea> st;
   return 0;
}
