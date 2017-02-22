#ifndef _HIRO_CORE_H
#define _HIRO_CORE_H

#include "hiro.h"

SDL_Renderer* hiro_default_renderer(mrb_state*);

mrb_value hiro_mrb_set_entrypoint(mrb_state*, mrb_value);
mrb_value hiro_mrb_quit_bang(mrb_state*, mrb_value);

void hiro_set_instance(mrb_state*, mrb_value);

void hiro_define(mrb_state*);

#endif
