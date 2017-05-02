#include "object.h"

mrb_value hiro_window_object(mrb_state* mrb, SDL_Window* ptr) {
  return hiro_data_wrap(window, ptr);
}

SDL_Window* hiro_window_ptr(mrb_state* mrb, mrb_value self) {
  SDL_Window* window;
  hiro_data_get(self, window, window);
  return window;
}

mrb_value hiro_renderer_object(mrb_state* mrb, SDL_Renderer* ptr) {
  return hiro_data_wrap(renderer, ptr);
}

SDL_Renderer* hiro_renderer_ptr(mrb_state* mrb, mrb_value self) {
  SDL_Renderer* renderer;
  hiro_data_get(self, renderer, renderer);
  return renderer;
}
