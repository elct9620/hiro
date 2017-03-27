// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_HASH_H
#define _HIRO_HASH_H

#include "hiro.h"

#define r_hash_set(self, key, value) mrb_hash_set(mrb, self, mrb_symbol_value(mrb_intern_lit(mrb, key)), value)

#endif
