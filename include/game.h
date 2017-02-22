#ifndef _HIRO_GAME_H
#define _HIRO_GAME_H

#include "hiro.h"

mrb_value hiro_game_mrb_initialize(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_loop(mrb_state*, mrb_value);
mrb_value hiro_game_mrb_stop_bang(mrb_state*, mrb_value);
void hiro_game_mrb_free(mrb_state*, void*);

struct hiro_game {
  int stop;
};

HIRO_API const struct mrb_data_type hiro_game_type;

void hiro_define_game(mrb_state*);

#endif
