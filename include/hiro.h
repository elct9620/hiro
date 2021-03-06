// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

// Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <mruby/hash.h>
#include <mruby/array.h>

// Macros
#define HIRO_INIT(module) hiro_##module##_init(mrb)
#define HIRO_COMP_INIT(name) hiro_##name##_init(mrb, component)

// Hiro
#include "wrapper.h"
#include "helper.h"
#include "hash.h"
#include "object.h"
#include "vector2.h"
#include "rectangle.h"

#include "core.h"
#include "game.h"
#include "config.h"
#include "event.h"

#include "game_object.h"
#include "scene.h"
#include "component.h"
#include "components/sprite_renderer.h"
#include "components/animator.h"
