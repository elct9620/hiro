// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

#ifndef _HIRO_GAME_H
#define _HIRO_GAME_H

#include "hiro.h"

// Object Define
struct hiro_game {
  int           stop;
  SDL_Window*   window;
  SDL_Renderer* renderer;
};

static void hiro_free_game(mrb_state*, void* ptr);
static const struct mrb_data_type hiro_game_type = { "game", hiro_free_game };
mrb_value hiro_game_object(mrb_state*, struct hiro_game*);
struct hiro_game* hiro_game_ptr(mrb_state*, mrb_value);
struct hiro_game* hiro_create_game(mrb_state*);

void hiro_free_game(mrb_state* mrb, void *ptr) {
  struct hiro_game* game = (struct hiro_game*)ptr;
  if(game) {
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);
    mrb_free(mrb, game);
  }
}

// C API
void hiro_game_draw(mrb_state*, mrb_value);
void hiro_game_update(mrb_state*, mrb_value, mrb_int);
void hiro_game_poll_event(mrb_state*, mrb_value);

// Ruby API
mrb_value hiro_game_mrb_init(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_start(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_stop_bang(mrb_state*, mrb_value);

void hiro_game_init(mrb_state*);

#endif
