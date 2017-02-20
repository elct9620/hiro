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

mrb_value hiro_event_to_mrb_value(mrb_state* mrb, SDL_Event event) {
  switch(event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      return hiro_event_set_keyboard_data(mrb, event);
    break;
  }

  return hiro_event_new_data(mrb);
}

mrb_value hiro_event_new_data(mrb_state* mrb) {
  struct RClass* mod = mrb_module_get(mrb, "Event");
  struct RClass* klass = mrb_class_get_under(mrb, mod, "Data");
  return mrb_obj_new(mrb, klass, 0, NULL);
}

mrb_value hiro_event_set_keyboard_data(mrb_state* mrb, SDL_Event event) {
  mrb_value data = hiro_event_new_data(mrb);
  const char *type, *state;

  type = event.key.type == SDL_KEYDOWN ? "keydown" : (event.key.type == SDL_KEYUP ? "keyup" : "unknown");
  state = event.key.state == SDL_PRESSED ? "pressed" : (event.key.state == SDL_RELEASED ? "released" : "");

  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "type")), mrb_symbol_value(mrb_intern_cstr(mrb, type)));
  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "window")), mrb_fixnum_value(event.key.windowID));
  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "state")), mrb_symbol_value(mrb_intern_cstr(mrb, state)));
  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "repeat")), mrb_bool_value(event.key.repeat != 0));
  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "key")), mrb_fixnum_value(event.key.keysym.scancode));
  mrb_hash_set(mrb, data, mrb_symbol_value(mrb_intern_lit(mrb, "mod")), mrb_fixnum_value(event.key.keysym.mod));

  return data;
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

void hiro_event_call(mrb_state* mrb, SDL_Event event) {
  mrb_value events = hiro_event_get_events(mrb);
  mrb_value cb = mrb_hash_get(mrb, events, mrb_fixnum_value(event.type));
  mrb_value data = hiro_event_to_mrb_value(mrb, event);

  if(mrb_nil_p(cb)) {
    return;
  }

  mrb_yield_argv(mrb, cb, 1, &data);
}

mrb_value hiro_event_mrb_poll(mrb_state* mrb, mrb_value self) {

  SDL_Event ev;
  while(SDL_PollEvent(&ev)) {
    hiro_event_call(mrb, ev);
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
