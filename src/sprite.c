#include "sprite.h"

void hiro_define_sprite(mrb_state* mrb) {
  struct RClass *klass, *game_object_class;

  game_object_class = mrb_class_get(mrb, "GameObject");
  klass = mrb_define_class(mrb, "Sprite", game_object_class);
}
