// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_CONFIG_H
#define _HIRO_CONFIG_H

#include "hiro.h"

#define hiro_config_get(name) hiro_config_mrb_get(mrb, name)

mrb_value hiro_config_mrb_get(mrb_state*, const char*);

#endif
