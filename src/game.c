#include "game.h"

const struct mrb_data_type hiro_game_type = { "Game", hiro_game_mrb_free };

mrb_value hiro_game_mrb_initialize(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;

  game = (struct hiro_game*)DATA_PTR(self);
  if(game != NULL) {
    hiro_game_mrb_free(mrb, game);
  }
  mrb_data_init(self, NULL, &hiro_game_type);

  // TODO: Implement full `hiro_game` creation method
  game = (struct hiro_game*)mrb_malloc(mrb, sizeof(struct hiro_game));
  game->stop = 0;

  mrb_data_init(self, game, &hiro_game_type);

  return self;
}

mrb_value hiro_game_mrb_start(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;
  mrb_value cb;
  SDL_Event ev;

  game = DATA_GET_PTR(mrb, self, &hiro_game_type, struct hiro_game);

  mrb_get_args(mrb, "|&", &cb);

  while(!game->stop) {
    // TODO: Implement Game Instance related methods
    while(SDL_PollEvent(&ev)) {
      hiro_event_call(mrb, ev);
    }

    mrb_funcall(mrb, self, "update", 0);
  }

  return self;
}

mrb_value hiro_game_mrb_update(mrb_state* mrb, mrb_value self) {
  return self;
}

mrb_value hiro_game_mrb_stop_bang(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;

  game = DATA_GET_PTR(mrb, self, &hiro_game_type, struct hiro_game);
  game->stop = 1;

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
  mrb_define_method(mrb, klass, "update", hiro_game_mrb_update, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "start", hiro_game_mrb_start, MRB_ARGS_BLOCK());
  mrb_define_method(mrb, klass, "stop!", hiro_game_mrb_stop_bang, MRB_ARGS_NONE());
}
