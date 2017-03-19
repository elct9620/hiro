#ifndef _HIRO_ANIMATOR_COMPONENT_H
#define _HIRO_ANIMATOR_COMPONENT_H

#include "hiro.h"

mrb_value hiro_animator_component_mrb_initialize(mrb_state*, mrb_value);

void hiro_define_animator_component(mrb_state* mrb, struct RClass*);

#endif
