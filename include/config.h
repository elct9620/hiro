#ifndef _HIRO_CONFIG_H
#define _HIRO_CONFIG_H

#include "hiro.h"

mrb_bool hiro_config_is_setter(const char*);
void hiro_config_set(mrb_state* mrb, mrb_value, mrb_sym, mrb_value);

mrb_value hiro_config_mrb_register(mrb_state*, mrb_value);
mrb_value hiro_config_mrb_method_missing(mrb_state*, mrb_value);

void hiro_define_config(mrb_state*);

#endif
