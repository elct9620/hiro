#include "component.h"

void hiro_component_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_component_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall(mrb, self, "draw", argc, argv);
}

void hiro_component_init(mrb_state* mrb) {
  struct RClass* component;

  component = mrb_define_class(mrb, "Component", mrb->object_class);
}
