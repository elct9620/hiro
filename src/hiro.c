#include "hiro.h"

SDL_Renderer* hiro_default_renderer(mrb_state* mrb) {
  struct RClass* hiro;
  mrb_value instance;

  hiro = mrb_module_get(mrb, "Hiro");
  instance = mrb_mod_cv_get(mrb, hiro, mrb_intern_lit(mrb, "instance"));

  return hiro_game_default_renderer(mrb, instance);
}

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

void hiro_set_instance(mrb_state* mrb, mrb_value instance) {
  struct RClass* hiro;
  mrb_value _entrypoint;

  hiro = mrb_module_get(mrb, "Hiro");
  _entrypoint = mrb_mod_cv_get(mrb, hiro, mrb_intern_lit(mrb, "entrypoint"));

  if(!mrb_obj_is_instance_of(mrb, instance, mrb_class_ptr(_entrypoint))) {
    // TODO: Improve error message
    mrb_raisef(mrb, E_TYPE_ERROR, "The game instance is not match configure!");
  }

  mrb_mod_cv_set(mrb, hiro, mrb_intern_lit(mrb, "instance"), instance);
}

void hiro_define(mrb_state* mrb) {
  struct RClass* hiro;
  hiro = mrb_define_module(mrb, "Hiro");

  mrb_define_class_method(mrb, hiro, "entrypoint=", hiro_mrb_set_entrypoint, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, hiro, "quit!", hiro_mrb_quit_bang, MRB_ARGS_NONE());
}

void mrb_hiro_gem_init(mrb_state *mrb) {
  hiro_define(mrb);
  hiro_define_config(mrb);
  hiro_define_window(mrb);
  hiro_define_renderer(mrb);
  hiro_define_event(mrb);
  hiro_define_game(mrb);
  hiro_define_scene(mrb);

  hiro_define_component(mrb);

  hiro_define_game_object(mrb);
  hiro_define_sprite(mrb);
}

void mrb_hiro_gem_final(mrb_state *mrb) {
}
