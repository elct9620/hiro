// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_SCENE_H
#define _HIRO_SCENE_H

#include "hiro.h"

void hiro_scene_update(mrb_state*, mrb_value, mrb_int, mrb_value*);
void hiro_scene_draw(mrb_state*, mrb_value, mrb_int, mrb_value*);

void hiro_scene_init(mrb_state*);

#endif
