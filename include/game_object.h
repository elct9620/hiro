#ifndef _HIRO_GAME_OBJECT_H
#define _HIRO_GAME_OBJECT_H

#include "hiro.h"

mrb_value hiro_game_object_get_children(mrb_state*, mrb_value);
void hiro_game_object_add_child(mrb_state*, mrb_value, mrb_value);
void hiro_game_object_each_child_call(mrb_state*, mrb_value, const char*, mrb_int, mrb_value*);

mrb_value hiro_game_object_mrb_add(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_update(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_draw(mrb_state*, mrb_value);

void hiro_define_game_object(mrb_state*);

#endif
