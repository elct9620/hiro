#include "game_object.h"

mrb_bool hiro_is_game_object(mrb_state* mrb, mrb_value object) {
  struct RClass* game_object;

  game_object = mrb_class_get(mrb, "GameObject");
  if(!mrb_obj_is_kind_of(mrb, object, game_object)) {
    return 0;
  }

  return 1;
}

void hiro_game_object_update(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  HIRO_EACH_FN(self, "@components", hiro_component_update, argc, argv);
  HIRO_EACH_FN(self, "@children", hiro_game_object_update, argc, argv);
  mrb_funcall_argv(mrb, self, mrb_intern_lit(mrb, "update"), argc, argv);
}

void hiro_game_object_draw(mrb_state* mrb, mrb_value self, mrb_int argc, mrb_value* argv) {
  HIRO_EACH_FN(self, "@components", hiro_component_draw, argc, argv);
  HIRO_EACH_FN(self, "@children", hiro_game_object_draw, argc, argv);
  mrb_funcall(mrb, self, "draw", argc, argv);
}

mrb_value hiro_game_object_mrb_add(mrb_state* mrb, mrb_value self) {
  mrb_value children, child;

  children = r_iv_get("@children");
  mrb_get_args(mrb, "o", &child);
  if(!hiro_is_game_object(mrb, child)) {
    return mrb_false_value();
  }

  // TODO: If parent present, remove self from old parent.
  mrb_ary_push(mrb, children, child);
  mrb_iv_set(mrb, child, mrb_intern_lit(mrb, "@parent"), self);

  return mrb_true_value();
}

mrb_value hiro_game_object_mrb_use(mrb_state* mrb, mrb_value self) {
  mrb_value components, component;

  components = r_iv_get("@components");
  mrb_get_args(mrb, "o", &component);
  if(!hiro_is_component(mrb, component)) {
    return mrb_false_value();
  }

  // TODO: If game object present, remove self from old game object
  mrb_ary_push(mrb, components, component);
  mrb_iv_set(mrb, component, mrb_intern_lit(mrb, "@game_object"), self);

  return mrb_true_value();
}


void hiro_game_object_init(mrb_state* mrb) {
  struct RClass* game_object;

  game_object = mrb_define_class(mrb, "GameObject", mrb->object_class);
  mrb_define_method(mrb, game_object, "add", hiro_game_object_mrb_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, game_object, "use", hiro_game_object_mrb_use, MRB_ARGS_REQ(1));
}
