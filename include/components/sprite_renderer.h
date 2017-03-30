// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_SPRITE_RENDERER_H
#define _HIRO_SPRITE_RENDERER_H

#include "hiro.h"

// Object Define
struct hiro_sprite_renderer {
  int           width;
  int           height;
  SDL_Texture*  texture;
  SDL_Renderer* renderer;
};

static void hiro_free_sprite_renderer(mrb_state*, void* ptr);
static const struct mrb_data_type hiro_sprite_renderer_type = { "sprite_renderer", hiro_free_sprite_renderer };
mrb_value hiro_sprite_renderer_object(mrb_state*, struct hiro_sprite_renderer*);
struct hiro_sprite_renderer* hiro_sprite_renderer_ptr(mrb_state*, mrb_value);
struct hiro_sprite_renderer* hiro_create_sprite_renderer(mrb_state*, SDL_Renderer*, const char*);

void hiro_free_sprite_renderer(mrb_state* mrb, void *ptr) {
  struct hiro_sprite_renderer* renderer = (struct hiro_sprite_renderer*)ptr;
  SDL_DestroyTexture(renderer->texture);
  mrb_free(mrb, renderer);
}

// C API
SDL_RendererFlip hiro_sprite_renderer_flip(mrb_int x, mrb_int y);
struct hiro_vec2 hiro_sprite_renderer_scale(mrb_state*, mrb_value);
struct hiro_vec2 hiro_sprite_renderer_size(mrb_state*, mrb_value);
struct hiro_vec2 hiro_sprite_renderer_position(mrb_state*, mrb_value);

// Ruby API
mrb_value hiro_sprite_renderer_mrb_init(mrb_state*, mrb_value);
mrb_value hiro_sprite_renderer_mrb_draw(mrb_state*, mrb_value);

void hiro_sprite_renderer_init(mrb_state*, struct RClass*);

#endif
