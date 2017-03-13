#include "resource.h"

const struct mrb_data_type hiro_resource_type = { "Resource", hiro_resource_mrb_free };

void hiro_resource_mrb_free(mrb_state* mrb, void* ptr) {
  struct hiro_resource* resource;

  resource = (struct hiro_resource*)ptr;
  if(resource) {
    // TODO: Release resources
  }
  mrb_free(mrb, ptr);
}

void hiro_define_resource(mrb_state* mrb) {
  struct RClass* klass;

  klass = mrb_define_class(mrb, "Resource", mrb->object_class);
}
