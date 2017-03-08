#include "game_object.h"

mrb_bool hiro_is_kind_of_game_object(mrb_state* mrb, mrb_value object) {
  struct RClass* game_object_class;

  game_object_class = mrb_class_get(mrb, "GameObject");

  if(!mrb_obj_is_kind_of(mrb, object, game_object_class)) {
    return 0;
  }

  return 1;
}

void hiro_game_object_set_parent(mrb_state* mrb, mrb_value self, mrb_value parent) {
  mrb_bool is_game_object;

  is_game_object = hiro_is_kind_of_game_object(mrb, parent);

  if(!is_game_object) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not valid GameObject", parent);
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@parent"), parent);
}

void hiro_game_object_add_child(mrb_state* mrb, mrb_value self, mrb_value object) {
  mrb_value children;

  children = hiro_helper_get_array_attribute(mrb, self, mrb_intern_lit(mrb, "children"));

  if(!hiro_is_kind_of_game_object(mrb, object)) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not vaild GameObject.", object);
  }

  mrb_ary_push(mrb, children, object);

  hiro_game_object_set_parent(mrb, object, self);
}

void hiro_game_object_add_component(mrb_state* mrb, mrb_value self, mrb_value object) {
  mrb_value components;

  components = hiro_helper_get_array_attribute(mrb, self, mrb_intern_lit(mrb, "components"));

  if(!hiro_is_kind_of_component(mrb, object)) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not vaild Component.", object);
  }

  mrb_ary_push(mrb, components, object);

  hiro_component_set_game_object(mrb, object, self);
}

void hiro_game_object_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  hiro_helper_each_array_element_fn(mrb, self, mrb_intern_lit(mrb, "components"), hiro_component_update, argc, argv);
  hiro_helper_each_array_element_fn(mrb, self, mrb_intern_lit(mrb, "children"), hiro_game_object_update, argc, argv);
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_game_object_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  hiro_helper_each_array_element_fn(mrb, self, mrb_intern_lit(mrb, "components"), hiro_component_draw, 0, NULL);
  hiro_helper_each_array_element_fn(mrb, self, mrb_intern_lit(mrb, "children"), hiro_game_object_draw, 0, NULL);
  mrb_funcall(mrb, self, "draw", 0, NULL);

}

mrb_value hiro_game_object_mrb_add(mrb_state* mrb, mrb_value self) {
  mrb_value object;

  mrb_get_args(mrb, "o", &object);
  hiro_game_object_add_child(mrb, self, object);

  return self;
}

mrb_value hiro_game_object_mrb_parent(mrb_state* mrb, mrb_value self) {
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@parent"));
}

mrb_value hiro_game_object_mrb_set_parent(mrb_state* mrb, mrb_value self) {
  mrb_value parent;

  mrb_get_args(mrb, "o", &parent);
  hiro_game_object_set_parent(mrb, self, parent);

  return self;
}

mrb_value hiro_game_object_mrb_add_component(mrb_state* mrb, mrb_value self) {
  mrb_value component;

  mrb_get_args(mrb, "o", &component);
  hiro_game_object_add_component(mrb, self, component);

  return self;
}

void hiro_define_game_object(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "GameObject", mrb->object_class);

  mrb_define_method(mrb, klass, "add", hiro_game_object_mrb_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "update", hiro_helper_mrb_blob_api, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "draw", hiro_helper_mrb_blob_api, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "parent", hiro_game_object_mrb_parent, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "parent=", hiro_game_object_mrb_set_parent, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "add_component", hiro_game_object_mrb_add_component, MRB_ARGS_REQ(1));
}
