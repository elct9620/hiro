#include "helper.h"

mrb_value hiro_helper_get_hash_attribute(mrb_state* mrb, mrb_value instance, mrb_sym attr) {
  if(!mrb_iv_defined(mrb, instance, attr)) {
    mrb_iv_set(mrb, instance, attr, mrb_hash_new(mrb));
  }

  return mrb_iv_get(mrb, instance, attr);
}

mrb_value hiro_helper_get_array_attribute(mrb_state* mrb, mrb_value instance, mrb_sym attr) {
  if(!mrb_iv_defined(mrb, instance, attr)) {
    mrb_iv_set(mrb, instance, attr, mrb_ary_new(mrb));
  }

  return mrb_iv_get(mrb, instance, attr);
}

void hiro_helper_each_array_element_do(mrb_state* mrb, mrb_value instance, mrb_sym attr, const char* method_name, mrb_int argc, mrb_value* argv) {
  mrb_value elements, object;
  int len, i;

  elements = hiro_helper_get_array_attribute(mrb, instance, attr);
  len = RARRAY_LEN(elements);

  for(i = 0; i < len; i++) {
    object = mrb_ary_ref(mrb, elements, i);
    if(!mrb_nil_p(object)) {
      mrb_funcall(mrb, object, method_name, argc, argv);
    }
  }
}
