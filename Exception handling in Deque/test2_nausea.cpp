#include<iostream>
#include<stdexcept>
#include "Nausea.h"

void some_function(Nausea n)
{
  return;
}

int main()
{

  Nausea::type=Nausea::copy_ctor;
  Nausea::trigger=3;

  Nausea myobject;
  try {
    for(int i=0; i<5; ++i)
      some_function(myobject);
  }
  catch(std::exception& e){
    std::cout << e.what() << std::endl;
  }
  return 0;
}
