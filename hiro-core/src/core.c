#include "core.h"

void hiro_set_instance(mrb_state* mrb, mrb_value instance) {
  struct RClass* hiro;
  mrb_value game_class;

  hiro = mrb_class_get(mrb, "Hiro");
  game_class = mrb_mod_cv_get(mrb, hiro, mrb_intern_lit(mrb, "game_class"));

  if(!mrb_obj_is_instance_of(mrb, instance, mrb_class_ptr(game_class))) {
    mrb_raisef(mrb, E_TYPE_ERROR, "Expect %S, but got %S", game_class, instance);
  }

  mrb_mod_cv_set(mrb, hiro, mrb_intern_lit(mrb, "instance"), instance);
}

mrb_value hiro_mrb_set_game_class(mrb_state* mrb, mrb_value self) {
  mrb_value _class;

  // TODO: Check class type is a "Game" instance
  mrb_get_args(mrb, "C", &_class);
  mrb_cv_set(mrb, self, mrb_intern_lit(mrb, "game_class"), _class);

  return self;
}

mrb_value hiro_mrb_quit_bang(mrb_state* mrb, mrb_value self) {
  mrb_value instance;

  instance = mrb_cv_get(mrb, self, mrb_intern_lit(mrb, "instance"));
  if(!mrb_nil_p(instance)) {
    mrb_funcall(mrb, instance, "stop!", 0);
  }

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
