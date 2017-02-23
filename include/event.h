#ifndef _HIRO_EVENT_H
#define _HIRO_EVENT_H

#include "hiro.h"

mrb_bool hiro_event_has_events(mrb_state*);
mrb_value hiro_event_get_events(mrb_state*);
void hiro_event_init_events(mrb_state*);
void hiro_event_register(mrb_state*, mrb_int, mrb_value);

HIRO_API void hiro_event_call(mrb_state*, SDL_Event);

mrb_value hiro_event_to_mrb_value(mrb_state*, SDL_Event);
mrb_value hiro_event_new_data(mrb_state* mrb);
mrb_value hiro_event_set_keyboard_data(mrb_state* mrb, SDL_Event);

mrb_value hiro_event_mrb_poll(mrb_state*, mrb_value);
mrb_value hiro_event_mrb_on(mrb_state*, mrb_value);

void hiro_define_event(mrb_state*);

#endif
