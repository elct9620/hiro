#include "component.h"

mrb_bool hiro_is_kind_of_component(mrb_state* mrb, mrb_value object) {
  struct RClass* component_class;

  component_class = mrb_class_get(mrb, "Component");

  if(!mrb_obj_is_kind_of(mrb, object, component_class)) {
    return 0;
  }

  return 1;
}

void hiro_component_set_game_object(mrb_state* mrb, mrb_value self, mrb_value game_object) {
  mrb_bool is_game_object;

  is_game_object = hiro_is_kind_of_game_object(mrb, game_object);

  if(!is_game_object) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "%S is not valid GameObject", game_object);
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@game_object"), game_object);
}

void hiro_component_update(mrb_state* mrb, mrb_value self) {
  mrb_funcall(mrb, self, "update", 0, NULL);
}

void hiro_component_draw(mrb_state* mrb, mrb_value self) {
  mrb_funcall(mrb, self, "draw", 0, NULL);
}

void hiro_define_component(mrb_state* mrb) {
  struct RClass* klass;

  klass = mrb_define_class(mrb, "Component", mrb->object_class);
  mrb_define_method(mrb, klass, "update", hiro_helper_mrb_blob_api, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "draw", hiro_helper_mrb_blob_api, MRB_ARGS_NONE());
}
