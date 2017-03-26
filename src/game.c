#include "game.h"

mrb_value hiro_game_mrb_init(mrb_state* mrb, mrb_value self) {
  SDL_Window* window;
  SDL_Renderer* renderer;

  // Create Window
  // TODO: Read from params or config
  window = SDL_CreateWindow("Hiro Framework", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);
  if(!window) {
    SDL_DestroyWindow(window);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Window initialize failed!");
  }

  // Create Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(!renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Renderer initialize failed!");
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@window"), hiro_window_object(mrb, window));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@renderer"), hiro_renderer_object(mrb, renderer));

  return self;
}

mrb_value hiro_game_mrb_start(mrb_state* mrb, mrb_value self) {
  SDL_Renderer* renderer;

  renderer = hiro_renderer_ptr(mrb, mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@renderer")));

  SDL_Event ev;
  int quit = 0;

  while(!quit) {
    while(SDL_PollEvent(&ev)) {
      switch(ev.type) {
        case SDL_QUIT:
        case SDL_KEYDOWN:
          quit = 1;
      }
    }

    SDL_Delay(16);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  return self;
}

void hiro_game_init(mrb_state* mrb) {
  struct RClass* game;

  game = mrb_define_class(mrb, "Game", mrb->object_class);

  mrb_define_method(mrb, game, "init", hiro_game_mrb_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, game, "start", hiro_game_mrb_start, MRB_ARGS_NONE());
}
