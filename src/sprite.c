#include "sprite.h"

const struct mrb_data_type hiro_sprite_type = { "Sprite", hiro_sprite_mrb_free };

mrb_value hiro_sprite_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value _path, _position;
  mrb_int _width, _height;
  mrb_int argc;
  struct RClass* vector2_class;

  const char* path;
  struct hiro_sprite *sprite;

  sprite = (struct hiro_sprite*)DATA_PTR(self);
  if(sprite != NULL) {
    hiro_sprite_mrb_free(mrb, sprite);
  }
  mrb_data_init(self, NULL, &hiro_sprite_type);


  argc = mrb_get_args(mrb, "S|oii", &_path, &_position, &_width, &_height);

  path = mrb_str_to_cstr(mrb, _path);

  _width = argc > 2 ? _width : 0;
  _height = argc > 3 ? _height : 0;

  if(mrb_nil_p(_position)) {
    vector2_class = mrb_class_get(mrb, "Vector2");
    _position = mrb_obj_new(mrb, vector2_class, 0, NULL);
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@position"), _position);

  sprite = hiro_sprite_create(mrb, hiro_default_renderer(mrb), path, _width, _height);
  mrb_data_init(self, sprite, &hiro_sprite_type);

  return self;
}

mrb_value hiro_sprite_mrb_draw(mrb_state* mrb, mrb_value self) {
  struct hiro_sprite* sprite;
  SDL_Rect distance;
  mrb_int _x, _y;

  // TODO: Use `super` instead
  hiro_helper_each_array_element_do(mrb, self, mrb_intern_lit(mrb, "children"), "draw", 0, NULL);

  sprite = DATA_GET_PTR(mrb, self, &hiro_sprite_type, struct hiro_sprite);
  _x = mrb_fixnum(mrb_funcall(mrb, self, "x", 0));
  _y = mrb_fixnum(mrb_funcall(mrb, self, "y", 0));

  distance.w = sprite->width;
  distance.h = sprite->height;
  distance.x = _x;
  distance.y = _y;

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
  struct RClass *klass, *game_object_class;

  game_object_class = mrb_class_get(mrb, "GameObject");
  klass = mrb_define_class(mrb, "Sprite", game_object_class);

  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_sprite_mrb_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(3));
  mrb_define_method(mrb, klass, "draw", hiro_sprite_mrb_draw, MRB_ARGS_NONE());
}
