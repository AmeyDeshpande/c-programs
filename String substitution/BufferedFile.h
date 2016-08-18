#include"TrackingDeque.h"
#include<fstream>
#include<string>
using namespace std;
class BufferedFile : public fstream
{
  public:
    BufferedFile(string );
    BufferedFile& get(char& ch);
    void put(char ch);
    bool eof();
    char rawget();
    void do_over(char& ch);
    ~BufferedFile();
  private:
    TrackingDeque<char> deq;
    const string filename;
    int getter;
    int putter;
    int count;
    char temp;
    bool eofile;
};