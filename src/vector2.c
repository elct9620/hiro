#include "vector2.h"

mrb_value hiro_vector2_value(mrb_state* mrb, mrb_int x, mrb_int y) {
  struct RClass* klass;
  mrb_value argv[2];
  klass = mrb_class_get(mrb, "Vector2");
  argv[0] = mrb_fixnum_value(x);
  argv[1] = mrb_fixnum_value(y);
  return mrb_obj_new(mrb, klass, 2, argv);
}
