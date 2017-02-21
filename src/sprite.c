#include "sprite.h"

const struct mrb_data_type hiro_sprite_type = { "Sprite", hiro_sprite_mrb_free };

mrb_value hiro_sprite_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value _renderer, _path;
  mrb_int _x, _y, _width, _height;
  mrb_int argc;

  const char* path;
  struct hiro_sprite *sprite;
  struct hiro_renderer *renderer;

  sprite = (struct hiro_sprite*)DATA_PTR(self);
  if(sprite != NULL) {
    hiro_sprite_mrb_free(mrb, sprite);
  }
  mrb_data_init(self, NULL, &hiro_sprite_type);


  argc = mrb_get_args(mrb, "oS|iiii", &_renderer, &_path, &_x, &_y, &_width, &_height);

  renderer = DATA_GET_PTR(mrb, _renderer, &hiro_renderer_type, struct hiro_renderer);

  path = mrb_str_to_cstr(mrb, _path);

  _x = argc > 2 ? _x : 0;
  _y = argc > 3 ? _y : 0;
  _width = argc > 4 ? _width : 0;
  _height = argc > 5 ? _height : 0;

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@x"), mrb_fixnum_value(_x));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@y"), mrb_fixnum_value(_y));

  sprite = hiro_sprite_create(mrb, renderer->renderer, path, _width, _height);
  mrb_data_init(self, sprite, &hiro_sprite_type);

  return self;
}

mrb_value hiro_sprite_mrb_draw(mrb_state* mrb, mrb_value self) {
  struct hiro_sprite* sprite;
  SDL_Rect distance;
  mrb_value _x, _y;

  sprite = DATA_GET_PTR(mrb, self, &hiro_sprite_type, struct hiro_sprite);
  _x = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@x"));
  _y = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@y"));

  // TODO: Add position arguments
  distance.w = sprite->width;
  distance.h = sprite->height;
  distance.x = mrb_fixnum(_x);;
  distance.y = mrb_fixnum(_y);

  SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, &distance);

  return self;
}

void hiro_sprite_mrb_free(mrb_state* mrb, void* ptr) {
  struct hiro_sprite* sprite;

  sprite = (struct hiro_sprite*)ptr;
  if(sprite) {
    SDL_DestroyTexture(sprite->texture);
  }

  mrb_free(mrb, ptr);
}

struct hiro_sprite* hiro_sprite_create(mrb_state* mrb, SDL_Renderer *renderer, const char* path, int width, int height) {
  struct hiro_sprite* sprite;
  SDL_Surface* surface;

  surface = IMG_Load(path);
  if(surface == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Load %s failed!", path);
  }

  sprite = (struct hiro_sprite*)mrb_malloc(mrb, sizeof(struct hiro_sprite));
  sprite->path = path;
  sprite->width = width > 0 ? width : surface->w;
  sprite->height = height > 0 ? height : surface->h;
  sprite->texture = SDL_CreateTextureFromSurface(renderer, surface);
  sprite->renderer = renderer;

  SDL_FreeSurface(surface);

  return sprite;
}

void hiro_define_sprite(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Sprite", mrb->object_class);

  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_sprite_mrb_initialize, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(4));
  mrb_define_method(mrb, klass, "draw", hiro_sprite_mrb_draw, MRB_ARGS_NONE());
}
