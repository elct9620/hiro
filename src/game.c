#include "game.h"

mrb_value hiro_game_object(mrb_state* mrb, struct hiro_game *ptr) {
  return hiro_data_wrap(game, ptr);
}

struct hiro_game* hiro_game_ptr(mrb_state* mrb, mrb_value self) {
  struct hiro_game *game;
  hiro_data_get(self, game, game);
  return game;
}

// TODO: Provide create options
struct hiro_game* hiro_create_game(mrb_state* mrb) {
  struct hiro_game* game;
  SDL_Window* window;
  SDL_Renderer* renderer;

  const char* name;
  mrb_int width, height;

  name = mrb_str_to_cstr(mrb, hiro_config_get("title"));
  width = mrb_fixnum(hiro_config_get("width"));
  height = mrb_fixnum(hiro_config_get("height"));

  // Create Window
  // TODO: Read from params or config
  window = SDL_CreateWindow(name, 0, 0, width, height, SDL_WINDOW_SHOWN);
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

  game = (struct hiro_game*)mrb_malloc(mrb, sizeof(struct hiro_game));
  game->stop = 0;
  game->window = window;
  game->renderer = renderer;

  return game;
}

void hiro_game_draw(mrb_state* mrb, mrb_value self) {
  mrb_funcall(mrb, self, "draw", 0);
}

void hiro_game_update(mrb_state* mrb, mrb_value self, mrb_int ticks) {
  mrb_funcall(mrb, self, "update", 1, mrb_fixnum_value(ticks));
}

void hiro_game_poll_event(mrb_state* mrb, mrb_value self) {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    hiro_event_emit(mrb, event);
  }
}

mrb_value hiro_game_mrb_init(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;

  game = hiro_create_game(mrb);
  r_iv_set("@data", hiro_game_object(mrb, game));

  return self;
}

mrb_value hiro_game_mrb_start(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;

  game = hiro_game_ptr(mrb, r_iv_get("@data"));

  // TODO: Set FPS from Ruby
  mrb_int FPS = 60;
  mrb_int FIXED_TICKS =ceil(1000 / FPS); // Milliseconds

  mrb_int current_ticks = SDL_GetTicks();
  mrb_int next_update_ticks = current_ticks + FIXED_TICKS;

  while(!game->stop) {
    current_ticks = SDL_GetTicks();

    hiro_game_poll_event(mrb, self);
    hiro_game_update(mrb, self, current_ticks);

    if(current_ticks > next_update_ticks) {
      // TODO: Make sure update ticks not overflow
      next_update_ticks = current_ticks + FIXED_TICKS;

      SDL_RenderClear(game->renderer);
      hiro_game_draw(mrb, self);
      SDL_RenderPresent(game->renderer);
    }
  }

  return self;
}

mrb_value hiro_game_mrb_stop_bang(mrb_state* mrb, mrb_value self) {
  struct hiro_game *game;
  game = hiro_game_ptr(mrb, r_iv_get("@data"));

  game->stop = 1;

  return self;
}

void hiro_game_init(mrb_state* mrb) {
  struct RClass* game;

  game = mrb_define_class(mrb, "Game", mrb->object_class);

  mrb_define_method(mrb, game, "init", hiro_game_mrb_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, game, "start", hiro_game_mrb_start, MRB_ARGS_NONE());
  mrb_define_method(mrb, game, "stop!", hiro_game_mrb_stop_bang, MRB_ARGS_NONE());
}
