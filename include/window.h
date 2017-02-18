#ifndef _HIRO_WINDOW_H
#define _HIRO_WINDOW_H

#include "hiro.h"

static const char* HIRO_DEFAULT_WINDOW_NAME = "Hiro Framework";
static int HIRO_DEFAULT_WINDOW_WIDTH = 1080;
static int HIRO_DEFAULT_WINDOW_HEIGHT = 720;
static int HIRO_DEFAULT_WINDOW_FLAGS = SDL_WINDOW_SHOWN;

mrb_value hiro_window_mrb_initialize(mrb_state*, mrb_value);
void hiro_window_mrb_free(mrb_state*, void*);

struct hiro_window {
  const char* name;
  int         width;
  int         height;
  int         flags;
  SDL_Window* win;
};

HIRO_API const struct mrb_data_type hiro_window_type;

struct hiro_window* hiro_window_create(mrb_state*, const char* name, int width, int height, int flags);

void hiro_define_window(mrb_state*);

#endif
