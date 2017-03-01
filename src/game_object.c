#include "game_object.h"

void hiro_define_game_object(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "GameObject", mrb->object_class);
}
