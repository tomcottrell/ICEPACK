#ifndef AC_H
#define AC_H

#include <stdint.h>
#include <stdbool.h>

extern bool LOW;
extern bool MED;
extern bool HIGH;
extern bool COMP;

extern float Resistance_Setpoint;

void AC_app(void);

#endif




