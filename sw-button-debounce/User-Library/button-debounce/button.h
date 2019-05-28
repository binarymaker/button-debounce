
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

#ifndef BM_41d28752_7c45_11e9_9925_c8ff28b6c6d9
#define BM_41d28752_7c45_11e9_9925_c8ff28b6c6d9

#include "button-cfg.h"
#include "stdint.h"
#include "stdbool.h"

typedef enum {active_low = 0, active_high} active_logic_t;

typedef struct button_s{
  uint32_t *reg;
  uint16_t pin;
  active_logic_t active_logic;
  bool changed;
  bool state;
  bool laststate;
  bool fstate;
  bool fchanged;
  bool lastfstate;
  uint32_t time;
  uint32_t lastchange;
  uint32_t db_time;
  uint16_t on_delay;
  uint16_t off_delay;
}button_t;

void button_create(button_t *context, uint32_t *reg, uint16_t pin, active_logic_t active_logic);

bool button_read(button_t *context);

bool button_isPressed(button_t *context);

bool button_isReleased(button_t *context);

bool button_wasPressed(button_t *context);

bool button_wasReleased(button_t *context);

bool button_pressedFor(button_t *context, uint32_t time);

bool button_releasedFor(button_t *context, uint32_t time);

bool button_filter(button_t *context, uint32_t on_time,uint32_t off_time);

#endif // BM_41d28752_7c45_11e9_9925_c8ff28b6c6d9
