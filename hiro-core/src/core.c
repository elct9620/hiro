#include "core.h"

mrb_value hiro_mrb_set_game_class(mrb_state* mrb, mrb_value self) {
  // TODO: Save user defined game class
  return self;
}

mrb_value hiro_mrb_quit_bang(mrb_state* mrb, mrb_value self) {
  // TODO: Call "stop!" for game class instance
  return self;
}

void mrb_hiro_core_gem_init(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Hiro", mrb->object_class);

  // Makes Singleton
  mrb_undef_class_method(mrb, klass, "new");

  mrb_define_class_method(mrb, klass, "game_class=", hiro_mrb_set_game_class, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, klass, "quit!", hiro_mrb_quit_bang, MRB_ARGS_NONE());
}

void mrb_hiro_core_gem_final(mrb_state *mrb) {
}
