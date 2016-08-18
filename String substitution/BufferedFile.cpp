#include"BufferedFile.h"
#include<string>
#include<iostream>
#include<unistd.h>
using namespace std;

BufferedFile::BufferedFile(string fname):filename(fname),getter(0),putter(0),count(0),eofile(false)
{
  fstream::open(filename.c_str(), std::ios::out | std::ios::in);
}
bool BufferedFile::eof()
{
  if(!deq.empty())
    return false;
  else
    return eofile;
}
BufferedFile& BufferedFile::get(char& ch)
{
  if(!deq.empty())
  {
    ch=deq.front();
    deq.pop_front();
  }
  else
  {
    ch=rawget();
    if(fstream::eof())
    {
      fstream::clear();
      eofile=true;
    }
  }
  return *this;
}
void BufferedFile::put(char ch)
{
  if(getter==putter && !eofile)
  {
    temp=rawget();
    deq.push_back(temp);
  }
  fstream::seekp(putter);
  if(fstream::eof())
  {
    fstream::clear();
    eofile=true;
  }
  fstream::put(ch);
  putter++;
}
char BufferedFile::rawget()
{
  char tmp;
  seekg(getter);
  fstream::get(tmp);
  getter++;
  return tmp;
}
void BufferedFile::do_over(char& ch)
{
  deq.push_front(ch);
}
BufferedFile::~BufferedFile()
{
  truncate(filename.c_str(),putter);
  fstream::close();
}