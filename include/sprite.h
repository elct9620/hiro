#ifndef _HIRO_SPRITE_H
#define _HIRO_SPRITE_H

#include "hiro.h"

mrb_value hiro_sprite_mrb_initialize(mrb_state*, mrb_value);

void hiro_define_sprite(mrb_state*);

#endif
