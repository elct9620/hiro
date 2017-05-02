#include "event.h"

mrb_value hiro_create_event(mrb_state* mrb) {
  struct RClass* event;
  event = mrb_class_get(mrb, "Event");
  return mrb_obj_new(mrb, event, 0, NULL);
}

void hiro_event_emit(mrb_state* mrb, SDL_Event ev) {
  struct RClass* event;
  mrb_value event_class, event_object, type;
  event = mrb_class_get(mrb, "Event");
  event_class = mrb_obj_value(event);
  type = mrb_fixnum_value(ev.type);

  event_object = hiro_create_event(mrb);
  r_hash_set(event_object, "type", type);
  r_hash_set(event_object, "window", mrb_fixnum_value(ev.window.windowID));
  r_hash_set(event_object, "repeat", mrb_bool_value(ev.key.repeat != 0));
  r_hash_set(event_object, "key", mrb_fixnum_value(ev.key.keysym.scancode));
  r_hash_set(event_object, "mod", mrb_fixnum_value(ev.key.keysym.mod));

  mrb_funcall(mrb, event_class, "emit", 2, type, event_object);
}
