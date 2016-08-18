#include "Nausea.h"
#include<iostream>
#include<stdexcept>

Nausea::throw_where Nausea::type=Nausea::nowhere;
unsigned int Nausea::trigger=0;

Nausea::Nausea(const Nausea& n)
{
  std::cerr << "c";
  if(type==copy_ctor && --trigger==0)
    throw std::runtime_error("Copy ctor thrown");
}

Nausea::Nausea()
{
  std::cerr << "d";
  if(type==default_ctor && --trigger==0)
    throw std::runtime_error("Default ctor thrown");
}

Nausea& Nausea::operator=(const Nausea&)
{
  std::cerr << "a";
  if(type==assignment_op && --trigger==0)
    throw std::runtime_error("Assignment operator thrown");
  return *this;
}
