#include "scene.h"

void hiro_define_scene(mrb_state* mrb) {
  struct RClass *klass, *game_object_class;
  game_object_class = mrb_class_get(mrb, "GameObject");

  klass = mrb_define_class(mrb, "Scene", game_object_class);
}
