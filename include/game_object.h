// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_GAME_OBJECT_H
#define _HIRO_GAME_OBJECT_H

#include "hiro.h"

void hiro_game_object_update(mrb_state*, mrb_value, mrb_int, mrb_value*);
void hiro_game_object_draw(mrb_state*, mrb_value, mrb_int, mrb_value*);

void hiro_game_object_init(mrb_state*);

#endif
