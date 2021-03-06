/*
This file is part of the simulator for the LKV373
(c) 2019-2020 by kitten_nb_five
freenode #lkv373a

licence: AGPL v3 or later

THIS PROGRAM COMES WITHOUT ANY WARRANTY!
*/

#ifndef __MAC_H__
#define __MAC_H__
#include <stdbool.h>

#include "peripherals.h"

void mac_write(PERIPH_CB_WRITE_ARGUMENTS);
bool mac_read(PERIPH_CB_READ_ARGUMENTS);

#endif
