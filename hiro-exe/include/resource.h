#ifndef _HIRO_RESOURCE_H
#define _HIRO_RESOURCE_H

#include "hiro.h"

void hiro_resource_mrb_free(mrb_state*, void*);

struct hiro_resource {
  const char* path;
  int         references;
};

HIRO_API const struct mrb_data_type hiro_resource_type;

void hiro_define_resource(mrb_state*);

#endif
