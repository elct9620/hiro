#include "hiro.h"

void mrb_hiro_gem_init(mrb_state* mrb) {
  hiro_core_init(mrb);
  hiro_game_init(mrb);
}

void mrb_hiro_gem_final(mrb_state* mrb) {
}
