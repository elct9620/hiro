#include "components/renderer.h"

const struct mrb_data_type hiro_renderer_component_type = { "RendererComponent", hiro_renderer_component_mrb_free };

mrb_value hiro_renderer_component_new(mrb_state* mrb, mrb_int argc, mrb_value* argv) {
  struct RClass* klass;
  klass =  mrb_class_get(mrb, "RendererComponent");

  return mrb_obj_new(mrb, klass, argc, argv);
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

  return self;
}

mrb_value hiro_renderer_component_mrb_draw(mrb_state* mrb, mrb_value self) {
  mrb_value game_object;
  struct hiro_renderer_component* component;
  SDL_Rect distance;
  mrb_int _x, _y;

  game_object = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@game_object"));

  component = DATA_GET_PTR(mrb, self, &hiro_renderer_component_type, struct hiro_renderer_component);
  _x = mrb_fixnum(mrb_funcall(mrb, game_object, "x", 0));
  _y = mrb_fixnum(mrb_funcall(mrb, game_object, "y", 0));

  distance.w = component->width;
  distance.h = component->height;
  distance.x = _x;
  distance.y = _y;

  SDL_RenderCopy(component->renderer, component->texture, NULL, &distance);

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
}
