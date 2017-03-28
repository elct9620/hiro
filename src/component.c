#include "component.h"

void hiro_component_init(mrb_state* mrb) {
  struct RClass* component;

  component = mrb_define_class(mrb, "Component", mrb->object_class);
}
