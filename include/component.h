// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_COMPONENT_H
#define _HIRO_COMPONENT_H

#include "hiro.h"

mrb_bool hiro_is_component(mrb_state*, mrb_value);

void hiro_component_update(mrb_state*, mrb_value, mrb_int, mrb_value*);
void hiro_component_draw(mrb_state*, mrb_value, mrb_int, mrb_value*);

void hiro_component_init(mrb_state*);

#endif
