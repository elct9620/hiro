#include "scene.h"

void hiro_scene_init(mrb_state* mrb) {
  struct RClass* scene;

  scene = mrb_define_class(mrb, "Scene", mrb->object_class);
}
