#include "hiro.h"

void mrb_hiro_gem_init(mrb_state *mrb) {
  hiro_define_window(mrb);
  hiro_define_renderer(mrb);
  hiro_define_event(mrb);
}

void mrb_hiro_gem_final(mrb_state *mrb) {
}
