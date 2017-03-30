// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_HELPER_H
#define _HIRO_HELPER_H

#include "hiro.h"

typedef void (*hiro_fn)(mrb_state*, mrb_value, mrb_int, mrb_value*);

#define HIRO_EACH_FN(self, name, cb, argc, argv) hiro_helper_each_array_element_fn(mrb, self, mrb_intern_lit(mrb, name), cb, argc, argv)
#define HIRO_EACH_HASH_FN(self, name, cb, argc, argv) hiro_helper_each_hash_element_fn(mrb, self, mrb_intern_lit(mrb, name), cb, argc, argv)

void hiro_helper_each_array_element_fn(mrb_state*, mrb_value, mrb_sym, hiro_fn, mrb_int, mrb_value*);
void hiro_helper_each_hash_element_fn(mrb_state*, mrb_value, mrb_sym, hiro_fn, mrb_int, mrb_value*);

#endif
