#include <deque>
#include <iostream>
using namespace std;

template <typename T>
class TrackingDeque: public deque<T>
{
public:
  TrackingDeque();
  ~TrackingDeque();
  void push_back(T);
  void push_front(T);
private:
  int max_size;
};

template <typename T>
TrackingDeque<T>::TrackingDeque() : max_size(0)
{
}
template <typename T>
void TrackingDeque<T>::push_back(T q)
{
  deque<T>::push_back(q);
  if(this->size()>max_size)
    max_size++;  
}
template <typename T>
void TrackingDeque<T>::push_front(T q)
{
  deque<T>::push_front(q);
  if(this->size() > max_size)
    max_size++;
}
template <typename T>
TrackingDeque<T>::~TrackingDeque()
{
  cout<<"-->"<<max_size<<"<--"<<endl;
}
