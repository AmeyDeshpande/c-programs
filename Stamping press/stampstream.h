#ifndef STAMPSTREAM_H
#define STAMPSTREAM_H
#include<ostream>
#include"stampbuf.h"

using namespace std;
class stampstream : public ostream {
public:
  
  void end_row();
  void setrow();
  stampstream(int,int);
	~stampstream();
};
class row
{
 public:
   row(int);
   int gotorow() const;
 private:
   int go_row;
};
ostream& endrow(ostream&);
ostream& operator<<(ostream& ,const row&);
#endif

