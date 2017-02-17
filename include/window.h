#include <SDL2/SDL.h>

#include <mruby.h>

#ifndef _HIRO_WINDOW
#define _HIRO_WINDOW

mrb_value hiro_mrb_window_initialize(mrb_state*, mrb_value);

void hiro_define_window(mrb_state*);

#endif
