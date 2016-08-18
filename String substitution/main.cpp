#include"StreamSource.h"
#include<string>
using namespace std;
int main(int argc, char* argv[])
{
  string oldstr=argv[1];
  string newstr=argv[2];
  string filename=argv[3];
  StreamSource ss(oldstr,newstr,filename);
  int match_count=0; 
  char ch;
  while(!ss.get(ch).eof())
  {
    if(!ss.currently_replacing() && ch==oldstr[match_count])
    {
      ++match_count;
      if(match_count < oldstr.size())
        continue;
    }
    if(match_count == oldstr.size())
      ss.matched_search_string();
    else if(match_count > 0)
      ss.found_partial_match(match_count, ch);
    else
      ss.put(ch);
    match_count=0;
  }
  return 0;
}