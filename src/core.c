#include "core.h"

mrb_value hiro_core_mrb_start(mrb_state* mrb, mrb_value self) {
  struct RClass* game;
  mrb_value game_class, instance;

  mrb_get_args(mrb, "C", &game_class);
  game = mrb_class_ptr(game_class);

  instance = mrb_obj_new(mrb, game, 0, NULL);
  hiro_game_instance_set(mrb, instance);
  mrb_funcall(mrb, instance, "start", 0, NULL);

  return self;
}

void hiro_core_init(mrb_state* mrb) {
  struct RClass* krn;

  // NOTE: Discuss is necessary to use this way
  krn = mrb->kernel_module;
  mrb_define_method(mrb, krn, "start", hiro_core_mrb_start, MRB_ARGS_REQ(1));
}
