#include "components/sprite_renderer.h"

mrb_value hiro_sprite_renderer_object(mrb_state* mrb, struct hiro_sprite_renderer *ptr) {
  return hiro_data_wrap(sprite_renderer, ptr);
}

struct hiro_sprite_renderer* hiro_sprite_renderer_ptr(mrb_state* mrb, mrb_value self) {
  struct hiro_sprite_renderer *renderer;
  hiro_data_get(self, sprite_renderer, renderer);
  return renderer;
}

struct hiro_sprite_renderer* hiro_create_sprite_renderer(mrb_state* mrb, SDL_Renderer* main_renderer, const char* path) {
  struct hiro_sprite_renderer* renderer;
  SDL_Surface* surface;

  surface = IMG_Load(path);
  if(surface == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Load %s failed!", path);
  }

  renderer = (struct hiro_sprite_renderer*)mrb_malloc(mrb, sizeof(struct hiro_sprite_renderer));
  renderer->width = surface->w;
  renderer->height = surface->h;
  renderer->texture = SDL_CreateTextureFromSurface(main_renderer, surface);
  renderer->renderer = main_renderer;

  SDL_FreeSurface(surface);

  return renderer;
}

mrb_value hiro_sprite_renderer_mrb_init(mrb_state* mrb, mrb_value self) {
  struct hiro_game* game;
  struct hiro_sprite_renderer* renderer;

  // TODO: Accept custom renderer or auto split by renderer
  game = HIRO_GAME_PTR();
  renderer = hiro_create_sprite_renderer(mrb, game->renderer, mrb_str_to_cstr(mrb, r_iv_get("@path")));
  r_iv_set("@data", hiro_sprite_renderer_object(mrb, renderer));

  return self;
}

mrb_value hiro_sprite_renderer_mrb_draw(mrb_state* mrb, mrb_value self) {
  struct hiro_sprite_renderer* renderer;
  SDL_Rect distance;
  mrb_int width, height;

  width = mrb_fixnum(mrb_funcall(mrb, self, "width", 0, NULL));
  height = mrb_fixnum(mrb_funcall(mrb, self, "height", 0, NULL));

  renderer = hiro_sprite_renderer_ptr(mrb, r_iv_get("@data"));
  distance.x = mrb_fixnum(mrb_funcall(mrb, self, "x", 0, NULL));
  distance.y = mrb_fixnum(mrb_funcall(mrb, self, "y", 0, NULL));
  distance.w = width > 0 ? width: renderer->width;
  distance.h = height > 0 ? height : renderer->height;

  SDL_RenderCopy(renderer->renderer, renderer->texture, NULL, &distance);

  return self;
}


void hiro_sprite_renderer_init(mrb_state* mrb, struct RClass* component) {
  struct RClass* renderer;

  renderer = mrb_define_class(mrb, "SpriteRenderer", component);
  mrb_define_method(mrb, renderer, "init", hiro_sprite_renderer_mrb_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, renderer, "draw", hiro_sprite_renderer_mrb_draw, MRB_ARGS_NONE());
}
