#include "scene.h"

void hiro_scene_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall(mrb, self, "update", argc, argv);
}

void hiro_scene_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall(mrb, self, "draw", argc, argv);
}

void hiro_scene_init(mrb_state* mrb) {
  struct RClass* scene;

  scene = mrb_define_class(mrb, "Scene", mrb->object_class);
}
