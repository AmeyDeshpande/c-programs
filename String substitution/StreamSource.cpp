#include"StreamSource.h"
#include<string>
#include<iostream>
using namespace std;
StreamSource :: StreamSource(string srch,string replacementstr, string filenm):searchstr(srch),replacement(replacementstr),filename(filenm),replacement_count(0),search_origin(0),search_count(0),string_length(0),replacement_get(false),search_get(false),buf(filenm){}
bool StreamSource::eof()
{
  if(search_count>0 || replacement_count>0)
    return false;
  else
    return buf.eof();
}
StreamSource& StreamSource::get(char& ch)
{
  if(search_count > 0)
  {
    ch = searchstr[string_length-search_count--];
    search_get = true;
  }
  else if (replacement_count > 0)
  {
    ch = replacement[string_length-replacement_count--];
    replacement_get = true;
  }
  else
  {
    search_get=false;
    replacement_get = false;
    buf.get(ch);
  }
  return *this;
}
void StreamSource::put(char ch)
{
  buf.put(ch);
}
bool StreamSource::currently_replacing()
{
  return replacement_get;
}
void StreamSource::matched_search_string()
{
  string_length=replacement.size();
  replacement_count=replacement.size();
}
void StreamSource::found_partial_match(int match_count,char& ch)
{
  if(search_get)
    ++search_origin;
  else
  {  
    search_origin=0;
    string_length=match_count;
    buf.do_over(ch);    
  }
  put(searchstr[search_origin]);
  search_count=string_length-1-search_origin;
}
StreamSource::~StreamSource(){}