#include "component.h"

mrb_bool hiro_is_kind_of_component(mrb_state* mrb, mrb_value object) {
  struct RClass* component_class;

  component_class = mrb_class_get(mrb, "Component");

  if(!mrb_obj_is_kind_of(mrb, object, component_class)) {
    return 0;
  }

  return 1;
}

void hiro_component_set_name(mrb_state* mrb, mrb_value self, const char* path) {
  mrb_mod_cv_set(mrb, mrb_obj_class(mrb, self), mrb_intern_lit(mrb, "name"), mrb_str_new_cstr(mrb, path));
}

void hiro_component_set_game_object(mrb_state* mrb, mrb_value self, mrb_value game_object) {
  mrb_bool is_game_object;
  mrb_sym attr;
  mrb_value _component_name;
  const char *component_name;
  char* attr_name;
  size_t len;

  is_game_object = hiro_is_kind_of_game_object(mrb, game_object);

  if(!is_game_object) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not valid GameObject", game_object);
    return;
  }

  _component_name = hiro_component_mrb_name(mrb, self);
  if(!mrb_nil_p(_component_name)) {
    component_name = mrb_str_to_cstr(mrb, _component_name);
    len = strlen(component_name);
    attr_name = (char *)malloc(len + 1);
    attr_name[0] = '@';
    strncpy(attr_name + 1, component_name, len);
    attr_name[len + 1] = '\0';
    attr = mrb_intern_cstr(mrb, attr_name);
    mrb_iv_set(mrb, game_object, attr, self);
    free(attr_name);
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@game_object"), game_object);
}

void hiro_component_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_component_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  mrb_funcall(mrb, self, "draw", 0, NULL);
}

mrb_value hiro_component_mrb_name(mrb_state* mrb, mrb_value self) {
  struct RClass* component;
  mrb_sym attr;

  component = mrb_obj_class(mrb, self);
  attr = mrb_intern_lit(mrb, "name");

  if(mrb_mod_cv_defined(mrb, component, attr)) {
    return mrb_mod_cv_get(mrb, component, attr);
  }
  return mrb_nil_value();
}

void hiro_define_component(mrb_state* mrb) {
  struct RClass* klass;

  klass = mrb_define_class(mrb, "Component", mrb->object_class);
  mrb_define_method(mrb, klass, "update", hiro_helper_mrb_blob_api, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "draw", hiro_helper_mrb_blob_api, MRB_ARGS_NONE());

  // Component Implements
  hiro_define_renderer_component(mrb, klass);
  hiro_define_animator_component(mrb, klass);
}
