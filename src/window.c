#include "window.h"

const struct mrb_data_type hiro_window_type = { "Window", hiro_window_mrb_free };

mrb_value hiro_window_mrb_initialize(mrb_state* mrb, mrb_value self) {
  mrb_value _name;
  mrb_int _width, _height;
  const char* name;
  int argc;
  struct hiro_window *win;

  win = (struct hiro_window*)DATA_PTR(self);
  if(win) {
    hiro_window_mrb_free(mrb, win);
  }
  mrb_data_init(self, NULL, &hiro_window_type);

  argc = mrb_get_args(mrb, "|Sii", &_name, &_width, &_height);

  name = argc > 0 ? mrb_str_to_cstr(mrb, _name) : HIRO_DEFAULT_WINDOW_NAME;
  _width  = argc > 1 ? _width : HIRO_DEFAULT_WINDOW_WIDTH;
  _height = argc > 2 ? _height : HIRO_DEFAULT_WINDOW_HEIGHT;

  // TODO: Support custom SDL window flags
  win = hiro_window_create(mrb, name, _width, _height, HIRO_DEFAULT_WINDOW_FLAGS);

  mrb_data_init(self, win, &hiro_window_type);
  return self;
}

void hiro_window_mrb_free(mrb_state* mrb, void* ptr) {
  struct hiro_window *win;

  win = (struct hiro_window*)ptr;
  if(win) {
    SDL_DestroyWindow(win->win);
  }

  mrb_free(mrb, win);
}

struct hiro_window* hiro_window_create(mrb_state* mrb, const char* name, int width, int height, int flags) {
  struct hiro_window* win;

  SDL_Window* _win;

  _win = SDL_CreateWindow(name, 0, 0, width, height, flags);
  if(_win == NULL) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "Window initialize failed!");
    SDL_DestroyWindow(_win);
    return NULL;
  }

  win = (struct hiro_window*)mrb_malloc(mrb, sizeof(struct hiro_window));
  win->name = name;
  win->width = width;
  win->height = height;
  win->flags = flags;
  win->win = _win;

  return win;
}

void hiro_define_window(mrb_state* mrb) {
  struct RClass* klass;
  klass = mrb_define_class(mrb, "Window", mrb->object_class);
  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "initialize", hiro_window_mrb_initialize, MRB_ARGS_OPT(3));
}
