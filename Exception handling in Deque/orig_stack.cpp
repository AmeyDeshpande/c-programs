#include<iostream>
using namespace std;
template <typename T>
class Stack
{
  public:
    Stack();
    Stack(const Stack&);
    ~Stack();
    Stack& operator=(const Stack<T>&);
    int size();
    void push(T);
    T pop();
  private:
    static const int chunk_size;
    unsigned maximum_size;
    int current_size;
    T* base;
};
template <class T>
const int Stack<T>::chunk_size=10;

template <typename T>
Stack<T>::Stack()
:current_size(-1),maximum_size(chunk_size),base(new T[chunk_size])
{
  if(base==0)
    throw;
}
template <typename T>
Stack<T>::Stack(const Stack& s)
:maximum_size(s.maximum_size), base(new T[s.maximum_size])
{
  if(s.current_size>-1)
  {
    try {
    for(current_size=0; current_size<=s.current_size; current_size++)
      base[current_size]=s.base[current_size];
    }catch(...)
    {
      delete [] base;
      throw;
    }
    current_size--;
  }
}

template <typename T>
Stack<T>::~Stack()
{
  delete [] base;
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
  T* temp=base;
  int tmp=maximum_size;
  int temp_curr=current_size;
  maximum_size=s.maximum_size;
  try{
    base=new T[maximum_size];
    
  }
  catch(...)
  {  
    delete [] base;  
    base=temp;
    maximum_size=tmp;
    throw;
  }
  current_size=s.current_size;
  if(current_size>-1)
  {
    try
    {
      for(int x=0; x<=current_size; x++)
        base[x]=s.base[x];
      delete [] temp;
    }
    catch(...)
    {
      delete [] base;
      current_size=temp_curr;
      maximum_size=tmp;
      base=temp;
      throw;
    }
    
  }
  else
    delete [] temp;
  return *this;
}
template <typename T>
void Stack<T>::push(T element)
{
  current_size++;
  int temp_max=maximum_size;
  T* temp=base;
  if(current_size==maximum_size-1)
  {
    try
    {
      maximum_size+=chunk_size;
      T* new_buffer = new T[maximum_size];
      for(int x=0; x<current_size; x++)
        new_buffer[x]=base[x];	
      delete [] base;
      base=new_buffer;
      //base[current_size]=element;
    }
    catch(...)
    {
      delete [] base;
      maximum_size=temp_max;
      base=temp;
      current_size--;
      throw;
    }
  }
  base[current_size]=element;
}
template <typename T>
T Stack<T>::pop()
{
  try
  {
    return base[current_size--];
  }
  catch(...)
  {
    current_size++;
    throw;
  }
}
template<typename T>
int Stack<T>::size()
{
  return current_size+1;
}
