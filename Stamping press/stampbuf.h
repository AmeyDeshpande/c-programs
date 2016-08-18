#ifndef STAMPBUF_H
#define STAMPBUF_H
class stampbuf : public std::streambuf
{
public:
  stampbuf(int,int);
~stampbuf();
  void set_row(int);
  virtual int overflow(int);
  virtual int sync();
  void endrow();
private:
  int row;
  int col;
  int max_row;
  int max_col;
  char* stamp_buf;
};
#endif
