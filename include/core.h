// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

#ifndef _HIRO_CORE_H
#define _HIRO_CORE_H

#include "hiro.h"

mrb_value hiro_core_mrb_start(mrb_state*, mrb_value);

void hiro_core_init(mrb_state*);

#endif
