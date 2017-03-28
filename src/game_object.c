#include "game_object.h"

void hiro_game_object_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  HIRO_EACH_FN(self, "@components", hiro_component_update, argc, argv);
  HIRO_EACH_FN(self, "@children", hiro_game_object_update, argc, argv);
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_game_object_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  HIRO_EACH_FN(self, "@components", hiro_component_draw, argc, argv);
  HIRO_EACH_FN(self, "@children", hiro_game_object_draw, argc, argv);
  mrb_funcall(mrb, self, "draw", argc, argv);
}


void hiro_game_object_init(mrb_state* mrb) {
  struct RClass* game_object;

  game_object = mrb_define_class(mrb, "GameObject", mrb->object_class);
}
