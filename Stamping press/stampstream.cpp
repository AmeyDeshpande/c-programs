#include"stampstream.h"
#include<iostream>
#include<ostream>

using namespace std;

stampstream::stampstream(int c, int r) : ostream(new stampbuf(c,r))
{
}
stampstream:: ~stampstream()
{
  delete rdbuf();
}
ostream& operator<<(ostream& os, const row& row1)
{
  stampbuf* sbp=static_cast<stampbuf*>(os.rdbuf());
  sbp->set_row( row1.gotorow() );
return os;
}
ostream& endrow(ostream& os)
{
  stampbuf* sbp=static_cast<stampbuf*>(os.rdbuf());
  sbp->endrow();
	return os;
}

row::row(int r) : go_row(r)
{
}
int row::gotorow() const
{
  return go_row;
}
