#include "helper.h"

void hiro_helper_each_array_element_fn(mrb_state* mrb, mrb_value self, mrb_sym attr, hiro_fn fn, mrb_int argc, mrb_value* argv) {
  mrb_value elements, object;
  int len, i;

  elements = mrb_iv_get(mrb, self, attr);
  len = RARRAY_LEN(elements);

  for(i = 0; i < len; i++) {
    object = mrb_ary_ref(mrb, elements, i);
    if(!mrb_nil_p(object)) {
      fn(mrb, object, argc, argv);
    }
  }
}

