#include "components/renderer.h"

const struct mrb_data_type hiro_renderer_component_type = { "RendererComponent", hiro_renderer_component_mrb_free };

mrb_value hiro_renderer_component_new(mrb_state* mrb, mrb_int argc, mrb_value* argv) {
  struct RClass* klass;
  klass =  mrb_class_get(mrb, "RendererComponent");

  return mrb_obj_new(mrb, klass, argc, argv);
}

void hiro_renderer_component_setup_animation(mrb_state* mrb, mrb_value self) {
  struct hiro_renderer_component *component;
  mrb_int _width, _height;

  component = DATA_GET_PTR(mrb, self, &hiro_renderer_component_type, struct hiro_renderer_component);
  _width = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@width")));
  _height = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@height")));

  component->xFrames = ceil(component->width / _width);
  component->yFrames = ceil(component->height / _height);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@frames"), mrb_fixnum_value(component->xFrames * component->yFrames));
}

mrb_value hiro_renderer_component_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value _path;
  mrb_bool has_width, has_height;
  mrb_int _width, _height;
  mrb_int argc;

  const char* path;
  struct hiro_renderer_component *component;

  component = (struct hiro_renderer_component*)DATA_PTR(self);
  if(component != NULL) {
    hiro_renderer_component_mrb_free(mrb, component);
  }
  mrb_data_init(self, NULL, &hiro_renderer_component_type);

  argc = mrb_get_args(mrb, "S|ii", &_path, &_width, &_height);

  path = mrb_str_to_cstr(mrb, _path);
  has_width = argc > 1 && _width > 0;
  has_height = argc > 2 && _width > 0;

  component = hiro_renderer_component_create(mrb, hiro_default_renderer(mrb), path);
  mrb_data_init(self, component, &hiro_renderer_component_type);

  _width = has_width ? _width : component->width;
  _height = has_height ? _height : component->height;

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@width"), mrb_fixnum_value(_width));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@height"), mrb_fixnum_value(_height));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@animate"), mrb_false_value());
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@frame"), mrb_fixnum_value(0));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@scale"), hiro_vector2_value(mrb, 0, 0));

  hiro_component_set_name(mrb, self, "renderer");

  return self;
}

mrb_value hiro_renderer_component_mrb_draw(mrb_state* mrb, mrb_value self) {
  mrb_value game_object, is_animate, scale;
  struct hiro_renderer_component* component;
  SDL_Rect distance, clip;
  SDL_RendererFlip flip;
  mrb_int _x, _y, _clip_y, _frame, _scale_x, _scale_y;

  game_object = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@game_object"));

  component = DATA_GET_PTR(mrb, self, &hiro_renderer_component_type, struct hiro_renderer_component);
  _x = mrb_fixnum(mrb_funcall(mrb, game_object, "x", 0));
  _y = mrb_fixnum(mrb_funcall(mrb, game_object, "y", 0));
  _frame = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@frame")));

  flip = SDL_FLIP_NONE;

  scale = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@scale"));
  _scale_x = mrb_fixnum(mrb_funcall(mrb, scale, "x", 0));
  _scale_y = mrb_fixnum(mrb_funcall(mrb, scale, "y", 0));

  if(0 > _scale_x) { flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL); }
  if(0 > _scale_y) { flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL); }

  distance.w = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@width")));
  distance.h = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@height")));
  distance.x = _x;
  distance.y = _y;

  is_animate = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@animate"));

  if(mrb_bool(is_animate)) {
    _clip_y = ceil((float)(_frame+1) / component->xFrames);

    clip.w = distance.w;
    clip.h = distance.h;
    clip.x = _frame % component->xFrames * clip.w;
    clip.y = (_clip_y - 1) * clip.h;
    SDL_RenderCopyEx(component->renderer, component->texture, &clip, &distance, 0, NULL, flip);
  } else {
    SDL_RenderCopyEx(component->renderer, component->texture, NULL, &distance, 0, NULL, flip);
  }

  return self;
}

mrb_value hiro_renderer_component_mrb_set_animate(mrb_state* mrb, mrb_value self) {
  mrb_sym attr = mrb_intern_lit(mrb, "@animate");
  mrb_bool enabled;

  mrb_get_args(mrb, "b", &enabled);

  if(enabled) {
    hiro_renderer_component_setup_animation(mrb, self);
    mrb_iv_set(mrb, self, attr, mrb_true_value());
  } else {
    mrb_iv_set(mrb, self, attr, mrb_false_value());
  }

  return self;
}

void hiro_renderer_component_mrb_free(mrb_state* mrb, void* ptr) {
  struct hiro_renderer_component* component;

  component = (struct hiro_renderer_component*)ptr;
  if(component) {
    SDL_DestroyTexture(component->texture);
  }

  mrb_free(mrb, ptr);
}

struct hiro_renderer_component* hiro_renderer_component_create(mrb_state* mrb, SDL_Renderer *renderer, const char* path) {
  struct hiro_renderer_component* component;
  SDL_Surface* surface;

  surface = IMG_Load(path);
  if(surface == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Load %s failed!", path);
  }

  component = (struct hiro_renderer_component*)mrb_malloc(mrb, sizeof(struct hiro_renderer_component));
  component->path = path;
  component->width = surface->w;
  component->height = surface->h;
  component->texture = SDL_CreateTextureFromSurface(renderer, surface);
  component->renderer = renderer;

  SDL_FreeSurface(surface);

  return component;
}

void hiro_define_renderer_component(mrb_state* mrb, struct RClass* component_class) {
  struct RClass* klass;

  klass = mrb_define_class(mrb, "RendererComponent", component_class);
  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_renderer_component_mrb_initialize, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(2));
  mrb_define_method(mrb, klass, "draw", hiro_renderer_component_mrb_draw, MRB_ARGS_NONE());
  mrb_define_method(mrb, klass, "animate=", hiro_renderer_component_mrb_set_animate, MRB_ARGS_REQ(1));
}
