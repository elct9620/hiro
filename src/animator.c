#include "components/animator.h"

mrb_value hiro_animator_mrb_sprite_size(mrb_state* mrb, mrb_value self) {
  struct RClass* vector2;
  struct hiro_sprite_renderer* _renderer;
  mrb_value renderer;
  mrb_value size;

  vector2 = mrb_class_get(mrb, "Vector2");
  renderer = mrb_funcall(mrb, self, "renderer", 0, NULL);

  size = mrb_obj_new(mrb, vector2, 0, NULL);

  if(!mrb_nil_p(renderer)) {
    _renderer = hiro_sprite_renderer_ptr(mrb, mrb_iv_get(mrb, renderer, mrb_intern_lit(mrb, "@data")));
    mrb_iv_set(mrb, size, mrb_intern_lit(mrb, "@x"), mrb_fixnum_value(_renderer->width));
    mrb_iv_set(mrb, size, mrb_intern_lit(mrb, "@y"), mrb_fixnum_value(_renderer->height));
  }

  return size;
}

void hiro_animator_init(mrb_state* mrb, struct RClass* component) {
  struct RClass* animator;

  animator = mrb_define_class(mrb, "Animator", component);
  mrb_define_method(mrb, animator, "sprite_size", hiro_animator_mrb_sprite_size, MRB_ARGS_NONE());
}
