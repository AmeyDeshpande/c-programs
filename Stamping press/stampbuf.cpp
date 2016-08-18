#include<iostream>
#include<ostream>
#include"stampbuf.h"
#include"stamp.h"
#include<ctype.h>
#include <cctype>
using namespace std;

stampbuf::stampbuf(int c, int r): max_col(c), max_row(r),row(0),col(0),stamp_buf(new char[(max_col/2)])
{
  setp(stamp_buf,stamp_buf+ max_col/2);
  stamping_press::insert_plate(c,r);
}
stampbuf::~stampbuf()
{
  sync();
  stamping_press :: eject_plate();

}

int stampbuf::sync()
{
  int size= pptr()-pbase();;
  for(int i=0;i<size;i++)
  {
    char temp=stamp_buf[i];
    if(isalnum(temp) || temp=='*' || temp=='#')
    {
      
      if(temp!=stamping_press::get_die())
        stamping_press::set_die(temp);

      if(col<max_col && row<max_row)
      {
        stamping_press::stamp(col,row);
        col++;
      }
    }
    else if(temp==' ')
    {
      
      if(col<max_col && row<max_row)
      {
        col++;
      }
    }
    else
    {
      if(col<max_col && row<max_row)
      {
        col++;
      }
    }
  }
}
int stampbuf::overflow(int c)
{
  sync();
  char temp=c;
  if(temp==' ')
    col++;
  else
  {
    if(temp!=stamping_press::get_die())
      stamping_press::set_die(temp);
    if(col<max_col && row<max_row)
    {
      stamping_press::stamp(col,row);
      col++;
    }
  } 
  setp(stamp_buf,stamp_buf+ max_col/2);
}
void stampbuf::set_row(int row1)
{
  sync();
  setp(stamp_buf,stamp_buf+ (max_col/2));
  row=row1;
  col = 0;
}
void stampbuf::endrow()
{
  sync();
  setp(stamp_buf,stamp_buf+ (max_col/2));
  row++;
  col=0;
}

