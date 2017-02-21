#include "game.h"

const struct mrb_data_type hiro_game_type = { "Game", hiro_game_mrb_free };

mrb_value hiro_game_mrb_initialize(mrb_state* mrb, mrb_value self) {
  return self;
}

void hiro_game_mrb_free(mrb_state* mrb, void *ptr) {
  struct hiro_game* game;

  game = (struct hiro_game*)ptr;
  if(game) {
    // TODO: Release game related pointer
  }

  mrb_free(mrb, ptr);
}

void hiro_define_game(mrb_state *mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Game", mrb->object_class);

  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_game_mrb_initialize, MRB_ARGS_NONE());
}
