# Button Debounce Filter
Microcontroller GPIO button interface library.

[Library files](https://github.com/binarymaker/button-debounce/tree/master/sw-button-debounce/User-Library/button-debounce)
 
# Debounce concept 

```
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
```

# Code usage

## Debounce

```c
/* Include library */
#include "button.h"

/* button objects */
button_t btn;

void main()
{
   /* GPIO system initialization */
   User_Gpio_Init();

   /* Initialization of debounce filters */
   button_create(&btn, (uint32_t *)&GPIOB->IDR, GPIO_PIN_4, active_low); 
  
   /* Eliminate delay filter for debounce test */
   button_filter(&btn, 0, 0);

   while(1)
   {
      orgState = !(GPIOB->IDR & GPIO_PIN_4); /* Active low logic */
      debounceState = button_read(&btn);

      if (orgState != last_orgState)
      {
         last_orgState = orgState;
         orgCount++;
      }
    
      if (debounceState != last_debounceState)
      {
         last_debounceState = debounceState;
         debounceCount++;
      }
    
      if (HAL_GetTick() - print_time > 2000)
      {
         print_time = HAL_GetTick();
         printf("$%d %d;", orgCount, debounceCount);
      }

   }
}

```
Output:

Time(Sec) | orgCount | debounceCount
:---:     |:---:     |:---:
0         |0         | 0
2         |2         | 2
4         |2         | 2
8         |2         | 2
10        |8         | 5
12        |16        | 9
14        |23        | 13
16        |31        | 17
18        |38        | 21
20        |45        | 26
22        |53        | 30
24        |60        | 34
26        |64        | 36
28        |64        | 36

   + channel 0 - orgCount
   + channel 1 - debounceCount

![alt text](image/signal_vs_debounce.png)

## Long press

```c
/* Include library */
#include "button.h"

/* button objects */
button_t inc_btn;
button_t dec_btn;

void main()
{
   /* GPIO system initialization */
   User_Gpio_Init();

   /* Initialization of debounce filters
    *
    * Default debounce time - 10ms 
    * Filter on delay - 50ms
    * Filter off delay - 50ms
    * Refer configuration file button-cfg.h
    */ 
   button_create(&inc_btn, (uint32_t *)&GPIOB->IDR, GPIO_PIN_4, active_low); 
   button_create(&dec_btn, (uint32_t *)&GPIOB->IDR, GPIO_PIN_5, active_low); 

   while(1)
   {
      button_read(&inc_btn);
      button_read(&dec_btn);

      /* inc button short press */
      if (button_wasPressed(&inc_btn))
      {
         counter += 1;
      }

      /* inc button long press */
      if (button_pressedFor(&inc_btn, 1000))
      {
         if (HAL_GetTick() - longpress_inc_time > 500)
         {
            longpress_inc_time = HAL_GetTick();
            counter += 5;
         }
      }

      /* dec button short press */
      if (button_wasPressed(&dec_btn))
      {
         counter -= 1;
      }
      
      /* dec button long press */
      if (button_pressedFor(&dec_btn, 1000))
      {
         if (HAL_GetTick() - longpress_inc_time > 500)
         {
            longpress_inc_time = HAL_GetTick();
            counter -= 5;
         }
      }
      
      /* print count value */
      if (HAL_GetTick() - print_time > 500)
      {
         print_time = HAL_GetTick();
         printf("$%d;", counter);
      }
   }
}

```
Output:

Button | Press Length| Count
:---:  |:---:        |:---:
--     |--           |0
inc    |short        |1
inc    |short        |2
dec    |short        |1
dec    |long         |-4
inc    |short        |-3
inc    |long         |2
inc    |long         |7
inc    |long         |12
--     |--           |12
dec    | short       |11
dec    | long        |6
