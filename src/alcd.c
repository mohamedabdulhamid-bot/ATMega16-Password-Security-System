#include "alcd.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// LCD port definitions - Change these according to your connections
#define LCD_RS_PORT     PORTA
#define LCD_RS_DDR      DDRA
#define LCD_RS_PIN      0

#define LCD_RW_PORT     PORTA  
#define LCD_RW_DDR      DDRA
#define LCD_RW_PIN      1

#define LCD_EN_PORT     PORTA
#define LCD_EN_DDR      DDRA
#define LCD_EN_PIN      2

#define LCD_D4_PORT     PORTA
#define LCD_D4_DDR      DDRA
#define LCD_D4_PIN      3

#define LCD_D5_PORT     PORTA
#define LCD_D5_DDR      DDRA
#define LCD_D5_PIN      4

#define LCD_D6_PORT     PORTA
#define LCD_D6_DDR      DDRA
#define LCD_D6_PIN      5

#define LCD_D7_PORT     PORTA
#define LCD_D7_DDR      DDRA
#define LCD_D7_PIN      6

// Backlight pin (if available)
#define LCD_BL_PORT     PORTA
#define LCD_BL_DDR      DDRA
#define LCD_BL_PIN      7

// Local variables
static unsigned char lcd_cols = 16;
static unsigned char lcd_rows = 2;

// Private function prototypes
static void lcd_write_nibble(unsigned char nibble);
static void lcd_write_byte(unsigned char data, unsigned char mode);
static void lcd_busy_wait(void);

// Initialize LCD
void lcd_init(unsigned char lcd_columns)
{
    lcd_cols = lcd_columns;
    lcd_rows = 2; // Assuming 2-line display
    
    // Set control pins as outputs
    LCD_RS_DDR |= (1 << LCD_RS_PIN);
    LCD_RW_DDR |= (1 << LCD_RW_PIN);
    LCD_EN_DDR |= (1 << LCD_EN_PIN);
    
    // Set data pins as outputs
    LCD_D4_DDR |= (1 << LCD_D4_PIN);
    LCD_D5_DDR |= (1 << LCD_D5_PIN);
    LCD_D6_DDR |= (1 << LCD_D6_PIN);
    LCD_D7_DDR |= (1 << LCD_D7_PIN);
    
    // Set backlight pin as output (if used)
    LCD_BL_DDR |= (1 << LCD_BL_PIN);
    lcd_backlight_on();
    
    // Wait for LCD to power up
    _delay_ms(50);
    
    // Initialization sequence for 4-bit mode
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
    
    // Send initialization commands
    lcd_write_nibble(0x03);
    _delay_ms(5);
    lcd_write_nibble(0x03);
    _delay_us(150);
    lcd_write_nibble(0x03);
    _delay_us(150);
    lcd_write_nibble(0x02); // Set 4-bit mode
    
    // Function set: 4-bit mode, 2 lines, 5x8 font
    lcd_write_byte(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8_DOTS, 0);
    
    // Display off
    lcd_write_byte(LCD_DISPLAY_CONTROL | LCD_DISPLAY_OFF, 0);
    
    // Clear display
    lcd_clear();
    
    // Entry mode set: increment, no shift
    lcd_write_byte(LCD_ENTRY_MODE | LCD_ENTRY_LEFT, 0);
    
    // Display on, cursor off, blink off
    lcd_write_byte(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF, 0);
}

// Clear LCD display
void lcd_clear(void)
{
    lcd_write_byte(LCD_CLEAR, 0);
    _delay_ms(2);
}

// Set cursor position
void lcd_gotoxy(unsigned char x, unsigned char y)
{
    unsigned char address;
    
    switch(y)
    {
        case 0: address = 0x00; break;
        case 1: address = 0x40; break;
        case 2: address = 0x14; break; // For 4-line displays
        case 3: address = 0x54; break; // For 4-line displays
        default: address = 0x00;
    }
    
    address += x;
    lcd_write_byte(LCD_SET_DDRAM | address, 0);
}

// Write a single character
void lcd_putchar(char c)
{
    lcd_write_byte(c, 1);
}

// Write a string from RAM
void lcd_puts(const char *str)
{
    while(*str)
    {
        lcd_putchar(*str++);
    }
}

// Write a string from flash (program memory)
void lcd_putsf(const char *str)
{
    char c;
    while((c = *str++))
    {
        lcd_putchar(c);
    }
}

// Formatted printing (simplified version)
void lcd_printf(char *fmt, ...)
{
    char buffer[32];
    va_list args;
    
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    lcd_puts(buffer);
}

// Turn backlight on
void lcd_backlight_on(void)
{
    LCD_BL_PORT |= (1 << LCD_BL_PIN);
}

// Turn backlight off
void lcd_backlight_off(void)
{
    LCD_BL_PORT &= ~(1 << LCD_BL_PIN);
}

// Create custom character
void lcd_create_char(unsigned char location, unsigned char *charmap)
{
    location &= 0x07; // Only 8 locations (0-7)
    lcd_write_byte(LCD_SET_CGRAM | (location << 3), 0);
    
    for(int i = 0; i < 8; i++)
    {
        lcd_write_byte(charmap[i], 1);
    }
}

// Private: Write a nibble to LCD
static void lcd_write_nibble(unsigned char nibble)
{
    // Set data pins according to nibble
    if(nibble & 0x01) LCD_D4_PORT |= (1 << LCD_D4_PIN);
    else LCD_D4_PORT &= ~(1 << LCD_D4_PIN);
    
    if(nibble & 0x02) LCD_D5_PORT |= (1 << LCD_D5_PIN);
    else LCD_D5_PORT &= ~(1 << LCD_D5_PIN);
    
    if(nibble & 0x04) LCD_D6_PORT |= (1 << LCD_D6_PIN);
    else LCD_D6_PORT &= ~(1 << LCD_D6_PIN);
    
    if(nibble & 0x08) LCD_D7_PORT |= (1 << LCD_D7_PIN);
    else LCD_D7_PORT &= ~(1 << LCD_D7_PIN);
    
    // Pulse enable pin
    LCD_EN_PORT |= (1 << LCD_EN_PIN);
    _delay_us(1);
    LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
    _delay_us(50);
}

// Private: Write a byte to LCD
static void lcd_write_byte(unsigned char data, unsigned char mode)
{
    if(mode) // Data mode
        LCD_RS_PORT |= (1 << LCD_RS_PIN);
    else     // Command mode
        LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
        
    LCD_RW_PORT &= ~(1 << LCD_RW_PIN); // Write mode
    
    // Write high nibble first
    lcd_write_nibble(data >> 4);
    // Write low nibble
    lcd_write_nibble(data & 0x0F);
    
    // Wait for LCD to process
    _delay_us(50);
}

// Private: Wait until LCD is not busy
static void lcd_busy_wait(void)
{
    // For simplicity, using delay instead of busy flag checking
    _delay_us(50);
}