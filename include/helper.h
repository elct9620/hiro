#ifndef _HIRO_HELPER_H
#define _HIRO_HELPER_H

#include "hiro.h"

mrb_value hiro_helper_get_hash_attribute(mrb_state*, mrb_value, mrb_sym);
mrb_value hiro_helper_get_array_attribute(mrb_state*, mrb_value, mrb_sym);

void hiro_helper_each_array_element_do(mrb_state*, mrb_value, mrb_sym, const char*, mrb_int, mrb_value*);

#endif
