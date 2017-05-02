#include "hiro.h"

void mrb_hiro_gem_init(mrb_state* mrb) {
  HIRO_INIT(core);
  HIRO_INIT(game);

  HIRO_INIT(game_object);
  HIRO_INIT(scene);
  HIRO_INIT(component);
}

void mrb_hiro_gem_final(mrb_state* mrb) {
}
