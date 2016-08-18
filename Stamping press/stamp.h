#ifndef STAMP_H
#define STAMP_H
namespace stamping_press {
 void set_die(char die);
 char get_die();
 void insert_plate(int cols, int rows);
 void eject_plate();
 void stamp(int col, int row);
};
#endif
