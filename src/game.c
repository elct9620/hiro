#include "game.h"

const struct mrb_data_type hiro_game_type = { "Game", hiro_game_mrb_free };

mrb_value hiro_game_get_current_scene(mrb_state* mrb, mrb_value self) {
  // TODO: Add some protect method
  return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "current_scene"));
}

mrb_value hiro_game_mrb_initialize(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;
  struct RClass* default_scene;
  mrb_value window, renderer, current_scene;

  game = (struct hiro_game*)DATA_PTR(self);
  if(game != NULL) {
    hiro_game_mrb_free(mrb, game);
  }
  mrb_data_init(self, NULL, &hiro_game_type);

  window = hiro_game_create_default_window(mrb);
  renderer = hiro_game_create_default_renderer(mrb, window);
  default_scene = mrb_class_ptr(hiro_config_get(mrb, mrb_intern_lit(mrb, "default_scene")));

  mrb_gc_register(mrb, window);
  mrb_gc_register(mrb, renderer);

  // TODO: Implement full `hiro_game` creation method
  game = (struct hiro_game*)mrb_malloc(mrb, sizeof(struct hiro_game));
  game->stop = 0;
  game->window = window;
  game->renderer = renderer;

  mrb_data_init(self, game, &hiro_game_type);

  hiro_set_instance(mrb, self);

  current_scene = mrb_obj_new(mrb, default_scene, 0, NULL);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "current_scene"), current_scene);

  return self;
}

mrb_value hiro_game_mrb_start(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;
  mrb_value cb;
  SDL_Event ev;

  SDL_Renderer* renderer;

  game = DATA_GET_PTR(mrb, self, &hiro_game_type, struct hiro_game);
  renderer = hiro_game_default_renderer(mrb, self);

  mrb_get_args(mrb, "|&", &cb);

  while(!game->stop) {
    // TODO: Implement Game Instance related methods
    while(SDL_PollEvent(&ev)) {
      hiro_event_call(mrb, ev);
    }

    mrb_funcall(mrb, self, "update", 0);

    // TODO: Split render and actions controller
    SDL_RenderClear(renderer);
    mrb_funcall(mrb, self, "draw", 0);
    SDL_RenderPresent(renderer);
  }

  return self;
}

mrb_value hiro_game_mrb_draw(mrb_state* mrb, mrb_value self) {
  mrb_value current_scene;
  current_scene = hiro_game_get_current_scene(mrb, self);
  mrb_funcall(mrb, current_scene, "draw", 0);
  return self;
}

mrb_value hiro_game_mrb_update(mrb_state* mrb, mrb_value self) {
  mrb_value current_scene;
  current_scene = hiro_game_get_current_scene(mrb, self);
  mrb_funcall(mrb, current_scene, "update", 0);
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
    // mrb_gc_unregister(mrb, game->window);
    // mrb_gc_unregister(mrb, game->renderer);
  }

  mrb_free(mrb, ptr);
}

mrb_value hiro_game_create_default_window(mrb_state* mrb) {
  mrb_value args[3];

  struct RClass* klass = mrb_class_get(mrb, "Window");

  args[0] = hiro_config_get(mrb, mrb_intern_lit(mrb, "name"));
  args[1] = hiro_config_get(mrb, mrb_intern_lit(mrb, "width"));
  args[2] = hiro_config_get(mrb, mrb_intern_lit(mrb, "height"));

  return mrb_obj_new(mrb, klass, 3, args);
}

mrb_value hiro_game_create_default_renderer(mrb_state* mrb, mrb_value window) {
  mrb_value args[1];
  args[0] = window;

  struct RClass* klass = mrb_class_get(mrb, "Renderer");
  return mrb_obj_new(mrb, klass, 1, args);
}

SDL_Renderer* hiro_game_default_renderer(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;
  game = DATA_GET_PTR(mrb, self, &hiro_game_type, struct hiro_game);
  return hiro_renderer_get_ptr(mrb, game->renderer);
}

void hiro_define_game(mrb_state *mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Game", mrb->object_class);

  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_game_mrb_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "update", hiro_game_mrb_update, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "draw", hiro_game_mrb_draw, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "start", hiro_game_mrb_start, MRB_ARGS_BLOCK());
  mrb_define_method(mrb, klass, "stop!", hiro_game_mrb_stop_bang, MRB_ARGS_NONE());
}
