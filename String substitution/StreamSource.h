#include<string>
#include"BufferedFile.h"
class StreamSource
{
  public:
    StreamSource(string, string, string);
    StreamSource& get(char& ch);
    void put(char ch);
    bool eof();
    bool currently_replacing();
    void matched_search_string();
    void found_partial_match(int,char&);
    ~StreamSource();
  private:
    BufferedFile buf;
    string replacement;
    const string filename;
    string searchstr;
    int replacement_count;
    int search_origin;
    int search_count;
    int string_length;
    bool search_get;
    bool replacement_get;
};