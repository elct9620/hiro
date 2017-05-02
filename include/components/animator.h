// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_ANIMATOR_H
#define _HIRO_ANIMATOR_H

#include "hiro.h"

mrb_value hiro_animator_mrb_sprite_size(mrb_state*, mrb_value);

void hiro_animator_init(mrb_state* mrb, struct RClass*);

#endif
