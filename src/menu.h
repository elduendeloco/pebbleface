
#ifndef sail_menu_h
#define sail_menu_h
#include <pebble.h>
void set_menu_value (int value);
int get_menu_value ();
void set_rows_value (int value);
int get_rows_value ();

void menu_creator();
void menu_destroier();
#endif
