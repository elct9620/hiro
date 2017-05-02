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

SDL_RendererFlip hiro_sprite_renderer_flip(mrb_int x, mrb_int y) {
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  if(0 > x) { flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL); }
  if(0 > y) { flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL); }
  return flip;
}

struct hiro_vec2 hiro_sprite_renderer_scale(mrb_state* mrb, mrb_value self) {
  mrb_value scale;
  scale = mrb_funcall(mrb, self, "scale", 0, NULL);
  return hiro_sprite_renderer_position(mrb, scale);
}

struct hiro_vec2 hiro_sprite_renderer_size(mrb_state* mrb, mrb_value self) {
  struct hiro_vec2 size;
  size.x = mrb_fixnum(mrb_funcall(mrb, self, "width", 0, NULL));
  size.y = mrb_fixnum(mrb_funcall(mrb, self, "height", 0, NULL));
  return size;
}

struct hiro_vec2 hiro_sprite_renderer_position(mrb_state* mrb, mrb_value self) {
  struct hiro_vec2 position;
  position.x = mrb_fixnum(mrb_funcall(mrb, self, "x", 0, NULL));
  position.y = mrb_fixnum(mrb_funcall(mrb, self, "y", 0, NULL));
  return position;
}

struct hiro_rect hiro_sprite_renderer_bound(mrb_state* mrb, mrb_value self) {
  mrb_value _bound;
  struct hiro_rect bound;

  _bound = r_iv_get("@bound");
  bound.x = mrb_fixnum(mrb_funcall(mrb, _bound, "x", 0, NULL));
  bound.y = mrb_fixnum(mrb_funcall(mrb, _bound, "y", 0, NULL));
  bound.width = mrb_fixnum(mrb_funcall(mrb, _bound, "width", 0, NULL));
  bound.height = mrb_fixnum(mrb_funcall(mrb, _bound, "height", 0, NULL));

  return bound;
}

void hiro_sprite_renderer_draw(struct hiro_sprite_renderer* renderer, struct hiro_vec2 position, struct hiro_vec2 size, struct hiro_vec2 scale) {
  SDL_Rect distance;
  SDL_RendererFlip flip;

  flip = hiro_sprite_renderer_flip(scale.x, scale.y);

  distance.x = position.x;
  distance.y = position.y;
  distance.w = size.x > 0 ? size.x : renderer->width;
  distance.h = size.y > 0 ? size.y : renderer->height;

  SDL_RenderCopyEx(renderer->renderer, renderer->texture, NULL, &distance, 0, NULL, flip);
}

void hiro_sprite_renderer_draw_clip(struct hiro_sprite_renderer* renderer, struct hiro_vec2 position, struct hiro_rect bound, struct hiro_vec2 scale) {
  SDL_Rect distance, clip;
  SDL_RendererFlip flip;

  flip = hiro_sprite_renderer_flip(scale.x, scale.y);

  distance.x = position.x;
  distance.y = position.y;
  distance.w = bound.width;
  distance.h = bound.height;

  clip.x = bound.x;
  clip.y = bound.y;
  clip.w = bound.width;
  clip.h = bound.height;

  SDL_RenderCopyEx(renderer->renderer, renderer->texture, &clip, &distance, 0, NULL, flip);
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
  struct hiro_vec2 size, position, scale;
  struct hiro_rect bound;
  mrb_bool clip;

  size = hiro_sprite_renderer_size(mrb, self);
  scale = hiro_sprite_renderer_scale(mrb, self);
  position = hiro_sprite_renderer_position(mrb, self);
  bound = hiro_sprite_renderer_bound(mrb, self);

  clip = mrb_bool(r_iv_get("@clip"));
  renderer = hiro_sprite_renderer_ptr(mrb, r_iv_get("@data"));

  if(clip) {
    hiro_sprite_renderer_draw_clip(renderer, position, bound, scale);
  } else {
    hiro_sprite_renderer_draw(renderer, position, size, scale);
  }

  return self;
}

void hiro_sprite_renderer_init(mrb_state* mrb, struct RClass* component) {
  struct RClass* renderer;

  renderer = mrb_define_class(mrb, "SpriteRenderer", component);
  mrb_define_method(mrb, renderer, "init", hiro_sprite_renderer_mrb_init, MRB_ARGS_NONE());
  mrb_define_method(mrb, renderer, "draw", hiro_sprite_renderer_mrb_draw, MRB_ARGS_NONE());
}
