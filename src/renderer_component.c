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

  _width = argc > 1 ? _width : 0;
  _height = argc > 2 ? _height : 0;

  component = hiro_renderer_component_create(mrb, hiro_default_renderer(mrb), path, _width, _height);
  mrb_data_init(self, component, &hiro_renderer_component_type);

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@width"), mrb_fixnum_value(component->width));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@height"), mrb_fixnum_value(component->height));
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@animate"), mrb_false_value());
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@frame"), mrb_fixnum_value(0));

  hiro_component_set_name(mrb, self, "renderer");

  return self;
}

mrb_value hiro_renderer_component_mrb_draw(mrb_state* mrb, mrb_value self) {
  mrb_value game_object, is_animate;
  struct hiro_renderer_component* component;
  SDL_Rect distance, clip;
  mrb_int _x, _y, _frame;

  game_object = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@game_object"));

  component = DATA_GET_PTR(mrb, self, &hiro_renderer_component_type, struct hiro_renderer_component);
  _x = mrb_fixnum(mrb_funcall(mrb, game_object, "x", 0));
  _y = mrb_fixnum(mrb_funcall(mrb, game_object, "y", 0));
  _frame = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@frame")));

  distance.w = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@width")));
  distance.h = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@height")));
  distance.x = _x;
  distance.y = _y;

  is_animate = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@animate"));

  if(mrb_bool(is_animate)) {
    clip.w = distance.w;
    clip.h = distance.h;
    clip.x = _frame % (component->yFrames - 1) * clip.w;
    clip.y = _frame / component->xFrames * clip.h;
    SDL_RenderCopy(component->renderer, component->texture, &clip, &distance);
  } else {
    SDL_RenderCopy(component->renderer, component->texture, NULL, &distance);
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

struct hiro_renderer_component* hiro_renderer_component_create(mrb_state* mrb, SDL_Renderer *renderer, const char* path, int width, int height) {
  struct hiro_renderer_component* component;
  SDL_Surface* surface;

  surface = IMG_Load(path);
  if(surface == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Load %s failed!", path);
  }

  component = (struct hiro_renderer_component*)mrb_malloc(mrb, sizeof(struct hiro_renderer_component));
  component->path = path;
  component->width = width > 0 ? width : surface->w;
  component->height = height > 0 ? height : surface->h;
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
