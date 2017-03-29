#include "component.h"

mrb_bool hiro_is_component(mrb_state* mrb, mrb_value object) {
  struct RClass* component;

  component = mrb_class_get(mrb, "Component");
  if(!mrb_obj_is_kind_of(mrb, object, component)) {
    return 0;
  }

  return 1;
}

void hiro_component_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_component_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall(mrb, self, "draw", argc, argv);
}

void hiro_component_init(mrb_state* mrb) {
  struct RClass* component;

  component = mrb_define_class(mrb, "Component", mrb->object_class);

  hiro_sprite_renderer_init(mrb, component);
}
