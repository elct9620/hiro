#include "game_object.h"

void hiro_game_object_init(mrb_state* mrb) {
  struct RClass* game_object;

  game_object = mrb_define_class(mrb, "GameObject", mrb->object_class);
}
