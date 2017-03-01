#ifndef _HIRO_SCENE_H
#define _HIRO_SCENE_H

#include "hiro.h"

mrb_value hiro_scene_get_children(mrb_state*, mrb_value);
void hiro_secen_add_child(mrb_state*, mrb_value, mrb_value);
void hiro_scene_each_child_cll(mrb_state*, mrb_value, const char*, mrb_int, mrb_value*);

mrb_value hiro_scene_mrb_add(mrb_state*, mrb_value);
mrb_value hiro_scene_mrb_update(mrb_state*, mrb_value);
mrb_value hiro_scene_mrb_draw(mrb_state*, mrb_value);

void hiro_define_scene(mrb_state*);

#endif
