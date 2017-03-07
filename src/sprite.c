#include "sprite.h"

mrb_value hiro_sprite_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value _path, _position;
  mrb_value vector2_argv[2], renderer_comp_argv[3];
  mrb_int _width, _height;
  mrb_int argc;
  struct RClass* vector2_class;

  argc = mrb_get_args(mrb, "S|oii", &_path, &_position, &_width, &_height);

  if(mrb_nil_p(_position)) {
    vector2_class = mrb_class_get(mrb, "Vector2");
    vector2_argv[0] = mrb_fixnum_value(0);
    vector2_argv[1] = mrb_fixnum_value(0);
    _position = mrb_obj_new(mrb, vector2_class, 2, vector2_argv);
  }

  _width = argc > 1 ? _width : 0;
  _height = argc > 2 ? _height : 0;

  renderer_comp_argv[0] = _path;
  renderer_comp_argv[1] = mrb_fixnum_value(_width);
  renderer_comp_argv[2] = mrb_fixnum_value(_height);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@position"), _position);
  mrb_funcall(mrb, self, "add_component", 1, hiro_renderer_component_new(mrb, 3, renderer_comp_argv));

  return self;
}

void hiro_define_sprite(mrb_state* mrb) {
  struct RClass *klass, *game_object_class;

  game_object_class = mrb_class_get(mrb, "GameObject");
  klass = mrb_define_class(mrb, "Sprite", game_object_class);

  mrb_define_method(mrb, klass, "initialize", hiro_sprite_mrb_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(3));
}
