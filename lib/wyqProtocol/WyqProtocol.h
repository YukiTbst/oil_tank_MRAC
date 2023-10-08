#ifndef WYQPROTOCOL
#define WYQPROTOCOL
#include "Arduino.h"
bool command_check(String cmd_rec);
String check_bytes_cal(String cmd_str);
void check_bytes_append(String &cmd_str);
#endif