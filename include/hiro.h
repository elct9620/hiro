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
#include <mruby/array.h>

/**
 * Hiro Framework
 */

#include "core.h"
#include "helper.h"
#include "config.h"
#include "window.h"
#include "renderer.h"
#include "event.h"
#include "game.h"
#include "scene.h"

// Component
#include "component.h"
#include "components/renderer.h"

// Game Object
#include "game_object.h"
#include "sprite.h"
