#include "components/animator.h"

mrb_value hiro_animator_component_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@current"), mrb_nil_value());
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@frame"), mrb_fixnum_value(0));
  hiro_helper_get_hash_attribute(mrb, self, mrb_intern_lit(mrb, "@animations"));
  hiro_component_set_name(mrb, self, "animator");
  return self;
}

void hiro_define_animator_component(mrb_state* mrb, struct RClass* component_class) {
  struct RClass* klass;

  klass = mrb_define_class(mrb, "AnimatorComponent", component_class);
  mrb_define_method(mrb, klass, "initialize", hiro_animator_component_mrb_initialize, MRB_ARGS_NONE());
}
