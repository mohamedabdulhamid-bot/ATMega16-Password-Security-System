#ifndef ALCD_H_
#define ALCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>

// LCD commands
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_ENTRY_MODE      0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT    0x10
#define LCD_FUNCTION_SET    0x20
#define LCD_SET_CGRAM       0x40
#define LCD_SET_DDRAM       0x80

// Flags for display entry mode
#define LCD_ENTRY_RIGHT     0x00
#define LCD_ENTRY_LEFT      0x02
#define LCD_ENTRY_SHIFT_INC 0x01
#define LCD_ENTRY_SHIFT_DEC 0x00

// Flags for display on/off control
#define LCD_DISPLAY_ON      0x04
#define LCD_DISPLAY_OFF     0x00
#define LCD_CURSOR_ON       0x02
#define LCD_CURSOR_OFF      0x00
#define LCD_BLINK_ON        0x01
#define LCD_BLINK_OFF       0x00

// Flags for function set
#define LCD_8BIT_MODE       0x10
#define LCD_4BIT_MODE       0x00
#define LCD_2LINE           0x08
#define LCD_1LINE           0x00
#define LCD_5x10_DOTS       0x04
#define LCD_5x8_DOTS        0x00

// =============================================
// LCD PIN DEFINITIONS - UPDATE THESE FOR YOUR WIRING
// =============================================

// Control Pins (REQUIRED)
#define LCD_RS_PORT     PORTA
#define LCD_RS_DDR      DDRA
#define LCD_RS_PIN      0    // PA0 -> LCD RS (Pin 4)

#define LCD_RW_PORT     PORTA  
#define LCD_RW_DDR      DDRA
#define LCD_RW_PIN      1    // PA1 -> LCD RW (Pin 5) - Can ground this pin if not reading

#define LCD_EN_PORT     PORTA
#define LCD_EN_DDR      DDRA
#define LCD_EN_PIN      2    // PA2 -> LCD E (Pin 6)

// Data Pins (4-bit mode uses D4-D7 only)
#define LCD_D4_PORT     PORTA
#define LCD_D4_DDR      DDRA
#define LCD_D4_PIN      3    // PA3 -> LCD D4 (Pin 11)

#define LCD_D5_PORT     PORTA
#define LCD_D5_DDR      DDRA
#define LCD_D5_PIN      4    // PA4 -> LCD D5 (Pin 12)

#define LCD_D6_PORT     PORTA
#define LCD_D6_DDR      DDRA
#define LCD_D6_PIN      5    // PA5 -> LCD D6 (Pin 13)

#define LCD_D7_PORT     PORTA
#define LCD_D7_DDR      DDRA
#define LCD_D7_PIN      6    // PA6 -> LCD D7 (Pin 14)

// Backlight control (optional)
#define LCD_BL_PORT     PORTA
#define LCD_BL_DDR      DDRA  
#define LCD_BL_PIN      7    // PA7 -> LCD Backlight+

// =============================================
// USER FUNCTIONS (CodeVision compatible)
// =============================================
void lcd_init(unsigned char lcd_columns);
void lcd_clear(void);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_putchar(char c);
void lcd_puts(const char *str);
void lcd_putsf(const char *str);
void lcd_printf(char *fmt, ...);

// Backlight control
void lcd_backlight_on(void);
void lcd_backlight_off(void);

// Custom character functions
void lcd_create_char(unsigned char location, unsigned char *charmap);

#endif /* ALCD_H_ */