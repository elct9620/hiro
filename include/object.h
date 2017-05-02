// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

#ifndef _HIRO_OBJECT_H
#define _HIRO_OBJECT_H

#include "hiro.h"

// Macros
#define hiro_data_wrap(name, data)  mrb_obj_value(Data_Wrap_Struct(mrb, mrb->object_class, &hiro_##name##_type, data))
#define hiro_data_get(self, name, data)  Data_Get_Struct(mrb, self, &hiro_##name##_type, data)

// Objects
static void hiro_free_window(mrb_state*, void *ptr);
static const struct mrb_data_type hiro_window_type = { "window", hiro_free_window };
mrb_value hiro_window_object(mrb_state*, SDL_Window*);
SDL_Window* hiro_window_ptr(mrb_state*, mrb_value);

static void hiro_free_renderer(mrb_state*, void *ptr);
static const struct mrb_data_type hiro_renderer_type = { "renderer", hiro_free_renderer };
mrb_value hiro_renderer_object(mrb_state*, SDL_Renderer*);
SDL_Renderer* hiro_renderer_ptr(mrb_state*, mrb_value);

// Implements
void hiro_free_window(mrb_state* mrb, void* ptr) {
  SDL_Window* window = (SDL_Window*)ptr;
  SDL_DestroyWindow(window);
}

void hiro_free_renderer(mrb_state* mrb, void *ptr) {
  SDL_Renderer* renderer = (SDL_Renderer*)ptr;
  SDL_DestroyRenderer(renderer);
}

#endif
