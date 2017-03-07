#ifndef _HIRO_COMPONENT_H
#define _HIRO_COMPONENT_H

#include "hiro.h"

HIRO_API mrb_bool hiro_is_kind_of_component(mrb_state* mrb, mrb_value);
HIRO_API void hiro_component_set_name(mrb_state*, mrb_value self, const char*);

void hiro_component_set_game_object(mrb_state* mrb, mrb_value, mrb_value);

void hiro_component_update(mrb_state*, mrb_value);
void hiro_component_draw(mrb_state*, mrb_value);

mrb_value hiro_component_mrb_name(mrb_state*, mrb_value);

void hiro_define_component(mrb_state* mrb);

#endif
