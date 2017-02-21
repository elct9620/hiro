// Builtin API
#include <stdio.h>

// Common Macros
#define HIRO_API extern

// Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <mruby/hash.h>

// Hiro Framework
#include "window.h"
#include "renderer.h"
#include "event.h"
#include "sprite.h"
#include "game.h"
