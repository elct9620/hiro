#include "hiro.h"

mrb_value hiro_mrb_set_entrypoint(mrb_state* mrb, mrb_value self) {
  mrb_value _entrypoint;

  mrb_get_args(mrb, "C", &_entrypoint);
  mrb_cv_set(mrb, self, mrb_intern_lit(mrb, "entrypoint"), _entrypoint);

  return self;
}

mrb_value hiro_mrb_quit_bang(mrb_state* mrb, mrb_value self) {
  mrb_value instance;

  instance = mrb_cv_get(mrb, self, mrb_intern_lit(mrb, "instance"));
  mrb_funcall(mrb, instance, "stop!", 0);

  return self;
}

void hiro_define(mrb_state* mrb) {
  struct RClass* hiro;
  hiro = mrb_define_module(mrb, "Hiro");

  mrb_define_class_method(mrb, hiro, "entrypoint=", hiro_mrb_set_entrypoint, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, hiro, "quit!", hiro_mrb_quit_bang, MRB_ARGS_NONE());
}

void mrb_hiro_gem_init(mrb_state *mrb) {
  hiro_define(mrb);
  hiro_define_window(mrb);
  hiro_define_renderer(mrb);
  hiro_define_event(mrb);
  hiro_define_sprite(mrb);
  hiro_define_game(mrb);
}

void mrb_hiro_gem_final(mrb_state *mrb) {
}
