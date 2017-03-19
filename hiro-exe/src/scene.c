#include "scene.h"

void hiro_scene_update(mrb_state* mrb, mrb_value scene, mrb_int ticks) {
  mrb_value argv[1] = {mrb_fixnum_value(ticks)};
  mrb_funcall_argv(mrb, scene, mrb_intern_lit(mrb, "update"), 1, argv);
  hiro_helper_each_array_element_fn(mrb, scene, mrb_intern_lit(mrb, "children"), hiro_game_object_update, 1, argv);
}

void hiro_scene_draw(mrb_state* mrb, mrb_value scene) {
  mrb_funcall(mrb, scene, "draw", 0, NULL);
  hiro_helper_each_array_element_fn(mrb, scene, mrb_intern_lit(mrb, "children"), hiro_game_object_draw, 0, NULL);
}

mrb_value hiro_scene_get_children(mrb_state* mrb, mrb_value self) {
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

void hiro_scene_add_child(mrb_state* mrb, mrb_value self, mrb_value object) {
  mrb_value children;

  // TODO: Refactor to use shared method
  children = hiro_scene_get_children(mrb, self);

  if(!hiro_is_kind_of_game_object(mrb, object)) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not vaild GameObject.", object);
  }

  mrb_ary_push(mrb, children, object);
}

void hiro_scene_each_child_call(mrb_state* mrb, mrb_value self, const char* method_name, mrb_int argc, mrb_value* argv) {
  mrb_value children, object;
  int len, i;

  children = hiro_scene_get_children(mrb, self);
  len = RARRAY_LEN(children);

  for(i = 0; i < len; i++) {
    object = mrb_ary_ref(mrb, children, i);
    if(!mrb_nil_p(object)) {
      mrb_funcall(mrb, object, method_name, argc, argv);
    }
  }
}

mrb_value hiro_scene_mrb_add(mrb_state* mrb, mrb_value self) {
  mrb_value object;

  mrb_get_args(mrb, "o", &object);
  hiro_scene_add_child(mrb, self, object);

  return self;
}

mrb_value hiro_scene_mrb_blob_api(mrb_state* mrb, mrb_value self) {
  return self;
}

void hiro_define_scene(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Scene", mrb->object_class);

  mrb_define_method(mrb, klass, "add", hiro_scene_mrb_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, klass, "update", hiro_scene_mrb_blob_api, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "draw", hiro_scene_mrb_blob_api, MRB_ARGS_NONE());
}
