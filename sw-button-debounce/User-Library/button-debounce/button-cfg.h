
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

#ifndef BM_41f7266e_7c45_11e9_b196_c8ff28b6c6d9
#define BM_41f7266e_7c45_11e9_b196_c8ff28b6c6d9

/* tick timer library */
#include "stm32f0xx_hal.h"

#define TICK_TIMER          HAL_GetTick()               /* 1ms timer */

/*
 * Default confanfiguration for all button object 
 * 
 * Refer fn button_filter()
 *       button->db_time
 */
#define DEBOUNCE_TIME       10
#define ON_DELAY            50
#define OFF_DELAY           50

#endif // BM_41f7266e_7c45_11e9_b196_c8ff28b6c6d9
