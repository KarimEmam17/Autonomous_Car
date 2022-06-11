/*
 * LCD_CFG.h
 *
 * Created: 5/27/2022 4:41:34 PM
 *  Author: K.EMAM
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "GPIO_KAREEM.h"
#include "REG_ATMEL.h"

#define LCD_8_BIT_CMD_PORT           GPIO_PORTB
#define LCD_8_BIT_DATA_PORT          GPIO_PORTA
#define LCD_8_BIT_BUS                PORTA

#define LCD_4_BIT_CMD_PORT           GPIO_PORTB
#define LCD_4_BIT_DATA_PORT          GPIO_PORTA
#define LCD_4_BIT_BUS                PORTA

#define RS_PIN                       GPIO_PIN_1
#define RW_PIN                       GPIO_PIN_2
#define E_PIN                        GPIO_PIN_3
									
#define LCD_PIN0                     GPIO_PIN_0
#define LCD_PIN1                     GPIO_PIN_1
#define LCD_PIN2                     GPIO_PIN_2
#define LCD_PIN3                     GPIO_PIN_3
#define LCD_PIN4                     GPIO_PIN_4
#define LCD_PIN5                     GPIO_PIN_5
#define LCD_PIN6                     GPIO_PIN_6
#define LCD_PIN7                     GPIO_PIN_7

#endif /* LCD_CFG_H_ */