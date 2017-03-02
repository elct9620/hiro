#include "game_object.h"

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
  struct RClass* game_object_class;
  mrb_value children;

  game_object_class = mrb_class_get(mrb, "GameObject");
  children = hiro_game_object_get_children(mrb, self);

  if(!mrb_obj_is_kind_of(mrb, object, game_object_class)) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not vaild GameObject.", object);
  }

  mrb_ary_push(mrb, children, object);
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

void hiro_define_game_object(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "GameObject", mrb->object_class);

  mrb_define_method(mrb, klass, "add", hiro_game_object_mrb_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "update", hiro_game_object_mrb_update, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "draw", hiro_game_object_mrb_draw, MRB_ARGS_NONE());
}
