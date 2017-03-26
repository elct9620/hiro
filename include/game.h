// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

#ifndef _HIRO_GAME_H
#define _HIRO_GAME_H

#include "hiro.h"

mrb_value hiro_game_mrb_init(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_start(mrb_state*, mrb_value);

void hiro_game_init(mrb_state*);

#endif
