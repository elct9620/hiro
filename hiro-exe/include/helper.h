#ifndef _HIRO_HELPER_H
#define _HIRO_HELPER_H

#include "hiro.h"

HIRO_API mrb_value hiro_helper_get_hash_attribute(mrb_state*, mrb_value, mrb_sym);
HIRO_API mrb_value hiro_helper_get_array_attribute(mrb_state*, mrb_value, mrb_sym);

HIRO_API void hiro_helper_each_array_element_do(mrb_state*, mrb_value, mrb_sym, const char*, mrb_int, mrb_value*);
// TODO: Define callback function pointer
HIRO_API void hiro_helper_each_array_element_fn(mrb_state*, mrb_value, mrb_sym, void (*fn)(mrb_state*,mrb_value,mrb_int,mrb_value*), mrb_int, mrb_value*);

HIRO_API mrb_value hiro_helper_mrb_blob_api(mrb_state*, mrb_value);

#endif
