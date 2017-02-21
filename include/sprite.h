#ifndef _HIRO_SPRITE_H
#define _HIRO_SPRITE_H

#include "hiro.h"

mrb_value hiro_sprite_mrb_initialize(mrb_state*, mrb_value);
mrb_value hiro_sprite_mrb_draw(mrb_state*, mrb_value);
void hiro_sprite_mrb_free(mrb_state*, void*);

struct hiro_sprite* hiro_sprite_create(mrb_state*, SDL_Renderer*, const char *path, int width, int height);

struct hiro_sprite {
  const char*   path;
  int           width;
  int           height;
  SDL_Texture*  texture;
  SDL_Renderer* renderer;
};

HIRO_API const struct mrb_data_type hiro_sprite_type;

void hiro_define_sprite(mrb_state*);

#endif
