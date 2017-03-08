#ifndef _HIRO_SCENE_H
#define _HIRO_SCENE_H

#include "hiro.h"

HIRO_API void hiro_scene_update(mrb_state*, mrb_value, mrb_int);
HIRO_API void hiro_scene_draw(mrb_state*, mrb_value);

mrb_value hiro_scene_get_children(mrb_state*, mrb_value);
void hiro_scene_add_child(mrb_state*, mrb_value, mrb_value);
void hiro_scene_each_child_call(mrb_state*, mrb_value, const char*, mrb_int, mrb_value*);

mrb_value hiro_scene_mrb_add(mrb_state*, mrb_value);
mrb_value hiro_scene_mrb_blob_api(mrb_state*, mrb_value);

void hiro_define_scene(mrb_state*);

#endif
