#ifndef _HIRO_GAME_H
#define _HIRO_GAME_H

#include "hiro.h"

mrb_value hiro_game_mrb_initialize(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_update(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_start(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_stop_bang(mrb_state*, mrb_value);
void hiro_game_mrb_free(mrb_state*, void*);

mrb_value hiro_game_create_default_window(mrb_state* mrb);
mrb_value hiro_game_create_default_renderer(mrb_state* mrb, mrb_value);

SDL_Renderer* hiro_game_default_renderer(mrb_state*, mrb_value);

struct hiro_game {
  int stop;
  mrb_value window;
  mrb_value renderer;
};

HIRO_API const struct mrb_data_type hiro_game_type;

void hiro_define_game(mrb_state*);

#endif
