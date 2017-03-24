#ifndef _HIRO_GAME_OBJECT_H
#define _HIRO_GAME_OBJECT_H

#include "hiro.h"

HIRO_API mrb_bool hiro_is_kind_of_game_object(mrb_state* mrb, mrb_value);

void hiro_game_object_set_parent(mrb_state* mrb, mrb_value, mrb_value);

void hiro_game_object_add_child(mrb_state*, mrb_value, mrb_value);
void hiro_game_object_add_component(mrb_state*, mrb_value, mrb_value);

void hiro_game_object_update(mrb_state*, mrb_value, mrb_int, mrb_value*);
void hiro_game_object_draw(mrb_state*, mrb_value, mrb_int, mrb_value*);

mrb_value hiro_game_object_mrb_add(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_parent(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_set_parent(mrb_state*, mrb_value);
mrb_value hiro_game_object_mrb_add_component(mrb_state*, mrb_value);

void hiro_define_game_object(mrb_state*);

#endif
