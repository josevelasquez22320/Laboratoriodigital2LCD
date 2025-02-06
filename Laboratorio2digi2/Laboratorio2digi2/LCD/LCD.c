/*
 * LCD.c
 *
 * Created: 30/01/2025 10:28:22
 *  Author: josea
 */ 

#include "LCD.h"

// Definition of control pins for the LCD
#define REG_SEL PB2  // Register Select (RS) on pin PB2
#define READ_WRITE PB3  // Read/Write (RW) on pin PB3
#define ENABLE_PIN PB5  // Enable (E) on pin PB5

// Definition of data ports for the LCD
#define LCD_DATA_PORT PORTC  // Data port for the LCD
#define LCD_DATA_DDR DDRC    // Data port direction (input/output)
#define LCD_CTRL_PORT PORTB  // Control port for the LCD
#define LCD_CTRL_DDR DDRB    // Control port direction (input/output)

// Function to send commands to the LCD
void lcd_send_command(uint8_t cmd) {
	// Select that we are sending a command
	LCD_CTRL_PORT &= ~(1 << REG_SEL);  // REG_SEL = 0 (command)
	LCD_CTRL_PORT &= ~(1 << READ_WRITE);  // READ_WRITE = 0 (write)
	
	// Send the most significant 4 bits to the data port
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);
	LCD_CTRL_PORT = (LCD_CTRL_PORT & 0x0F) | (cmd & 0x0F);

	// Enable pulse
	LCD_CTRL_PORT |= (1 << ENABLE_PIN);  // Enable
	_delay_us(1);           // Brief delay
	LCD_CTRL_PORT &= ~(1 << ENABLE_PIN); // Disable
	_delay_ms(2);           // Wait for the command to be processed
}

// Function to initialize the LCD
void lcd_initialize(void) {
	LCD_DATA_DDR = 0xFF;   // Configure the data port as output
	LCD_CTRL_DDR = 0x1F;    // Configure PB0-PB4 as output

	_delay_ms(15);     // Initial delay after turning on the LCD
	lcd_send_command(0x30); // Send initialization command (8 bits)
	_delay_ms(5);      // Wait for stabilization
	lcd_send_command(0x30); // Repeat initialization
	_delay_us(100);    // Short delay
	lcd_send_command(0x30); // Last repeat of initialization

	// Configure the LCD
	lcd_send_command(0x38); // 8-bit mode, 2 lines, 5x8 character matrix
	lcd_send_command(0x08); // Turn off display
	lcd_send_command(0x01); // Clear display
	_delay_ms(2);      // Wait for the LCD to process the clear command
	lcd_send_command(0x06); // Set increment mode with no shift
	lcd_send_command(0x0C); // Turn on display and hide cursor
}

// Function to send data to the LCD (print characters)
void lcd_send_data(uint8_t data) {
	// Select that we are sending data
	LCD_CTRL_PORT |= (1 << REG_SEL);  // REG_SEL = 1 (data)
	LCD_CTRL_PORT &= ~(1 << READ_WRITE); // READ_WRITE = 0 (write)
	
	// Send the most significant 4 bits to the data port
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	LCD_CTRL_PORT = (LCD_CTRL_PORT & 0x0F) | (data & 0x0F);

	// Enable pulse
	LCD_CTRL_PORT |= (1 << ENABLE_PIN);  // Enable
	_delay_us(1);           // Brief delay
	LCD_CTRL_PORT &= ~(1 << ENABLE_PIN); // Disable
	_delay_ms(2);           // Wait for the data to be processed
}

// Function to print a string on the LCD
void lcd_print_text(const char *str) {
	while (*str) {  // Iterate until the null character is reached
		lcd_send_data(*str);  // Send each character to the LCD
		str++;           // Move to the next character
	}
}

// Function to clear the LCD screen
void lcd_clear_screen(void) {
	lcd_send_command(0x01);  // Send clear display command
	_delay_ms(2);       // Wait for the LCD to process the command
}

// Function to set the cursor at a specific row and column
void lcd_set_cursor_position(uint8_t row, uint8_t col) {
	uint8_t position = (row == 0) ? (0x80 + col) : (0xC0 + col); // 0x80 for the first row, 0xC0 for the second row
	lcd_send_command(position); // Send command to move the cursor
}
