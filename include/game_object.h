// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_GAME_OBJECT_H
#define _HIRO_GAME_OBJECT_H

#include "hiro.h"

mrb_bool hiro_is_game_object(mrb_state*, mrb_value);

void hiro_game_object_update(mrb_state*, mrb_value, mrb_int, mrb_value*);
void hiro_game_object_draw(mrb_state*, mrb_value, mrb_int, mrb_value*);

mrb_value hiro_game_object_mrb_add(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_use(mrb_state*, mrb_value);

void hiro_game_object_init(mrb_state*);

#endif
