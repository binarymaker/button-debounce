
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

/**
 * @file button.h
 * @author binary maker <https://github.com/binarymaker>
 * @brief button debounce and button on delay, off delay filter
 * @date 2019-05-30
 */

/*

                          _______________________
Expected switch  ________|                       |___________________
               
                              ___________________
Actual switch    ________|||||                   |||||_______________
                         <--->                   <--->
                           ^---_Button glitches----^ 
                          _______________________
Debounce Delay   ________|                       |___________________
applied
                                _______________________
Filter On-Off    ______________|                       |_____________
Delay Applied             <---->                  <---->
                   On delay-^              Off delay-^
               
```
+ Filter delay used for noise remove
```
                                              ______ _____
signal           ______|___________|_________|      |     |________
                 Noise-^-----------^----------------^
                        ___         ___       ______     _
Debounce delay   ______|   |_______|   |_____|      |___| |________ NOT OK
signal
                                                 ____________
filtered delay   _______________________________|            |______ OK
signal

Debounce delay + Filter delay

*/
#include "button-cfg.h"
#include "stdint.h"
#include "stdbool.h"

typedef enum
{
  active_low = 0,
  active_high
} active_logic_t;

typedef struct button_s
{
  uint32_t *reg;               /**< GPIO read mcu register */
  uint16_t pin;                /**< Port pin mask ex:(1 << pin_number) */
  active_logic_t active_logic; /**< Active logic */

  bool state;     /** Present state of button */
  bool laststate; /** Previews state of button */
  bool changed;   /**< Button state change */

  bool fstate;     /** Filtered button present status */
  bool lastfstate; /** Filtered button previews status */
  bool fchanged;   /**< Filtered button state change */

  uint32_t time;       /**< Time stamp of system*/
  uint32_t lastchange; /**< Button status confirmed time stamp*/
  uint32_t db_time;    /**< Button debounce time in ms */
  uint16_t on_delay;   /** Filter on delay in ms */
  uint16_t off_delay;  /** Filter on delay in ms */
} button_t;

/**
 * @brief Button object initialization
 * 
 * @param context [in] Instance of button object
 * @param reg [in] GPIO Port read register address pointer
 * @param pin [in] GPIO pin mask
 * @param active_logic [in] Active logic of button
 */
void button_create(button_t *context, uint32_t *reg, uint16_t pin, active_logic_t active_logic);

/**
 * @brief Assign button filter value on-off delay to button object
 * 
 * @param context [in] Instance of button object
 * @param on_time [in] Button on delay time in ms
 * @param off_time [in] Button off delay time in ms
 */
void button_filter(button_t *context, uint32_t on_time, uint32_t off_time);

/**
 * @brief Read button object status 
 * 
 * @param context [in] Instance of button object
 * @return true - Button is press
 * @return false - Button is not press
 */
bool button_read(button_t *context);

/**
 * @brief Check button is press
 * 
 * @param context [in] Instance of button object
 * @return true - Button is press
 * @return false - Button is not press
 */
bool button_isPressed(button_t *context);

/**
 * @brief Check button is not press or release
 * 
 * @param context [in] Instance of button object
 * @return true - Button is not press or release
 * @return false - Button is press
 */
bool button_isReleased(button_t *context);

/**
 * @brief Check button status changes
 * 
 * @param context [in] Instance of button object
 * @return true - Button state change to pressed
 * @return false - Button state change to not pressed
 */
bool button_wasPressed(button_t *context);

/**
 * @brief Check button status changes
 * 
 * @param context [in] Instance of button object
 * @return true - Button state change to pressed
 * @return false - Button state change to not pressed
 */
bool button_wasReleased(button_t *context);

/**
 * @brief Check button status for particular time
 * 
 * @param context [in] Instance of button object
 * @param time [in] Button press time in ms
 * @return true - Button press time reach expected
 * @return false - Button press time not reach expected
 */
bool button_pressedFor(button_t *context, uint32_t time);

/**
 * @brief Check button status for particular time
 * 
 * @param context [in] Instance of button object
 * @param time [in] Button release time in ms
 * @return true - Button release time reach expected
 * @return false - Button release time not reach expected
 */
bool button_releasedFor(button_t *context, uint32_t time);

#endif // BM_41d28752_7c45_11e9_9925_c8ff28b6c6d9
