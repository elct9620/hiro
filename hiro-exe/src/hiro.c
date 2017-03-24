#include "hiro.h"

void mrb_hiro_gem_init(mrb_state *mrb) {
  hiro_define_config(mrb);
  hiro_define_window(mrb);
  hiro_define_renderer(mrb);
  hiro_define_event(mrb);
  hiro_define_game(mrb);
  hiro_define_scene(mrb);
  hiro_define_resource(mrb);

  hiro_define_component(mrb);

  hiro_define_game_object(mrb);
  hiro_define_sprite(mrb);
}

void mrb_hiro_gem_final(mrb_state *mrb) {
}
