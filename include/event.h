// Hiro Framework - Copyright 2017 Zheng Xian Qiu

#ifndef _HIRO_EVENT_H
#define _HIRO_EVENT_H

#include "hiro.h"

mrb_value hiro_create_event(mrb_state*);

void hiro_event_emit(mrb_state*, SDL_Event);

#endif
