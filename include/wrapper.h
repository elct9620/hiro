// Hiro Framework - Copyright 2017 Zheng Xian Qiu.

#ifndef _HIRO_WRAPPER_H
#define _HIRO_WRAPPER_H

#define r_iv_set(name, value) mrb_iv_set(mrb, self, mrb_intern_lit(mrb, name), value)
#define r_iv_get(name) mrb_iv_get(mrb, self, mrb_intern_lit(mrb, name))

#endif
