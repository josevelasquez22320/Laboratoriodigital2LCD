/*
 * LCD.h
 *
 * Created: 30/01/2025 10:28:33
 *  Author: josea
 */ 

#ifndef LCD
#define LCD

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

// Definition of control pins for the LCD
#define REG_SEL PB2  // Register Select (RS) on pin PB2
#define READ_WRITE PB3  // Read/Write (RW) on pin PB3
#define ENABLE_PIN PB5  // Enable (E) on pin PB5

// Definition of data ports for the LCD
#define LCD_DATA_PORT PORTC  // Data port for the LCD
#define LCD_DATA_DDR DDRC    // Data port direction (input/output)
#define LCD_CTRL_PORT PORTB  // Control port for the LCD
#define LCD_CTRL_DDR DDRB    // Control port direction (input/output)

// Function prototypes
void lcd_send_command(uint8_t cmd);
void lcd_initialize(void);
void lcd_send_data(uint8_t data);
void lcd_print_text(const char *str);
void lcd_clear_screen(void);
void lcd_set_cursor_position(uint8_t row, uint8_t col);

#endif /* LCD_16X2_8B_V2_H_ */
