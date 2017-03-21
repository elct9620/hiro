#ifndef _HIRO_CORE_H
#define _HIRO_CORE_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>

// TODO: Add support for Windows
#define HIRO_API extern

HIRO_API void hiro_set_instance(mrb_state*, mrb_value);

mrb_value hiro_mrb_set_game_class(mrb_state*, mrb_value);
mrb_value hiro_mrb_quit_bang(mrb_state*, mrb_value);

#endif
