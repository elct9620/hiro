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
  struct RClass* game_object_class;
  mrb_bool is_game_object, is_nil;

  game_object_class = mrb_class_get(mrb, "GameObject");

  is_game_object = mrb_obj_is_kind_of(mrb, parent, game_object_class);
  is_nil = mrb_nil_p(parent);

  if(!is_game_object && !is_nil) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not valid GameObject", parent);
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@parent"), parent);
}

mrb_value hiro_game_object_get_children(mrb_state* mrb, mrb_value self) {
  mrb_sym attr;
  mrb_value children;

  attr = mrb_intern_lit(mrb, "children");

  if(mrb_iv_defined(mrb, self, attr)) {
    return mrb_iv_get(mrb, self, attr);
  }

  children = mrb_ary_new(mrb);
  mrb_iv_set(mrb, self, attr, children);

  return children;
}

void hiro_game_object_add_child(mrb_state* mrb, mrb_value self, mrb_value object) {
  mrb_value children;

  children = hiro_game_object_get_children(mrb, self);

  if(!hiro_is_kind_of_game_object(mrb, object)) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not vaild GameObject.", object);
  }

  mrb_ary_push(mrb, children, object);

  hiro_game_object_set_parent(mrb, object, self);
}

void hiro_game_object_each_child_call(mrb_state* mrb, mrb_value self, const char* method_name, mrb_int argc, mrb_value* argv) {
  mrb_value children, object;
  int len, i;

  children = hiro_game_object_get_children(mrb, self);
  len = RARRAY_LEN(children);

  for(i = 0; i < len; i++) {
    object = mrb_ary_ref(mrb, children, i);
    if(!mrb_nil_p(object)) {
      mrb_funcall(mrb, object, method_name, argc, argv);
    }
  }
}

mrb_value hiro_game_object_mrb_add(mrb_state* mrb, mrb_value self) {
  mrb_value object;

  mrb_get_args(mrb, "o", &object);
  hiro_game_object_add_child(mrb, self, object);

  return self;
}

mrb_value hiro_game_object_mrb_update(mrb_state* mrb, mrb_value self) {
  hiro_game_object_each_child_call(mrb, self, "update", 0, NULL);
  return self;
}

mrb_value hiro_game_object_mrb_draw(mrb_state* mrb, mrb_value self) {
  hiro_game_object_each_child_call(mrb, self, "draw", 0, NULL);
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

void hiro_define_game_object(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "GameObject", mrb->object_class);

  mrb_define_method(mrb, klass, "add", hiro_game_object_mrb_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "update", hiro_game_object_mrb_update, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "draw", hiro_game_object_mrb_draw, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "parent", hiro_game_object_mrb_parent, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "parent=", hiro_game_object_mrb_set_parent, MRB_ARGS_REQ(1));
}
