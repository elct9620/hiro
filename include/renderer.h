#ifndef _HIRO_RENDERER_H
#define _HIRO_RENDERER_H

#include "hiro.h"

static int HIRO_DEFAULT_RENDERER_DRIVER = -1;

mrb_value hiro_renderer_mrb_initialize(mrb_state*, mrb_value);
mrb_value hiro_renderer_mrb_update(mrb_state*, mrb_value);
void hiro_renderer_mrb_free(mrb_state*, void*);

struct hiro_renderer {
  SDL_Renderer* renderer;
};

HIRO_API const struct mrb_data_type hiro_renderer_type;

struct hiro_renderer* hiro_renderer_create(mrb_state*, SDL_Window*);

void hiro_define_renderer(mrb_state*);

#endif
