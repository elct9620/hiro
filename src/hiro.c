#include "window.h"

void mrb_hiro_gem_init(mrb_state *mrb) {
  hiro_define_window(mrb);
}

void mrb_hiro_gem_final(mrb_state *mrb) {
}
