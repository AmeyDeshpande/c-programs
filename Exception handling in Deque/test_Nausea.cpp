#include<iostream>
#include<stdexcept>
#include "Nausea.h"
#include "orig_stack.cpp"

int main()
{
  Stack<Nausea> stackA;
  Stack<Nausea> stackB;
  Nausea n;
  /*stackA.push(n);
  stackA.push(n);*/
  Nausea::type=Nausea::copy_ctor;
  Nausea::trigger=2;

  
  
  //stackB.push(n);
  //stackB.push(n);
  //n=stackA.pop();
  


  

  try {
  //stackA.size();
  //stackA.pop();
  //stackB=stackA;
  stackA.push(n);
  stackA.push(n);
  stackA.push(n);
  stackA.push(n);
  //stackA.push(n);
  //stackA.push(n);
  //stackA.pop();
  //stackA.pop();
  //stackB=stackA;
  cout<<"in try"<<stackA.size()<<endl;
  }

  catch(std::exception& e){
    cout<<stackA.size()<<endl;
    std::cout << e.what() << std::endl;
    cout<<stackA.size()<<endl;
  }
  
  return 0;
}
