#include "config.h"

mrb_bool hiro_config_is_setter(const char *name) {
  size_t len;

  len = strlen(name);

  if(name[len - 1] == '=') {
    return 1;
  }

  return 0;
}

void hiro_config_set(mrb_state* mrb, mrb_value self, mrb_sym attr, mrb_value value) {
  if(mrb_cv_defined(mrb, self, attr)) {
    mrb_cv_set(mrb, self, attr, value);
    return;
  }

  mrb_raisef(mrb, E_RUNTIME_ERROR, "Cannot set undefined config %S", mrb_symbol_value(attr));
}

mrb_value hiro_config_mrb_register(mrb_state* mrb, mrb_value self) {
  mrb_sym name;
  mrb_value value;
  mrb_int argc;

  argc = mrb_get_args(mrb, "n|o", &name, &value);
  value = argc > 1 ? value : mrb_nil_value();

  if(!mrb_cv_defined(mrb, self, name)) {
    mrb_cv_set(mrb, self, name, value);
  }

  return self;
}

mrb_value hiro_config_mrb_method_missing(mrb_state* mrb, mrb_value self) {
  mrb_sym name;
  mrb_value *values;
  mrb_int value_len;
  const char *method_name;
  char *attr_name;
  size_t method_len;

  mrb_get_args(mrb, "n*", &name, &values, &value_len);
  method_name = mrb_sym2name(mrb, name);
  method_len = strlen(method_name);

  if(mrb_cv_defined(mrb, self, name)) {
    return mrb_cv_get(mrb, self, name);
  }

  if(hiro_config_is_setter(method_name)) {
    attr_name = (char*)malloc(method_len);
    attr_name = strncpy(attr_name, method_name, method_len - 1);
    hiro_config_set(mrb, self, mrb_intern_cstr(mrb, attr_name), values[0]);
    free(attr_name);
    return mrb_nil_value();
  }

  mrb_raisef(mrb, E_RUNTIME_ERROR, "Can not found config %S", mrb_symbol_value(name));

  return mrb_nil_value();
}

void hiro_define_config(mrb_state* mrb) {
  struct RClass* klass = mrb_define_class(mrb, "Config", mrb->object_class);
  MRB_SET_INSTANCE_TT(klass, MRB_TT_SCLASS);
  mrb_undef_class_method(mrb, klass, "new");

  mrb_define_class_method(mrb, klass, "register", hiro_config_mrb_register, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, klass, "method_missing", hiro_config_mrb_method_missing, MRB_ARGS_ANY());
}
