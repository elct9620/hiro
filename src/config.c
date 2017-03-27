#include "config.h"

mrb_value hiro_config_mrb_get(mrb_state* mrb, const char* name) {
  struct RClass* config;
  mrb_value config_object;

  config = mrb_class_get(mrb, "Config");
  config_object = mrb_obj_value(config);

  return mrb_funcall(mrb, config_object, name, 0);
}
