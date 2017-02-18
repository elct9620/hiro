#include "renderer.h"

const struct mrb_data_type hiro_renderer_type = { "Renderer", hiro_renderer_mrb_free };

mrb_value hiro_renderer_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value win;
  struct hiro_renderer* renderer;
  struct hiro_window* window;

  renderer = (struct hiro_renderer*)DATA_PTR(self);
  if(renderer) {
    hiro_renderer_mrb_free(mrb, renderer);
  }
  mrb_data_init(self, NULL, &hiro_renderer_type);

  mrb_get_args(mrb, "o", &win);

  window = DATA_GET_PTR(mrb, win, &hiro_window_type, struct hiro_window);

  // TODO: Prevent GC free Window before Renderer release
  renderer = hiro_renderer_create(mrb, window->win);
  mrb_data_init(self, renderer, &hiro_renderer_type);

  return self;
}

mrb_value hiro_renderer_mrb_update(mrb_state* mrb, mrb_value self) {
  struct hiro_renderer* renderer;

  renderer = DATA_GET_PTR(mrb, self, &hiro_renderer_type, struct hiro_renderer);
  SDL_RenderClear(renderer->renderer);
  // TODO: Put renderer target draw callback at here
  SDL_RenderPresent(renderer->renderer);

  return self;
}

void hiro_renderer_mrb_free(mrb_state* mrb, void* ptr) {
  struct hiro_renderer* renderer;

  renderer = (struct hiro_renderer*)ptr;
  if(renderer) {
    SDL_DestroyRenderer(renderer->renderer);
  }

  mrb_free(mrb, renderer);
}

struct hiro_renderer* hiro_renderer_create(mrb_state* mrb, SDL_Window* win) {
  struct hiro_renderer* renderer;

  SDL_Renderer* _renderer = SDL_CreateRenderer(win, HIRO_DEFAULT_RENDERER_DRIVER, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(_renderer == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Renderer initialize failed!");
    SDL_DestroyRenderer(_renderer);
    return NULL;
  }

  renderer = (struct hiro_renderer*)mrb_malloc(mrb, sizeof(struct hiro_renderer*));
  renderer->renderer = _renderer;

  return renderer;
}

void hiro_define_renderer(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Renderer", mrb->object_class);
  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_renderer_mrb_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "update", hiro_renderer_mrb_update, MRB_ARGS_NONE());
}

