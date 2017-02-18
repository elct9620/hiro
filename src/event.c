#include "hiro.h"

mrb_bool hiro_event_has_events(mrb_state* mrb) {
  struct RClass* mod = mrb_module_get(mrb, "Event");
  mrb_sym cv_name = mrb_intern_cstr(mrb, "events");
  return mrb_mod_cv_defined(mrb, mod, cv_name);
}

mrb_value hiro_event_get_events(mrb_state* mrb) {
  if(!hiro_event_has_events(mrb)) {
    hiro_event_init_events(mrb);
  }

  struct RClass* mod = mrb_module_get(mrb, "Event");
  mrb_sym cv_name = mrb_intern_cstr(mrb, "events");
  return mrb_mod_cv_get(mrb, mod, cv_name);
}

void hiro_event_init_events(mrb_state* mrb) {
  struct RClass* mod = mrb_module_get(mrb, "Event");
  mrb_sym cv_name = mrb_intern_cstr(mrb, "events");
  mrb_value events = mrb_hash_new(mrb);
  mrb_mod_cv_set(mrb, mod, cv_name, events);
}

void hiro_event_register(mrb_state* mrb, mrb_int event, mrb_value cb) {
  mrb_value events = hiro_event_get_events(mrb);
  mrb_hash_set(mrb, events, mrb_fixnum_value(event), cb);
}

void hiro_event_call(mrb_state* mrb, mrb_int event) {
  mrb_value events = hiro_event_get_events(mrb);
  mrb_value cb = mrb_hash_get(mrb, events, mrb_fixnum_value(event));

  if(mrb_nil_p(cb)) {
    return;
  }

  mrb_yield_argv(mrb, cb, 0, NULL);
}

mrb_value hiro_event_mrb_poll(mrb_state* mrb, mrb_value self) {

  SDL_Event ev;
  while(SDL_PollEvent(&ev)) {
    hiro_event_call(mrb, ev.type);
  }

  return self;
}

mrb_value hiro_event_mrb_on(mrb_state* mrb, mrb_value self) {

  mrb_int event;
  mrb_value callback;

  mrb_get_args(mrb, "i&", &event, &callback);
  hiro_event_register(mrb, event, callback);

  return self;
}

void hiro_define_event(mrb_state* mrb) {
  struct RClass* mod = mrb_define_module(mrb, "Event");

  mrb_define_class_method(mrb, mod, "poll", hiro_event_mrb_poll, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, mod, "on", hiro_event_mrb_on, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
}
