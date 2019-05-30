
/**
 ******************************************************************************
 * ______  _                             ___  ___        _
 * | ___ \(_)                            |  \/  |       | |
 * | |_/ / _  _ __    __ _  _ __  _   _  | .  . |  __ _ | | __ ___  _ __
 * | ___ \| || '_ \  / _` || '__|| | | | | |\/| | / _` || |/ // _ \| '__|
 * | |_/ /| || | | || (_| || |   | |_| | | |  | || (_| ||   <|  __/| |
 * \____/ |_||_| |_| \__,_||_|    \__, | \_|  |_/ \__,_||_|\_\\___||_|
 *                                 __/ |
 *                                |___/
 *
 * Copyright (C) 2019 Binary Maker - All Rights Reserved
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution.
 * Written by Binary Maker <https://github.com/binarymaker>
 ******************************************************************************
 */

#include "button.h"
#include "button-cfg.h"

bool
button_raw(button_t *context)
{
  bool raw = (uint16_t)(context->reg[0]) & context->pin;

  if (context->active_logic == active_low)
  {
    raw = !raw;
  }
  return raw;
}

void
button_create(button_t *context, uint32_t *reg, uint16_t pin,
              active_logic_t active_logic)
{
  context->reg = reg;
  context->pin = pin;
  context->active_logic = active_logic;

  context->state = button_raw(context);

  context->fstate = context->state;
  context->fstate = context->lastfstate;
  context->laststate = context->state;
  context->lastchange = context->time;
  context->changed = false;
  context->fchanged = false;
  context->time = TICK_TIMER;
  context->db_time = DEBOUNCE_TIME;
  context->on_delay = ON_DELAY;
  context->off_delay = OFF_DELAY;
}

void
button_filter(button_t *context, uint32_t on_time, uint32_t off_time)
{
  context->on_delay = on_time;
  context->off_delay = off_time;
}

bool
button_read(button_t *context)
{
  uint32_t now = TICK_TIMER;
  bool pinVal = button_raw(context);

  if (now - context->lastchange < context->db_time)
  {
    context->changed = false;
  }
  else
  {
    context->laststate = context->state;
    context->state = pinVal;
    context->changed = (context->laststate != context->state);
    if (context->changed)
    {
      context->lastchange = now;
    }
  }
  context->time = now;

  context->lastfstate = context->fstate;

  if (context->state && ((context->time - context->lastchange) >=
                         context->on_delay))
  {
    context->fstate = true;
  }
  else if (!context->state && ((context->time - context->lastchange) >=
                               context->off_delay))
  {
    context->fstate = false;
  }

  context->fchanged = (context->fstate != context->lastfstate);

  return context->fstate;
}

bool
button_isPressed(button_t *context)
{
  return context->fstate;
}

bool
button_isReleased(button_t *context)
{
  return !context->fstate;
}

bool
button_wasPressed(button_t *context)
{
  return context->fstate && context->fchanged;
}

bool
button_wasReleased(button_t *context)
{
  return !context->fstate && context->fchanged;
}

bool
button_pressedFor(button_t *context, uint32_t time)
{
  return context->fstate && ((context->time - context->lastchange) >= time);
}

bool
button_releasedFor(button_t *context, uint32_t time)
{
  return !context->fstate && ((context->time - context->lastchange) >= time);
}

