#include <stdio.h>
#include "window.h"

mrb_value hiro_mrb_window_initialize(mrb_state* mrb, mrb_value value) {
  // TODO: Implement SLD2 Window initialize
  return value;
}

void hiro_define_window(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Window", mrb->object_class);

  mrb_define_method(mrb, klass, "initialize", hiro_mrb_window_initialize, MRB_ARGS_OPT(2));
}
