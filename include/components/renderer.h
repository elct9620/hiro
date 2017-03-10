#ifndef _HIRO_RENDERER_COMPONENT_H
#define _HIRO_RENDERER_COMPONENT_H

#include "hiro.h"

HIRO_API mrb_value hiro_renderer_component_new(mrb_state*, mrb_int, mrb_value*);

void hiro_renderer_component_setup_animation(mrb_state*, mrb_value);

mrb_value hiro_renderer_component_mrb_initialize(mrb_state*, mrb_value);
mrb_value hiro_renderer_component_mrb_draw(mrb_state*, mrb_value);
mrb_value hiro_renderer_component_mrb_set_animate(mrb_state*, mrb_value);
void hiro_renderer_component_mrb_free(mrb_state*, void*);

struct hiro_renderer_component* hiro_renderer_component_create(mrb_state*, SDL_Renderer*, const char *path);

struct hiro_renderer_component {
  const char*   path;
  int           width;
  int           height;
  int           scaleX;
  int           scaleY;
  int           xFrames;
  int           yFrames;
  SDL_Texture*  texture;
  SDL_Renderer* renderer;
};

HIRO_API const struct mrb_data_type hiro_renderer_component_type;

void hiro_define_renderer_component(mrb_state*, struct RClass*);

#endif
